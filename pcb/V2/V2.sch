EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Franz-mod
LIBS:V2-cache
EELAYER 25 0
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
L CONN_01X02 J1
U 1 1 59C951E1
P 1300 1350
F 0 "J1" H 1300 1500 50  0000 C CNN
F 1 "Bat" V 1400 1350 50  0000 C CNN
F 2 "" H 1300 1350 50  0001 C CNN
F 3 "" H 1300 1350 50  0001 C CNN
	1    1300 1350
	0    -1   -1   0   
$EndComp
$Comp
L Ads1115-Mod M2
U 1 1 59C95345
P 3650 2750
F 0 "M2" H 4100 2950 60  0000 C CNN
F 1 "Ads1115-Mod" V 4200 3400 60  0000 C CNN
F 2 "" H 3650 2750 60  0001 C CNN
F 3 "" H 3650 2750 60  0001 C CNN
	1    3650 2750
	1    0    0    -1  
$EndComp
$Comp
L ACS712-5A M1
U 1 1 59C95535
P 2100 2100
F 0 "M1" H 2450 2700 60  0000 C CNN
F 1 "ACS712-5A" H 2550 2850 60  0000 C CNN
F 2 "" H 2100 2100 60  0001 C CNN
F 3 "" H 2100 2100 60  0001 C CNN
	1    2100 2100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 J3
U 1 1 59C95F94
P 5450 650
F 0 "J3" H 5450 900 50  0000 C CNN
F 1 "toFC" V 5550 650 50  0000 C CNN
F 2 "" H 5450 650 50  0001 C CNN
F 3 "" H 5450 650 50  0001 C CNN
	1    5450 650 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 59C960B8
P 5300 850
F 0 "#PWR01" H 5300 600 50  0001 C CNN
F 1 "GND" H 5300 700 50  0000 C CNN
F 2 "" H 5300 850 50  0001 C CNN
F 3 "" H 5300 850 50  0001 C CNN
	1    5300 850 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR02
U 1 1 59C9620D
P 5400 850
F 0 "#PWR02" H 5400 700 50  0001 C CNN
F 1 "+5V" H 5400 990 50  0000 C CNN
F 2 "" H 5400 850 50  0001 C CNN
F 3 "" H 5400 850 50  0001 C CNN
	1    5400 850 
	-1   0    0    1   
$EndComp
Wire Wire Line
	5500 850  5500 1450
Wire Wire Line
	5500 1450 5250 1450
Wire Wire Line
	5600 850  5600 1600
Wire Wire Line
	5600 1600 5250 1600
Text Label 5300 1450 0    60   ~ 0
SCL
Text Label 5300 1600 0    60   ~ 0
SDA
$Comp
L GND #PWR03
U 1 1 59C96371
P 1350 1550
F 0 "#PWR03" H 1350 1300 50  0001 C CNN
F 1 "GND" H 1350 1400 50  0000 C CNN
F 2 "" H 1350 1550 50  0001 C CNN
F 3 "" H 1350 1550 50  0001 C CNN
	1    1350 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1550 1250 1750
Wire Wire Line
	1250 1750 1700 1750
Wire Wire Line
	1700 1900 1250 1900
Wire Wire Line
	1250 1900 1250 4950
Wire Wire Line
	3650 2150 2950 2150
Wire Wire Line
	2950 2150 2950 1750
Wire Wire Line
	2950 1750 2650 1750
$Comp
L +5V #PWR04
U 1 1 59C963CC
P 2650 1850
F 0 "#PWR04" H 2650 1700 50  0001 C CNN
F 1 "+5V" H 2650 1990 50  0000 C CNN
F 2 "" H 2650 1850 50  0001 C CNN
F 3 "" H 2650 1850 50  0001 C CNN
	1    2650 1850
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR05
U 1 1 59C963ED
P 3650 1450
F 0 "#PWR05" H 3650 1300 50  0001 C CNN
F 1 "+5V" V 3650 1590 50  0000 C CNN
F 2 "" H 3650 1450 50  0001 C CNN
F 3 "" H 3650 1450 50  0001 C CNN
	1    3650 1450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR06
U 1 1 59C96407
P 3650 1550
F 0 "#PWR06" H 3650 1300 50  0001 C CNN
F 1 "GND" H 3650 1400 50  0000 C CNN
F 2 "" H 3650 1550 50  0001 C CNN
F 3 "" H 3650 1550 50  0001 C CNN
	1    3650 1550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR07
U 1 1 59C964BC
P 2650 1950
F 0 "#PWR07" H 2650 1700 50  0001 C CNN
F 1 "GND" H 2650 1800 50  0000 C CNN
F 2 "" H 2650 1950 50  0001 C CNN
F 3 "" H 2650 1950 50  0001 C CNN
	1    2650 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3650 2050 3050 2050
