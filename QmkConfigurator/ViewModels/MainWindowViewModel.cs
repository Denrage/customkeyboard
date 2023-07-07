using Avalonia.Media;
using HarfBuzzSharp;
using HidApi;
using ReactiveUI;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Management;
using System.Reactive;
using System.Runtime.ExceptionServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;

namespace QmkConfigurator.ViewModels;
public class MainWindowViewModel : ViewModelBase
{
    private readonly UsbService usbService;
    private bool keyboardConnected;
    private Color color;
    private SetRgbEffectCommand.Effects selectedEffect;

    public IEnumerable<SetRgbEffectCommand.Effects> Effects => Enum.GetValues<SetRgbEffectCommand.Effects>();

    public SetRgbEffectCommand.Effects SelectedEffect
    {
        get => selectedEffect;
        set
        {
            if (this.RaiseAndSetIfChanged(ref this.selectedEffect, value) == value)
            {
                this.usbService.Communication.SendPacket(new SetRgbEffectCommand()
                {
                    Effect = value
                });
            }
        }
    }

    public Color Color
    {
        get => this.color;
        set
        {
            if (this.RaiseAndSetIfChanged(ref this.color, value) == value)
            {
                this.usbService.Communication.SendPacket(new SetHsvColorCommand()
                {
                    HsvColor = SetHsvColorCommand.Color.FromRgb(this.Color.G, this.Color.B, this.Color.R),
                });
            }
        }
    }

    public bool KeyboardConnected
    {
        get => this.keyboardConnected;
        set => this.RaiseAndSetIfChanged(ref this.keyboardConnected, value);
    }

    public MainWindowViewModel()
    {
        this.usbService = new UsbService(new UsbListener());
        usbService.KeyboardConnected += () => this.KeyboardConnected = true;
        usbService.KeyboardDisconnected += () => this.KeyboardConnected = false;
        this.usbService.Initialize();
    }
}

public class UsbService
{
    private const ushort VendorId = 0xFEEA;
    private const ushort ProductId = 0x001;
    private readonly UsbListener listener;

    public event Action KeyboardConnected;
    public event Action KeyboardDisconnected;

    public HidCommunication? Communication { get; private set; }

    public UsbService(UsbListener listener)
    {
        this.listener = listener;
    }

    public void Initialize()
    {
        this.listener.UsbDeviceConnected += DeviceConnected;
        this.listener.UsbDeviceDisconnected += DeviceDisconnected;
        this.listener.Start();
    }

    private void DeviceConnected(UsbDevice device)
    {
        if (device.ProductId == ProductId && device.VendorId == VendorId)
        {
            var hidDevice = HidApi.Hid.Enumerate(VendorId, ProductId).FirstOrDefault(x => x.Usage == 0x61 && x.UsagePage == 0xFF60);
            if (hidDevice != null)
            {
                this.Communication = new HidCommunication(hidDevice);
                this.Communication.Open();
                this.KeyboardConnected?.Invoke();
            }
        }
    }

    private void DeviceDisconnected(UsbDevice device)
    {
        if (device.ProductId == ProductId && device.VendorId == VendorId)
        {
            this.Communication?.Dispose();
            //this.Communication = null;
            this.KeyboardDisconnected?.Invoke();
        }
    }
}

public class UsbDevice
{
    private static readonly Regex HardwareIdTripletRegex = new Regex(@"USB\\VID_([0-9A-F]{4})&PID_([0-9A-F]{4})&REV_([0-9A-F]{4}).*");

    public ManagementBaseObject WmiDevice { get; }

    public ushort VendorId { get; }

    public ushort ProductId { get; }

    public ushort RevisionBcd { get; }

    public string ManufacturerString { get; }

    public string ProductString { get; }

    public string Driver { get; }

    public UsbDevice(ManagementBaseObject d)
    {
        WmiDevice = d;

        ManufacturerString = (string)WmiDevice.GetPropertyValue("Manufacturer");
        ProductString = (string)WmiDevice.GetPropertyValue("Name");

        var hardwareIdTriplet = HardwareIdTripletRegex.Match(GetHardwareId(WmiDevice));
        VendorId = Convert.ToUInt16(hardwareIdTriplet.Groups[1].ToString(), 16);
        ProductId = Convert.ToUInt16(hardwareIdTriplet.Groups[2].ToString(), 16);
        RevisionBcd = Convert.ToUInt16(hardwareIdTriplet.Groups[3].ToString(), 16);

        Driver = GetDriverName(WmiDevice);
    }

