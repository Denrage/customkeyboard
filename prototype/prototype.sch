EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:USB_C_Plug P?
U 1 1 611485C9
P 1150 5350
F 0 "P?" H 1257 6617 50  0000 C CNN
F 1 "USB_C_Plug" H 1257 6526 50  0000 C CNN
F 2 "" H 1300 5350 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 1300 5350 50  0001 C CNN
	1    1150 5350
	1    0    0    -1  
$EndComp
$Comp
L MCU_ST_STM32F3:STM32F303VCTx U?
U 1 1 6115BE99
P 5500 3900
F 0 "U?" H 5500 1011 50  0000 C CNN
F 1 "STM32F303VCTx" H 5500 920 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_14x14mm_P0.5mm" H 4900 1300 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00058181.pdf" H 5500 3900 50  0001 C CNN
	1    5500 3900
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U?
U 1 1 61163108
P 1200 1050
F 0 "U?" H 1200 1292 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 1200 1201 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 1200 1250 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 1300 800 50  0001 C CNN
	1    1200 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6116A39B
P 1200 1400
F 0 "#PWR?" H 1200 1150 50  0001 C CNN
F 1 "GND" H 1205 1227 50  0000 C CNN
F 2 "" H 1200 1400 50  0001 C CNN
F 3 "" H 1200 1400 50  0001 C CNN
	1    1200 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6116B331
P 600 950
F 0 "#PWR?" H 600 800 50  0001 C CNN
F 1 "+5V" H 615 1123 50  0000 C CNN
F 2 "" H 600 950 50  0001 C CNN
F 3 "" H 600 950 50  0001 C CNN
	1    600  950 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6116C543
P 1750 900
F 0 "#PWR?" H 1750 750 50  0001 C CNN
F 1 "+3.3V" H 1765 1073 50  0000 C CNN
F 2 "" H 1750 900 50  0001 C CNN
F 3 "" H 1750 900 50  0001 C CNN
	1    1750 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1050 1750 1050
Wire Wire Line
	1750 1050 1750 900 
Wire Wire Line
	1200 1350 1200 1400
$Comp
L Device:C_Small C?
U 1 1 6116E249
P 600 1200
F 0 "C?" H 692 1246 50  0000 L CNN
F 1 "100nF" H 692 1155 50  0000 L CNN
F 2 "" H 600 1200 50  0001 C CNN
F 3 "~" H 600 1200 50  0001 C CNN
	1    600  1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6116FCD3
P 1750 1200
F 0 "C?" H 1842 1246 50  0000 L CNN
F 1 "10uF" H 1842 1155 50  0000 L CNN
F 2 "" H 1750 1200 50  0001 C CNN
F 3 "~" H 1750 1200 50  0001 C CNN
	1    1750 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1050 1750 1100
Connection ~ 1750 1050
Wire Wire Line
	1750 1300 1750 1350
Wire Wire Line
	1750 1350 1200 1350
Connection ~ 1200 1350
Wire Wire Line
	600  1350 600  1300
Wire Wire Line
	600  950  600  1050
Connection ~ 600  1050
Wire Wire Line
	600  1050 600  1100
Wire Wire Line
	600  1050 900  1050
Wire Wire Line
	600  1350 1200 1350
Wire Wire Line
	5300 1200 5400 1200
Connection ~ 5400 1200
Wire Wire Line
	5400 1200 5500 1200
Connection ~ 5500 1200
Wire Wire Line
	5500 1200 5600 1200
Connection ~ 5600 1200
Wire Wire Line
	5600 1200 5700 1200
Connection ~ 5700 1200
Wire Wire Line
	5700 1200 5800 1200
Wire Wire Line
	5500 1200 5500 1050
Wire Wire Line
	5400 6700 5500 6700
Connection ~ 5500 6700
Wire Wire Line
	5500 6700 5600 6700
Connection ~ 5600 6700
Wire Wire Line
	5600 6700 5700 6700
$Comp
L power:GND #PWR?
U 1 1 61173D62
P 5050 6800
F 0 "#PWR?" H 5050 6550 50  0001 C CNN
F 1 "GND" H 5055 6627 50  0000 C CNN
F 2 "" H 5050 6800 50  0001 C CNN
F 3 "" H 5050 6800 50  0001 C CNN
	1    5050 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 6700 5050 6700
Wire Wire Line
	5050 6700 5050 6800