Wire Wire Line
	3050 2050 3050 1600
Wire Wire Line
	3050 1600 1650 1600
Wire Wire Line
	1650 1600 1650 1750
Connection ~ 1650 1750
$Comp
L R R2
U 1 1 59C967F7
P 3100 2700
F 0 "R2" V 3180 2700 50  0000 C CNN
F 1 "10k" V 3100 2700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3030 2700 50  0001 C CNN
F 3 "" H 3100 2700 50  0001 C CNN
F 4 "Value" H 3100 2700 60  0001 C CNN "Fieldname"
	1    3100 2700
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 59C96884
P 2850 2700
F 0 "R1" V 2930 2700 50  0000 C CNN
F 1 "10k" V 2850 2700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2780 2700 50  0001 C CNN
F 3 "" H 2850 2700 50  0001 C CNN
	1    2850 2700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J2
U 1 1 59C968C4
P 2950 3150
F 0 "J2" H 2950 3300 50  0000 C CNN
F 1 "TSens+" V 3050 3150 50  0000 C CNN
F 2 "" H 2950 3150 50  0001 C CNN
F 3 "" H 2950 3150 50  0001 C CNN
F 4 "Value" H 2950 3150 60  0001 C CNN "Fieldname"
	1    2950 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 2950 3350 2950
Wire Wire Line
	3100 2950 3100 2850
Wire Wire Line
	2900 2950 2850 2950
Wire Wire Line
	2850 2950 2850 2850
$Comp
L +5V #PWR08
U 1 1 59C969EB
P 2850 2550
F 0 "#PWR08" H 2850 2400 50  0001 C CNN
F 1 "+5V" V 2850 2690 50  0000 C CNN
F 2 "" H 2850 2550 50  0001 C CNN
F 3 "" H 2850 2550 50  0001 C CNN
	1    2850 2550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 59C96A2E
P 3100 2550
F 0 "#PWR09" H 3100 2400 50  0001 C CNN
F 1 "+5V" V 3100 2690 50  0000 C CNN
F 2 "" H 3100 2550 50  0001 C CNN
F 3 "" H 3100 2550 50  0001 C CNN
	1    3100 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2250 3300 2250
Wire Wire Line
	3300 2250 3300 2900
Wire Wire Line
	3300 2900 2850 2900
Connection ~ 2850 2900
Wire Wire Line
	3650 2350 3350 2350
Wire Wire Line
	3350 2350 3350 2950
Connection ~ 3100 2950
Wire Wire Line
	3250 1650 3650 1650
Wire Wire Line
	3650 1750 3250 1750
Text Label 3350 1750 0    60   ~ 0
SDA
Text Label 3350 1650 0    60   ~ 0
SCL
$Comp
L MT3608 P1
U 1 1 59C96CF8
P 2800 5300
F 0 "P1" H 3000 5300 60  0000 C CNN
F 1 "MT3608" H 3000 5550 60  0000 C CNN
F 2 "Franz-Mods:MT3608" H 2800 5300 60  0001 C CNN
F 3 "" H 2800 5300 60  0001 C CNN
	1    2800 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 4950 2500 4950
$Comp
L +5V #PWR010
U 1 1 59C96DA0
P 3550 4950
F 0 "#PWR010" H 3550 4800 50  0001 C CNN
F 1 "+5V" V 3550 5090 50  0000 C CNN
F 2 "" H 3550 4950 50  0001 C CNN
F 3 "" H 3550 4950 50  0001 C CNN
	1    3550 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 59C96DF3
P 3550 5150
F 0 "#PWR011" H 3550 4900 50  0001 C CNN
F 1 "GND" H 3550 5000 50  0000 C CNN
F 2 "" H 3550 5150 50  0001 C CNN
F 3 "" H 3550 5150 50  0001 C CNN
	1    3550 5150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 59C96E72
P 2500 5150
F 0 "#PWR012" H 2500 4900 50  0001 C CNN
F 1 "GND" H 2500 5000 50  0000 C CNN
F 2 "" H 2500 5150 50  0001 C CNN
F 3 "" H 2500 5150 50  0001 C CNN
	1    2500 5150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J4
U 1 1 59C96FAF
P 2000 4250
F 0 "J4" H 2000 4400 50  0000 C CNN
F 1 "Solar" V 2100 4250 50  0000 C CNN
F 2 "" H 2000 4250 50  0001 C CNN
F 3 "" H 2000 4250 50  0001 C CNN
	1    2000 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1950 4450 1950 4950