    public override string ToString()
    {
        return $"{ManufacturerString} {ProductString} ({VendorId:X4}:{ProductId:X4}:{RevisionBcd:X4})";
    }

    private static string GetHardwareId(ManagementBaseObject d)
    {
        var hardwareIds = (string[])d.GetPropertyValue("HardwareID");
        if (hardwareIds != null && hardwareIds.Length > 0)
        {
            return hardwareIds[0];
        }

        return null;
    }

    private static string GetDriverName(ManagementBaseObject d)
    {
        var service = (string)d.GetPropertyValue("Service");
        if (service != null && service.Length > 0)
        {
            return service;
        }

        return "NO DRIVER";
    }
}

public class UsbListener
{
    private static readonly Regex UsbIdRegex = new Regex(@"USB\\VID_([0-9A-F]{4})&PID_([0-9A-F]{4})&REV_([0-9A-F]{4})");
    private readonly List<UsbDevice> Devices = new List<UsbDevice>();
    private ManagementEventWatcher deviceConnectedWatcher;
    private ManagementEventWatcher deviceDisconnectedWatcher;

    public event Action<UsbDevice> UsbDeviceConnected;
    public event Action<UsbDevice> UsbDeviceDisconnected;

    public UsbListener()
    {
    }

    public void Start()
    {
        this.deviceConnectedWatcher ??= CreateManagementEventWatcher("__InstanceCreationEvent");
        this.deviceConnectedWatcher.EventArrived += UsbDeviceWmiEvent;
        this.deviceConnectedWatcher.Start();

        this.deviceDisconnectedWatcher ??= CreateManagementEventWatcher("__InstanceDeletionEvent");
        this.deviceDisconnectedWatcher.EventArrived += UsbDeviceWmiEvent;
        this.deviceDisconnectedWatcher.Start();

        this.EnumerateUsbDevices(true);
    }

    private void EnumerateUsbDevices(bool connected)
    {
        var enumeratedDevices = new ManagementObjectSearcher(@"SELECT * FROM Win32_PnPEntity WHERE DeviceID LIKE 'USB%'").Get()
            .Cast<ManagementBaseObject>().ToList()
            .Where(d => ((string[])d.GetPropertyValue("HardwareID")).Any(s => UsbIdRegex.Match(s).Success));

        if (connected)
        {
            foreach (var device in enumeratedDevices)
            {
                var listed = Devices.ToList().Aggregate(false, (curr, d) => curr | d.WmiDevice.Equals(device));

                if (device != null && !listed)
                {
                    var usbDevice = new UsbDevice(device);

                    if (!this.Devices.Any(x => x.VendorId == usbDevice.VendorId && x.ProductId == usbDevice.ProductId))
                    {
                        this.UsbDeviceConnected?.Invoke(usbDevice);
                    }

                    this.Devices.Add(usbDevice);
                }
            }
        }
        else
        {
            var devices = this.Devices.ToList();
            foreach (var device in devices)
            {
                var listed = enumeratedDevices.Aggregate(false, (curr, d) => curr | device.WmiDevice.Equals(d));

                if (!listed)
                {
                    _ = this.Devices.Remove(device);
                    this.UsbDeviceDisconnected?.Invoke(device);
                }
            }
        }
    }

    private void UsbDeviceWmiEvent(object sender, EventArrivedEventArgs e)
    {
        if (!(e.NewEvent["TargetInstance"] is ManagementBaseObject _))
        {
            return;
        }

    (sender as ManagementEventWatcher)?.Stop();
        EnumerateUsbDevices(e.NewEvent.ClassPath.ClassName.Equals("__InstanceCreationEvent"));
        (sender as ManagementEventWatcher)?.Start();
    }

    private ManagementEventWatcher CreateManagementEventWatcher(string eventType)
    {
        return new ManagementEventWatcher($"SELECT * FROM {eventType} WITHIN 2 WHERE TargetInstance ISA 'Win32_PnPEntity' AND TargetInstance.DeviceID LIKE 'USB%'");
    }
}

