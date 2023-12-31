EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3500 1000 650  1350
U 63CCADBE
F0 "Key Matrix" 50
F1 "KeyMatrix.sch" 50
F2 "DOUT" I R 4150 1100 50 
F3 "COUT" I R 4150 1200 50 
F4 "COL1" I L 3500 1600 50 
F5 "DIN" I L 3500 1100 50 
F6 "CIN" I L 3500 1200 50 
F7 "VCC" I L 3500 2200 50 
F8 "ROW1" I L 3500 1700 50 
F9 "COL2" I L 3500 1500 50 
F10 "COL3" I L 3500 1400 50 
F11 "COL4" I L 3500 1300 50 
F12 "ROW3" I L 3500 1900 50 
F13 "ROW5" I L 3500 2100 50 
F14 "ROW2" I L 3500 1800 50 
F15 "ROW4" I L 3500 2000 50 
$EndSheet
$Comp
L Connector_Generic:Conn_01x13 J2
U 1 1 640667B5
P 3050 1700
F 0 "J2" H 3130 1742 50  0000 L CNN
F 1 "Conn_01x13" H 3130 1651 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x13_P2.54mm_Vertical" H 3050 1700 50  0001 C CNN
F 3 "~" H 3050 1700 50  0001 C CNN
	1    3050 1700
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 640701B7
P 4350 1100
F 0 "J1" H 4430 1092 50  0000 L CNN
F 1 "Conn_01x02" H 4430 1001 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4350 1100 50  0001 C CNN
F 3 "~" H 4350 1100 50  0001 C CNN
	1    4350 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 1100 3500 1100
Wire Wire Line
	3250 1200 3500 1200
Wire Wire Line
	3250 1300 3500 1300
Wire Wire Line
	3250 1400 3500 1400
Wire Wire Line
	3250 1500 3500 1500
Wire Wire Line
	3250 1600 3500 1600
Wire Wire Line
	3250 1700 3500 1700
Wire Wire Line
	3250 1800 3500 1800
Wire Wire Line
	3250 1900 3500 1900
Wire Wire Line
	3250 2000 3500 2000
Wire Wire Line
	3250 2100 3500 2100
Wire Wire Line
	3250 2200 3500 2200
$Comp
L power:GND #PWR0101
U 1 1 63DE42CC
P 3250 2300
F 0 "#PWR0101" H 3250 2050 50  0001 C CNN
F 1 "GND" H 3255 2127 50  0000 C CNN
F 2 "" H 3250 2300 50  0001 C CNN
F 3 "" H 3250 2300 50  0001 C CNN
	1    3250 2300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