Connection ~ 1950 4950
$Comp
L GND #PWR013
U 1 1 59C9712C
P 2050 4450
F 0 "#PWR013" H 2050 4200 50  0001 C CNN
F 1 "GND" H 2050 4300 50  0000 C CNN
F 2 "" H 2050 4450 50  0001 C CNN
F 3 "" H 2050 4450 50  0001 C CNN
	1    2050 4450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J5
U 1 1 59C973C1
P 2950 3600
F 0 "J5" H 2950 3750 50  0000 C CNN
F 1 "TSens-" V 3050 3600 50  0000 C CNN
F 2 "" H 2950 3600 50  0001 C CNN
F 3 "" H 2950 3600 50  0001 C CNN
F 4 "Value" H 2950 3600 60  0001 C CNN "Fieldname"
	1    2950 3600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR014
U 1 1 59C974A3
P 2900 3800
F 0 "#PWR014" H 2900 3550 50  0001 C CNN
F 1 "GND" H 2900 3650 50  0000 C CNN
F 2 "" H 2900 3800 50  0001 C CNN
F 3 "" H 2900 3800 50  0001 C CNN
	1    2900 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 59C974CF
P 3000 3800
F 0 "#PWR015" H 3000 3550 50  0001 C CNN
F 1 "GND" H 3000 3650 50  0000 C CNN
F 2 "" H 3000 3800 50  0001 C CNN
F 3 "" H 3000 3800 50  0001 C CNN
	1    3000 3800
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 59C97C55
P 6950 4450
F 0 "R4" V 7030 4450 50  0000 C CNN
F 1 "100k" V 6950 4450 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6880 4450 50  0001 C CNN
F 3 "" H 6950 4450 50  0001 C CNN
	1    6950 4450
	-1   0    0    1   
$EndComp
$Comp
L AO4801A T1
U 1 1 59C97CE6
P 8000 4500
F 0 "T1" H 7950 4150 60  0000 C CNN
F 1 "AO4801A" H 7950 4300 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 8000 4500 60  0001 C CNN
F 3 "" H 8000 4500 60  0001 C CNN
F 4 "Value" H 8000 4500 60  0001 C CNN "Fieldname"
	1    8000 4500
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 59C97E11
P 7250 4650
F 0 "R5" V 7330 4650 50  0000 C CNN
F 1 "100k" V 7250 4650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7180 4650 50  0001 C CNN
F 3 "" H 7250 4650 50  0001 C CNN
	1    7250 4650
	-1   0    0    1   
$EndComp
Wire Wire Line
	7600 4300 6950 4300
Wire Wire Line
	6950 4600 7100 4600
Wire Wire Line
	7100 4400 7100 4700
Wire Wire Line
	7100 4400 7600 4400
Wire Wire Line
	7250 4500 7600 4500
Wire Wire Line
	7250 4800 7700 4800
Wire Wire Line
	7500 4800 7500 4600
Wire Wire Line
	7500 4600 7600 4600
Wire Wire Line
	7250 4100 7250 4500
Connection ~ 7250 4300
Wire Wire Line
	7250 4100 6400 4100
Wire Wire Line
	6400 4100 6400 4600
Wire Wire Line
	6400 4600 2250 4600
Wire Wire Line
	2250 4600 2250 4950
Connection ~ 2250 4950
Wire Wire Line
	7700 4800 7700 5200
Connection ~ 7500 4800
Wire Wire Line
	6800 5300 6800 4700
Wire Wire Line
	6800 4700 7100 4700
Connection ~ 7100 4600
$Comp
L GND #PWR016
U 1 1 59C9837B
P 7700 5600
F 0 "#PWR016" H 7700 5350 50  0001 C CNN
F 1 "GND" H 7700 5450 50  0000 C CNN
F 2 "" H 7700 5600 50  0001 C CNN
F 3 "" H 7700 5600 50  0001 C CNN
	1    7700 5600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 59C98416
P 6800 5700
F 0 "#PWR017" H 6800 5450 50  0001 C CNN
F 1 "GND" H 6800 5550 50  0000 C CNN
F 2 "" H 6800 5700 50  0001 C CNN
F 3 "" H 6800 5700 50  0001 C CNN
	1    6800 5700
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 59C98451
P 7250 5400
F 0 "R6" V 7330 5400 50  0000 C CNN
F 1 "1k" V 7250 5400 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7180 5400 50  0001 C CNN
F 3 "" H 7250 5400 50  0001 C CNN
	1    7250 5400
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 59C984AE
P 6350 5500
F 0 "R3" V 6430 5500 50  0000 C CNN
F 1 "1k" V 6350 5500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6280 5500 50  0001 C CNN
F 3 "" H 6350 5500 50  0001 C CNN
	1    6350 5500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7100 5150 7100 5400