public class HidCommunication : IDisposable
{
    private readonly DeviceInfo deviceInfo;
    private Device device;
    private readonly CancellationTokenSource readCancellationTokenSource = new CancellationTokenSource();

    public HidCommunication(DeviceInfo device)
    {
        this.deviceInfo = device;
    }

    public void Open()
    {
        this.device = this.deviceInfo.ConnectToDevice();
        Task.Run(() => this.ReceivePacket(this.readCancellationTokenSource.Token));
    }

    public void SendPacket(HidPacket packet)
    {
        var message = packet.Serialize();

        using var messageToSend = new MemoryStream();

        using (var binaryWriter = new BinaryWriter(messageToSend, Encoding.UTF8, true))
        {
            binaryWriter.Write((byte)0x0);
            binaryWriter.Write(message.Length);
            binaryWriter.Write(message);
        }

        messageToSend.Seek(0, SeekOrigin.Begin);

        while (messageToSend.Position != messageToSend.Length)
        {
            var buffer = new byte[32];
            messageToSend.Read(buffer, 0, buffer.Length);
            this.device.Write(buffer);
        }
    }

    public void ReceivePacket(CancellationToken ct)
    {
        while (true)
        {
            try
            {
                ct.ThrowIfCancellationRequested();
                var buffer = this.device.ReadTimeout(32, 500);
                var bytesRead = buffer.Length;

                if (buffer.Length == -1)
                {
                    return;
                }

                if (buffer.Length == 0)
                {
                    continue;
                }

                var message = new MemoryStream();
                var length = BitConverter.ToInt32(buffer[..4]);

                if (length == 0)
                {
                    Thread.Sleep(100);
                    continue;
                }

                bytesRead -= sizeof(int);
                message.Write(buffer[4..]);
                while (bytesRead < length)
                {
                    ct.ThrowIfCancellationRequested();
                    var messageBuffer = this.device.Read(32);
                    message.Write(messageBuffer);
                    bytesRead += messageBuffer.Length;
                }

                Debug.WriteLine(string.Join(", ", message.ToArray()));

                message.Dispose();
            }
            catch (HidApi.HidException ex)
            {
                return;
            }
        }
    }

    public void Dispose()
    {
        this.readCancellationTokenSource.Cancel();
        this.device.Dispose();
    }
}

public abstract class HidPacket
{
    public abstract HidCommand Command { get; }

    public byte[] Serialize()
    {
        var message = new MemoryStream();
        message.WriteByte((byte)this.Command);
        var result = this.SerializeInternal(message);

        message.Dispose();
        return result;
    }

    protected abstract byte[] SerializeInternal(MemoryStream message);
}

public class SetHsvColorCommand : HidPacket
{
    public struct Color
    {
        public byte H { get; set; }

        public byte S { get; set; }

        public byte V { get; set; }

        public Color(byte h, byte s, byte v)
        {
            this.H = h;
            this.S = s;
            this.V = v;
        }

        public static Color FromRgb(byte r, byte g, byte b)
        {
            double delta, min;
            double h = 0, s, v;

            min = Math.Min(Math.Min(r, g), b);
            v = Math.Max(Math.Max(r, g), b);
            delta = v - min;

            s = v == 0.0 ? 0 : delta / v;

            if (s == 0)
            {
                h = 0.0;
            }
            else
            {
                if (r == v)
                {
                    h = (g - b) / delta;
                }
                else if (g == v)
                {
                    h = 2 + ((b - r) / delta);
                }
                else if (b == v)
                {
                    h = 4 + ((r - g) / delta);
                }

                h *= 60;

                if (h < 0.0)
                {
                    h += 360;
                }
            }

            return new Color((byte)(h / 360 * 255), (byte)(s * 255), (byte)v);
        }
    }

    public override HidCommand Command => HidCommand.SetHsvColor;

    public Color HsvColor { get; set; }

    protected override byte[] SerializeInternal(MemoryStream message)
    {
        message.WriteByte(this.HsvColor.H);
        message.WriteByte(this.HsvColor.S);
        message.WriteByte(this.HsvColor.V);

        return message.ToArray();
    }
}