Connection ~ 5400 6700
$Comp
L power:+3.3V #PWR?
U 1 1 61172573
P 5500 1050
F 0 "#PWR?" H 5500 900 50  0001 C CNN
F 1 "+3.3V" H 5515 1223 50  0000 C CNN
F 2 "" H 5500 1050 50  0001 C CNN
F 3 "" H 5500 1050 50  0001 C CNN
	1    5500 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61177791
P 2100 1200
F 0 "C?" H 2192 1246 50  0000 L CNN
F 1 "100nF" H 2192 1155 50  0000 L CNN
F 2 "" H 2100 1200 50  0001 C CNN
F 3 "~" H 2100 1200 50  0001 C CNN
	1    2100 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61178702
P 2500 1200
F 0 "C?" H 2592 1246 50  0000 L CNN
F 1 "100nF" H 2592 1155 50  0000 L CNN
F 2 "" H 2500 1200 50  0001 C CNN
F 3 "~" H 2500 1200 50  0001 C CNN
	1    2500 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61178BAD
P 2950 1200
F 0 "C?" H 3042 1246 50  0000 L CNN
F 1 "100nF" H 3042 1155 50  0000 L CNN
F 2 "" H 2950 1200 50  0001 C CNN
F 3 "~" H 2950 1200 50  0001 C CNN
	1    2950 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 611791E5
P 4150 1200
F 0 "C?" H 4242 1246 50  0000 L CNN
F 1 "100nF" H 4242 1155 50  0000 L CNN
F 2 "" H 4150 1200 50  0001 C CNN
F 3 "~" H 4150 1200 50  0001 C CNN
	1    4150 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61179529
P 3750 1200
F 0 "C?" H 3842 1246 50  0000 L CNN
F 1 "100nF" H 3842 1155 50  0000 L CNN
F 2 "" H 3750 1200 50  0001 C CNN
F 3 "~" H 3750 1200 50  0001 C CNN
	1    3750 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61179766
P 3350 1200
F 0 "C?" H 3442 1246 50  0000 L CNN
F 1 "100nF" H 3442 1155 50  0000 L CNN
F 2 "" H 3350 1200 50  0001 C CNN
F 3 "~" H 3350 1200 50  0001 C CNN
	1    3350 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1300 2100 1300
Connection ~ 1750 1300
Connection ~ 2100 1300
Wire Wire Line
	2100 1300 2500 1300
Connection ~ 2500 1300
Wire Wire Line
	2500 1300 2950 1300
Connection ~ 2950 1300
Wire Wire Line
	2950 1300 3350 1300
Connection ~ 3350 1300
Wire Wire Line
	3350 1300 3750 1300
Connection ~ 3750 1300
Wire Wire Line
	3750 1300 4150 1300
Wire Wire Line
	2100 1100 2500 1100
Connection ~ 2500 1100
Wire Wire Line
	2500 1100 2950 1100
Connection ~ 2950 1100
Wire Wire Line
	2950 1100 3350 1100
Connection ~ 3350 1100
Wire Wire Line
	3350 1100 3750 1100
Connection ~ 3750 1100
Wire Wire Line
	3750 1100 4150 1100
Wire Wire Line
	2100 1100 1750 1100
Connection ~ 2100 1100
Connection ~ 1750 1100
Text Notes 2550 1050 0    50   ~ 0
These capacitors will be placed \nnext to their corresponding \npin on the pcb
Text GLabel 1900 4850 2    50   Input ~ 0
D-
Text GLabel 1900 5050 2    50   Input ~ 0
D+
Wire Wire Line
	1750 4850 1900 4850
Wire Wire Line
	1750 5050 1900 5050
Text GLabel 6400 2600 2    50   Input ~ 0
D-
Text GLabel 6400 2700 2    50   Input ~ 0
D+
Wire Wire Line
	6300 2600 6400 2600
Wire Wire Line
	6300 2700 6400 2700
$Comp
L power:+5V #PWR?
U 1 1 6118F6B2
P 1900 4350
F 0 "#PWR?" H 1900 4200 50  0001 C CNN
F 1 "+5V" H 1915 4523 50  0000 C CNN
F 2 "" H 1900 4350 50  0001 C CNN
F 3 "" H 1900 4350 50  0001 C CNN
	1    1900 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 4350 1900 4350
$EndSCHEMATC