Wire Wire Line
	5750 5150 7100 5150
Wire Wire Line
	6200 5500 5750 5500
Text Label 5950 5150 0    60   ~ 0
SW0
Text Label 5900 5500 0    60   ~ 0
SW1
$Comp
L BC817-40 Q4
U 1 1 59C990D4
P 7600 5400
F 0 "Q4" H 7800 5475 50  0000 L CNN
F 1 "BC817-40" H 7800 5400 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7800 5325 50  0001 L CIN
F 3 "" H 7600 5400 50  0001 L CNN
	1    7600 5400
	1    0    0    -1  
$EndComp
$Comp
L BC817-40 Q3
U 1 1 59C99174
P 6700 5500
F 0 "Q3" H 6900 5575 50  0000 L CNN
F 1 "BC817-40" H 6900 5500 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6900 5425 50  0001 L CIN
F 3 "" H 6700 5500 50  0001 L CNN
	1    6700 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 4300 8750 4300
Wire Wire Line
	8750 4100 8750 4400
Wire Wire Line
	8750 4400 8350 4400
Wire Wire Line
	8350 4500 8750 4500
Wire Wire Line
	8750 4500 8750 4650
Wire Wire Line
	8750 4600 8350 4600
$Comp
L R R8
U 1 1 59C99C0F
P 5100 6200
F 0 "R8" V 5180 6200 50  0000 C CNN
F 1 "100k" V 5100 6200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5030 6200 50  0001 C CNN
F 3 "" H 5100 6200 50  0001 C CNN
	1    5100 6200
	-1   0    0    1   
$EndComp
$Comp
L AO4801A T2
U 1 1 59C99C16
P 6150 6250
F 0 "T2" H 6100 5900 60  0000 C CNN
F 1 "AO4801A" H 6100 6050 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 6150 6250 60  0001 C CNN
F 3 "" H 6150 6250 60  0001 C CNN
F 4 "Value" H 6150 6250 60  0001 C CNN "Fieldname"
	1    6150 6250
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 59C99C1C
P 5400 6400
F 0 "R9" V 5480 6400 50  0000 C CNN
F 1 "100k" V 5400 6400 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5330 6400 50  0001 C CNN
F 3 "" H 5400 6400 50  0001 C CNN
	1    5400 6400
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 6050 5100 6050
Wire Wire Line
	5100 6350 5250 6350
Wire Wire Line
	5250 6150 5250 6450
Wire Wire Line
	5250 6150 5750 6150
Wire Wire Line
	5400 6250 5750 6250
Wire Wire Line
	5400 6550 5850 6550
Wire Wire Line
	5650 6550 5650 6350
Wire Wire Line
	5650 6350 5750 6350
Wire Wire Line
	5400 5850 5400 6250
Connection ~ 5400 6050
Wire Wire Line
	5400 5850 4550 5850
Wire Wire Line
	5850 6550 5850 6950
Connection ~ 5650 6550
Wire Wire Line
	4950 7050 4950 6450
Wire Wire Line
	4950 6450 5250 6450
Connection ~ 5250 6350
$Comp
L GND #PWR018
U 1 1 59C99C34
P 5850 7350
F 0 "#PWR018" H 5850 7100 50  0001 C CNN
F 1 "GND" H 5850 7200 50  0000 C CNN
F 2 "" H 5850 7350 50  0001 C CNN
F 3 "" H 5850 7350 50  0001 C CNN
	1    5850 7350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 59C99C3A
P 4950 7450
F 0 "#PWR019" H 4950 7200 50  0001 C CNN
F 1 "GND" H 4950 7300 50  0000 C CNN
F 2 "" H 4950 7450 50  0001 C CNN
F 3 "" H 4950 7450 50  0001 C CNN
	1    4950 7450
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 59C99C40
P 5400 7150
F 0 "R10" V 5480 7150 50  0000 C CNN
F 1 "1k" V 5400 7150 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5330 7150 50  0001 C CNN
F 3 "" H 5400 7150 50  0001 C CNN
	1    5400 7150
	0    -1   -1   0   
$EndComp
$Comp
L R R7
U 1 1 59C99C46
P 4500 7250
F 0 "R7" V 4580 7250 50  0000 C CNN
F 1 "1k" V 4500 7250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 7250 50  0001 C CNN
F 3 "" H 4500 7250 50  0001 C CNN
	1    4500 7250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5250 6900 5250 7150
Wire Wire Line
	3900 6900 5250 6900
Wire Wire Line
	4350 7250 3900 7250