public class SetRgbEffectCommand : HidPacket
{
    public enum Effects
    {
        None = 0,
        SolidColor = 1,                 // Static single hue, no speed support
        AlphasMods = 2,                 // Static dual hue, speed is hue for secondary hue
        GradientUpDown = 3,             // Static gradient top to bottom, speed controls how much gradient changes
        GradientLeftRight = 4,          // Static gradient left to right, speed controls how much gradient changes
        Breathing = 5,                  // Single hue brightness cycling animation
        BandSaturation = 6,             // Single hue band fading saturation scrolling left to right
        BandValue = 7,                  // Single hue band fading brightness scrolling left to right
        BandPinwheelSaturation = 8,     // Single hue 3 blade spinning pinwheel fades saturation
        BandPinwheelValue = 9,          // Single hue 3 blade spinning pinwheel fades brightness
        BandSpiralSaturation = 10,      // Single hue spinning spiral fades saturation
        BandSpiralValue = 11,           // Single hue spinning spiral fades brightness
        CycleAll = 12,                  // Full keyboard solid hue cycling through full gradient
        CycleLeftRight = 13,            // Full gradient scrolling left to right
        CycleUpDown = 14,               // Full gradient scrolling top to bottom
        CycleOutIn = 15,                // Full gradient scrolling out to in
        CycleOutInDual = 16,            // Full dual gradients scrolling out to in
        RainbowMovingChevron = 17,      // Full gradient Chevron shapped scrolling left to right
        CyclePinwheel = 18,             // Full gradient spinning pinwheel around center of keyboard
        CycleSpiral = 19,               // Full gradient spinning spiral around center of keyboard
        DualBeacon = 20,                // Full gradient spinning around center of keyboard
        RainbowBeacon = 21,             // Full tighter gradient spinning around center of keyboard
        RainbowPinwheels = 22,          // Full dual gradients spinning two halfs of keyboard
        Raindrops = 23,                 // Randomly changes a single key's hue
        JellybeanRaindrops = 24,        // Randomly changes a single key's hue and saturation
        HueBreathing = 25,              // Hue shifts up a slight ammount at the same time, then shifts back
        HuePendulum = 26,               // Hue shifts up a slight ammount in a wave to the right, then back to the left
        HueWave = 27,                   // Hue shifts up a slight ammount and then back down in a wave to the right
        PixelFractal = 28,              // Single hue fractal filled keys pulsing horizontally out to edges
        PixelFlow = 29,                 // Pulsing RGB flow along LED wiring with random hues
        PixelRain = 30,                 // Randomly light keys with random hues
        // Framebuffer set
        TypingHeatmap = 31,             // How hot is your WPM!
        DigitalRain = 32,               // That famous computer simulation
        // Keypresses or Release
        SolidReactiveSimple = 33,       // Pulses keys hit to hue & value then fades value out
        SolidReactive = 34,             // Static single hue, pulses keys hit to shifted hue then fades to current hue
        SolidReactiveWide = 35,         // Hue & value pulse near a single key hit then fades value out
        SolidReactiveMultiwide = 36,    // Hue & value pulse near multiple key hits then fades value out
        SolidReactiveCross = 37,        // Hue & value pulse the same column and row of a single key hit then fades value out
        SolidReactiveMultiCross = 38,   // Hue & value pulse the same column and row of multiple key hits then fades value out
        SolidReactiveNexus = 39,        // Hue & value pulse away on the same column and row of a single key hit then fades value out
        SolidReactiveMultinexus = 40,   // Hue & value pulse away on the same column and row of multiple key hits then fades value out
        Splash = 41,                    // Full gradient & value pulse away from a single key hit then fades value out
        Multisplash = 42,               // Full gradient & value pulse away from multiple key hits then fades value out
        SolidSplash = 43,               // Hue & value pulse away from a single key hit then fades value out
        SolidMultisplash = 44,          // Hue & value pulse away from multiple key hits then fades value out
    }

    public Effects Effect { get; set; }

    public override HidCommand Command => HidCommand.SetRgbEffect;

    protected override byte[] SerializeInternal(MemoryStream message)
    {
        message.WriteByte((byte)this.Effect);

        return message.ToArray();
    }
}

public enum HidCommand
{
    SetHsvColor = 0,
    SetRgbEffect = 1,
}