Text Label 4100 6900 0    60   ~ 0
SW2
Text Label 4050 7250 0    60   ~ 0
SW3
$Comp
L BC817-40 Q2
U 1 1 59C99C51
P 5750 7150
F 0 "Q2" H 5950 7225 50  0000 L CNN
F 1 "BC817-40" H 5950 7150 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5950 7075 50  0001 L CIN
F 3 "" H 5750 7150 50  0001 L CNN
	1    5750 7150
	1    0    0    -1  
$EndComp
$Comp
L BC817-40 Q1
U 1 1 59C99C57
P 4850 7250
F 0 "Q1" H 5050 7325 50  0000 L CNN
F 1 "BC817-40" H 5050 7250 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5050 7175 50  0001 L CIN
F 3 "" H 4850 7250 50  0001 L CNN
	1    4850 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 6050 6900 6050
Wire Wire Line
	6900 5950 6900 6150
Wire Wire Line
	6900 6150 6500 6150
Wire Wire Line
	6500 6250 6900 6250
Wire Wire Line
	6900 6250 6900 6350
Wire Wire Line
	6500 6350 7200 6350
Wire Wire Line
	4550 5850 4550 4600
Connection ~ 4550 4600
$Comp
L MT3608 P2
U 1 1 59C9A235
P 9800 4450
F 0 "P2" H 10000 4450 60  0000 C CNN
F 1 "MT3608" H 10000 4700 60  0000 C CNN
F 2 "Franz-Mods:MT3608" H 9800 4450 60  0001 C CNN
F 3 "" H 9800 4450 60  0001 C CNN
	1    9800 4450
	1    0    0    -1  
$EndComp
$Comp
L MT3608 P3
U 1 1 59C9A38D
P 9800 5000
F 0 "P3" H 10000 5000 60  0000 C CNN
F 1 "MT3608" H 10000 5250 60  0000 C CNN
F 2 "Franz-Mods:MT3608" H 9800 5000 60  0001 C CNN
F 3 "" H 9800 5000 60  0001 C CNN
	1    9800 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 4100 8750 4100
Connection ~ 8750 4300
Wire Wire Line
	8750 4650 9500 4650
Connection ~ 8750 4600
$Comp
L GND #PWR020
U 1 1 59C9A500
P 9500 4300
F 0 "#PWR020" H 9500 4050 50  0001 C CNN
F 1 "GND" H 9500 4150 50  0000 C CNN
F 2 "" H 9500 4300 50  0001 C CNN
F 3 "" H 9500 4300 50  0001 C CNN
	1    9500 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 59C9A55C
P 9500 4850
F 0 "#PWR021" H 9500 4600 50  0001 C CNN
F 1 "GND" H 9500 4700 50  0000 C CNN
F 2 "" H 9500 4850 50  0001 C CNN
F 3 "" H 9500 4850 50  0001 C CNN
	1    9500 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 59C9A5B8
P 10550 4850
F 0 "#PWR022" H 10550 4600 50  0001 C CNN
F 1 "GND" H 10550 4700 50  0000 C CNN
F 2 "" H 10550 4850 50  0001 C CNN
F 3 "" H 10550 4850 50  0001 C CNN
	1    10550 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 59C9A66F
P 10550 4300
F 0 "#PWR023" H 10550 4050 50  0001 C CNN
F 1 "GND" H 10550 4150 50  0000 C CNN
F 2 "" H 10550 4300 50  0001 C CNN
F 3 "" H 10550 4300 50  0001 C CNN
	1    10550 4300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J13
U 1 1 59C9A810
P 10950 4150
F 0 "J13" H 10950 4300 50  0000 C CNN
F 1 "ServoV" V 11050 4150 50  0000 C CNN
F 2 "" H 10950 4150 50  0001 C CNN
F 3 "" H 10950 4150 50  0001 C CNN
F 4 "Value" H 10950 4150 60  0001 C CNN "Fieldname"
	1    10950 4150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J12
U 1 1 59C9A9A4
P 10900 4700
F 0 "J12" H 10900 4850 50  0000 C CNN
F 1 "VideoV" V 11000 4700 50  0000 C CNN
F 2 "" H 10900 4700 50  0001 C CNN
F 3 "" H 10900 4700 50  0001 C CNN
F 4 "Value" H 10900 4700 60  0001 C CNN "Fieldname"
	1    10900 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 4100 10750 4100
Wire Wire Line
	10750 4200 10550 4200
Wire Wire Line
	10550 4200 10550 4300
Wire Wire Line
	10700 4650 10550 4650
Wire Wire Line
	10700 4750 10550 4750
Wire Wire Line
	10550 4750 10550 4850
$Comp
L CONN_01X02 J6
U 1 1 59C9AF66
P 7400 6000
F 0 "J6" H 7400 6150 50  0000 C CNN
F 1 "Heater1" V 7500 6000 50  0000 C CNN
F 2 "" H 7400 6000 50  0001 C CNN
F 3 "" H 7400 6000 50  0001 C CNN
F 4 "Value" H 7400 6000 60  0001 C CNN "Fieldname"
	1    7400 6000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J7
U 1 1 59C9B08E
P 7400 6400
F 0 "J7" H 7400 6550 50  0000 C CNN
F 1 "Heater2" V 7500 6400 50  0000 C CNN
F 2 "" H 7400 6400 50  0001 C CNN
F 3 "" H 7400 6400 50  0001 C CNN
F 4 "Value" H 7400 6400 60  0001 C CNN "Fieldname"
	1    7400 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 5950 6900 5950
Connection ~ 6900 6050
Connection ~ 6900 6350
$Comp
L GND #PWR024
U 1 1 59C9B453
P 7200 6450
F 0 "#PWR024" H 7200 6200 50  0001 C CNN
F 1 "GND" H 7200 6300 50  0000 C CNN
F 2 "" H 7200 6450 50  0001 C CNN
F 3 "" H 7200 6450 50  0001 C CNN
	1    7200 6450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 59C9B4BB
P 7200 6050
F 0 "#PWR025" H 7200 5800 50  0001 C CNN
F 1 "GND" H 7200 5900 50  0000 C CNN
F 2 "" H 7200 6050 50  0001 C CNN
F 3 "" H 7200 6050 50  0001 C CNN
	1    7200 6050
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 59C9CC5E
P 8550 2400
F 0 "R13" V 8630 2400 50  0000 C CNN
F 1 "100k" V 8550 2400 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8480 2400 50  0001 C CNN
F 3 "" H 8550 2400 50  0001 C CNN
	1    8550 2400
	-1   0    0    1   
$EndComp
$Comp
L AO4801A T3
U 1 1 59C9CC65
P 9600 2450
F 0 "T3" H 9550 2100 60  0000 C CNN
F 1 "AO4801A" H 9550 2250 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 9600 2450 60  0001 C CNN
F 3 "" H 9600 2450 60  0001 C CNN
F 4 "Value" H 9600 2450 60  0001 C CNN "Fieldname"
	1    9600 2450
	1    0    0    -1  
$EndComp
$Comp
L R R14
U 1 1 59C9CC6B
P 8850 2600
F 0 "R14" V 8930 2600 50  0000 C CNN
F 1 "100k" V 8850 2600 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8780 2600 50  0001 C CNN
F 3 "" H 8850 2600 50  0001 C CNN
	1    8850 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	9200 2250 8550 2250
Wire Wire Line
	8550 2550 8700 2550
Wire Wire Line
	8700 2350 8700 2650
Wire Wire Line
	8700 2350 9200 2350
Wire Wire Line
	8850 2450 9200 2450
Wire Wire Line
	8850 2750 9300 2750
Wire Wire Line
	9100 2750 9100 2550
Wire Wire Line
	9100 2550 9200 2550
Wire Wire Line
	8850 2050 8850 2450
Connection ~ 8850 2250
Wire Wire Line
	6850 2050 8850 2050
Wire Wire Line
	9300 2750 9300 3150
Connection ~ 9100 2750
Wire Wire Line
	8400 3250 8400 2650
Wire Wire Line
	8400 2650 8700 2650
Connection ~ 8700 2550
$Comp
L GND #PWR026
U 1 1 59C9CC81
P 9300 3550
F 0 "#PWR026" H 9300 3300 50  0001 C CNN
F 1 "GND" H 9300 3400 50  0000 C CNN
F 2 "" H 9300 3550 50  0001 C CNN
F 3 "" H 9300 3550 50  0001 C CNN
	1    9300 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 59C9CC87
P 8400 3650
F 0 "#PWR027" H 8400 3400 50  0001 C CNN
F 1 "GND" H 8400 3500 50  0000 C CNN
F 2 "" H 8400 3650 50  0001 C CNN
F 3 "" H 8400 3650 50  0001 C CNN
	1    8400 3650
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 59C9CC8D
P 8850 3350
F 0 "R15" V 8930 3350 50  0000 C CNN
F 1 "1k" V 8850 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8780 3350 50  0001 C CNN
F 3 "" H 8850 3350 50  0001 C CNN
	1    8850 3350
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 59C9CC93
P 7950 3450
F 0 "R12" V 8030 3450 50  0000 C CNN
F 1 "1k" V 7950 3450 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7880 3450 50  0001 C CNN
F 3 "" H 7950 3450 50  0001 C CNN
	1    7950 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8700 3100 8700 3350
Wire Wire Line
	7350 3100 8700 3100
Wire Wire Line
	7800 3450 7350 3450
Text Label 7550 3100 0    60   ~ 0
SW4
Text Label 7500 3450 0    60   ~ 0
SW5
$Comp
L BC817-40 Q7
U 1 1 59C9CC9E
P 9200 3350
F 0 "Q7" H 9400 3425 50  0000 L CNN
F 1 "BC817-40" H 9400 3350 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9400 3275 50  0001 L CIN
F 3 "" H 9200 3350 50  0001 L CNN
	1    9200 3350
	1    0    0    -1  
$EndComp
$Comp
L BC817-40 Q6
U 1 1 59C9CCA4
P 8300 3450
F 0 "Q6" H 8500 3525 50  0000 L CNN
F 1 "BC817-40" H 8500 3450 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8500 3375 50  0001 L CIN
F 3 "" H 8300 3450 50  0001 L CNN
	1    8300 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 2050 6850 4100
Connection ~ 6850 4100
Wire Wire Line
	9950 2250 10500 2250
Wire Wire Line
	10050 2250 10050 2350
Wire Wire Line
	10050 2350 9950 2350
Wire Wire Line
	9950 2450 10050 2450
Wire Wire Line
	10050 2450 10050 2600
Wire Wire Line
	10050 2550 9950 2550
$Comp
L CONN_01X02 J10
U 1 1 59C9D880
P 10700 2300
F 0 "J10" H 10700 2450 50  0000 C CNN
F 1 "BatSw1" V 10800 2300 50  0000 C CNN
F 2 "" H 10700 2300 50  0001 C CNN
F 3 "" H 10700 2300 50  0001 C CNN
F 4 "Value" H 10700 2300 60  0001 C CNN "Fieldname"
	1    10700 2300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J11
U 1 1 59C9D9F7
P 10700 2650
F 0 "J11" H 10700 2800 50  0000 C CNN
F 1 "BatSw2" V 10800 2650 50  0000 C CNN
F 2 "" H 10700 2650 50  0001 C CNN
F 3 "" H 10700 2650 50  0001 C CNN
F 4 "Value" H 10700 2650 60  0001 C CNN "Fieldname"
	1    10700 2650
	1    0    0    -1  
$EndComp
Connection ~ 10050 2250
Wire Wire Line
	10050 2600 10500 2600
Connection ~ 10050 2550
$Comp
L GND #PWR028
U 1 1 59C9DE6B
P 10500 2700
F 0 "#PWR028" H 10500 2450 50  0001 C CNN
F 1 "GND" H 10500 2550 50  0000 C CNN
F 2 "" H 10500 2700 50  0001 C CNN
F 3 "" H 10500 2700 50  0001 C CNN
	1    10500 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 59C9DF66
P 10500 2350
F 0 "#PWR029" H 10500 2100 50  0001 C CNN
F 1 "GND" H 10500 2200 50  0000 C CNN
F 2 "" H 10500 2350 50  0001 C CNN
F 3 "" H 10500 2350 50  0001 C CNN
	1    10500 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 59C9EC25
P 8250 1600
F 0 "#PWR030" H 8250 1350 50  0001 C CNN
F 1 "GND" H 8250 1450 50  0000 C CNN
F 2 "" H 8250 1600 50  0001 C CNN
F 3 "" H 8250 1600 50  0001 C CNN
	1    8250 1600
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 59C9EC2B
P 7800 1400
F 0 "R11" V 7880 1400 50  0000 C CNN
F 1 "1k" V 7800 1400 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7730 1400 50  0001 C CNN
F 3 "" H 7800 1400 50  0001 C CNN
	1    7800 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7650 1400 7200 1400
$Comp
L BC817-40 Q5
U 1 1 59C9EC32
P 8150 1400
F 0 "Q5" H 8350 1475 50  0000 L CNN
F 1 "BC817-40" H 8350 1400 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8350 1325 50  0001 L CIN
F 3 "" H 8150 1400 50  0001 L CNN
	1    8150 1400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J9
U 1 1 59C9EE33
P 8600 1050
F 0 "J9" H 8600 1200 50  0000 C CNN
F 1 "OC1" V 8700 1050 50  0000 C CNN
F 2 "" H 8600 1050 50  0001 C CNN
F 3 "" H 8600 1050 50  0001 C CNN
F 4 "Value" H 8600 1050 60  0001 C CNN "Fieldname"
	1    8600 1050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J8
U 1 1 59C9EF12
P 8600 700
F 0 "J8" H 8600 850 50  0000 C CNN
F 1 "OC2" V 8700 700 50  0000 C CNN
F 2 "" H 8600 700 50  0001 C CNN
F 3 "" H 8600 700 50  0001 C CNN
F 4 "Value" H 8600 700 60  0001 C CNN "Fieldname"
	1    8600 700 
	1    0    0    -1  
$EndComp
Text Label 7350 1400 0    60   ~ 0
SW6
Wire Wire Line
	8250 1200 8250 1000
Wire Wire Line
	8250 1000 8400 1000
$Comp
L GND #PWR031
U 1 1 59C9F43B
P 8400 1100
F 0 "#PWR031" H 8400 850 50  0001 C CNN
F 1 "GND" H 8400 950 50  0000 C CNN
F 2 "" H 8400 1100 50  0001 C CNN
F 3 "" H 8400 1100 50  0001 C CNN
	1    8400 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 59C9F4CA
P 8400 750
F 0 "#PWR032" H 8400 500 50  0001 C CNN
F 1 "GND" H 8400 600 50  0000 C CNN
F 2 "" H 8400 750 50  0001 C CNN
F 3 "" H 8400 750 50  0001 C CNN
	1    8400 750 
	1    0    0    -1  
$EndComp
$Comp
L PCF8574_EbayMod M3
U 1 1 59CA2BA9
P 5700 3350
F 0 "M3" H 5650 3050 60  0000 C CNN
F 1 "PCF8574_EbayMod" H 5850 3250 60  0000 C CNN
F 2 "" H 5700 3350 60  0001 C CNN
F 3 "" H 5700 3350 60  0001 C CNN
	1    5700 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR033
U 1 1 59CA2F5C
P 4950 3300
F 0 "#PWR033" H 4950 3050 50  0001 C CNN
F 1 "GND" H 4950 3150 50  0000 C CNN
F 2 "" H 4950 3300 50  0001 C CNN
F 3 "" H 4950 3300 50  0001 C CNN
	1    4950 3300
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR034
U 1 1 59CA330D
P 4950 3200
F 0 "#PWR034" H 4950 3050 50  0001 C CNN
F 1 "+5V" V 4950 3340 50  0000 C CNN
F 2 "" H 4950 3200 50  0001 C CNN
F 3 "" H 4950 3200 50  0001 C CNN
	1    4950 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 3400 4950 3400
Wire Wire Line
	4950 3500 4400 3500
Text Label 4500 3400 0    60   ~ 0
SDA
Text Label 4500 3500 0    60   ~ 0
SCL
Wire Wire Line
	6300 3000 6300 2500
Wire Wire Line
	6200 3000 6200 2500
Wire Wire Line
	6100 3000 6100 2500
Wire Wire Line
	6000 3000 6000 2500
Wire Wire Line
	5900 3000 5900 2500
Wire Wire Line
	5800 2500 5800 3000
Wire Wire Line
	5700 3000 5700 2500
Wire Wire Line
	5600 3000 5600 2500
Text Label 6300 2700 1    60   ~ 0
SW0
Text Label 6200 2700 1    60   ~ 0
SW1
Text Label 6100 2700 1    60   ~ 0
SW2
Text Label 6000 2700 1    60   ~ 0
SW3
Text Label 5900 2700 1    60   ~ 0
SW4
Text Label 5800 2700 1    60   ~ 0
SW5
Text Label 5700 2700 1    60   ~ 0
SW6
Text Label 5600 2700 1    60   ~ 0
SW7
$Comp
L GND #PWR035
U 1 1 59CA45A8
P 8000 1100
F 0 "#PWR035" H 8000 850 50  0001 C CNN
F 1 "GND" H 8000 950 50  0000 C CNN
F 2 "" H 8000 1100 50  0001 C CNN
F 3 "" H 8000 1100 50  0001 C CNN
	1    8000 1100
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 59CA45AE
P 7550 900
F 0 "R16" V 7630 900 50  0000 C CNN
F 1 "1k" V 7550 900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7480 900 50  0001 C CNN
F 3 "" H 7550 900 50  0001 C CNN
	1    7550 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7400 900  6950 900 
$Comp
L BC817-40 Q8
U 1 1 59CA45B5
P 7900 900
F 0 "Q8" H 8100 975 50  0000 L CNN
F 1 "BC817-40" H 8100 900 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8100 825 50  0001 L CIN
F 3 "" H 7900 900 50  0001 L CNN
	1    7900 900 
	1    0    0    -1  
$EndComp
Text Label 7100 900  0    60   ~ 0
SW7
Wire Wire Line
	8000 700  8000 500 
Wire Wire Line
	8000 500  8400 500 
Wire Wire Line
	8400 500  8400 650 
$EndSCHEMATC
