EESchema Schematic File Version 2
LIBS:KiCad-rescue
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
LIBS:mysensors_arduino
LIBS:ArduinoModules
LIBS:stm32f103c8t6-module-china
LIBS:KiCad-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
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
L stm32f103c8t6-module-china U8
U 1 1 591A002B
P 5250 3750
F 0 "U8" H 5250 5100 60  0000 C CNN
F 1 "stm32f103c8t6-module-china" V 5250 3750 60  0000 C CNN
F 2 "myelin-kicad:stm32f103c8t6-module-china" H 5250 2050 60  0001 C CNN
F 3 "" H 4850 4000 60  0000 C CNN
	1    5250 3750
	1    0    0    -1  
$EndComp
$Comp
L CurrentMeter_INA219DC U1
U 1 1 591A0068
P 1550 1100
F 0 "U1" H 1550 700 60  0000 C CNN
F 1 "CurrentMeter_INA219DC" H 1500 1450 60  0000 C CNN
F 2 "LIB:Current_Sensor" H 3000 1000 60  0001 C CNN
F 3 "" H 3000 1000 60  0001 C CNN
	1    1550 1100
	0    -1   -1   0   
$EndComp
$Comp
L GPS_NEO_6M U11
U 1 1 591A00D1
P 8550 2900
F 0 "U11" H 8550 2500 60  0000 C CNN
F 1 "GPS_NEO_6M" H 8550 3150 60  0000 C CNN
F 2 "LIB:GPS_Modul" H 10000 2800 60  0001 C CNN
F 3 "" H 10000 2800 60  0001 C CNN
	1    8550 2900
	1    0    0    -1  
$EndComp
$Comp
L Gyro_MPU_9250 U13
U 1 1 591A0156
P 10800 2150
F 0 "U13" H 10750 1550 60  0000 C CNN
F 1 "Gyro_MPU_9250" H 10750 2700 60  0000 C CNN
F 2 "LIB:MPU_9250" H 10700 2050 60  0001 C CNN
F 3 "" H 10700 2050 60  0001 C CNN
	1    10800 2150
	1    0    0    -1  
$EndComp
$Comp
L Gyro_MPU_9250 U14
U 1 1 591A01BB
P 10800 3450
F 0 "U14" H 10750 2850 60  0000 C CNN
F 1 "Gyro_MPU_9250" H 10750 4000 60  0000 C CNN
F 2 "LIB:MPU_9250" H 10700 3350 60  0001 C CNN
F 3 "" H 10700 3350 60  0001 C CNN
	1    10800 3450
	1    0    0    -1  
$EndComp
$Comp
L Transceiver_HC_12_UART U6
U 1 1 591A0217
P 3100 3200
F 0 "U6" H 3100 2850 60  0000 C CNN
F 1 "Transceiver_HC_12_UART" H 3050 3500 60  0000 C CNN
F 2 "LIB:HC-12" H 4550 3100 60  0001 C CNN
F 3 "" H 4550 3100 60  0001 C CNN
	1    3100 3200
	-1   0    0    -1  
$EndComp
$Comp
L Pressure_BMP180 U12
U 1 1 591A02C4
P 10750 1050
F 0 "U12" H 10750 800 60  0000 C CNN
F 1 "Pressure_BMP180" H 10750 1300 60  0000 C CNN
F 2 "LIB:BMP180" H 12200 950 60  0001 C CNN
F 3 "" H 12200 950 60  0001 C CNN
	1    10750 1050
	1    0    0    -1  
$EndComp
$Comp
L Battery-RESCUE-KiCad BT1
U 1 1 591A10A3
P 850 2300
F 0 "BT1" H 950 2400 50  0000 L CNN
F 1 "Battery" H 950 2300 50  0000 L CNN
F 2 "Connectors_Hirose:Hirose_DF63-2P-3.96DSA_02x3.96mm_Straight" V 850 2360 50  0001 C CNN
F 3 "" V 850 2360 50  0000 C CNN
	1    850  2300
	1    0    0    -1  
$EndComp
$Comp
L Level_Shifter U2
U 1 1 591A142A
P 2200 5350
F 0 "U2" H 2150 4750 60  0000 C CNN
F 1 "Level_Shifter" H 2200 5700 60  0000 C CNN
F 2 "LIB:level_shifter" H 2150 5050 60  0001 C CNN
F 3 "" H 2150 5050 60  0001 C CNN
	1    2200 5350
	1    0    0    -1  
$EndComp
$Comp
L Pressure_GY_36 U9
U 1 1 591A1DC8
P 9300 5900
F 0 "U9" H 9300 5350 60  0000 C CNN
F 1 "Pressure_GY_63" H 9300 6150 60  0000 C CNN
F 2 "LIB:GY_63" H 10750 5800 60  0001 C CNN
F 3 "" H 10750 5800 60  0001 C CNN
	1    9300 5900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P1
U 1 1 591A21ED
P 750 4650
F 0 "P1" H 750 4850 50  0000 C CNN
F 1 "PWM" V 850 4650 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 750 4650 50  0001 C CNN
F 3 "" H 750 4650 50  0000 C CNN
	1    750  4650
	-1   0    0    1   
$EndComp
$Comp
L StepDown U7
U 1 1 591A24F4
P 3850 750
F 0 "U7" H 3850 550 50  0000 C CNN
F 1 "StepDown" H 3850 950 50  0000 C CNN
F 2 "LIB:step_down" H 3850 750 50  0001 C CNN
F 3 "" H 3850 750 50  0000 C CNN
	1    3850 750 
	1    0    0    -1  
$EndComp
$Comp
L StepDown U4
U 1 1 591A2549
P 2750 1650
F 0 "U4" H 2750 1450 50  0000 C CNN
F 1 "StepDown" H 2750 1850 50  0000 C CNN
F 2 "LIB:step_down" H 2750 1650 50  0001 C CNN
F 3 "" H 2750 1650 50  0000 C CNN
	1    2750 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 591A2EE4
P 850 2750
F 0 "#PWR01" H 850 2500 50  0001 C CNN
F 1 "GND" H 850 2600 50  0000 C CNN
F 2 "" H 850 2750 50  0000 C CNN
F 3 "" H 850 2750 50  0000 C CNN
	1    850  2750
	1    0    0    -1  
$EndComp
$Comp
L +5VA #PWR02
U 1 1 591A307F
P 4450 700
F 0 "#PWR02" H 4450 550 50  0001 C CNN
F 1 "+5VA" H 4450 840 50  0000 C CNN
F 2 "" H 4450 700 50  0000 C CNN
F 3 "" H 4450 700 50  0000 C CNN
	1    4450 700 
	1    0    0    -1  
$EndComp
$Comp
L +5VD #PWR03
U 1 1 591A322B
P 3350 1600
F 0 "#PWR03" H 3350 1450 50  0001 C CNN
F 1 "+5VD" H 3350 1740 50  0000 C CNN
F 2 "" H 3350 1600 50  0000 C CNN
F 3 "" H 3350 1600 50  0000 C CNN
	1    3350 1600
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR04
U 1 1 591A354D
P 4050 5200
F 0 "#PWR04" H 4050 5050 50  0001 C CNN
F 1 "+3.3V" H 4050 5340 50  0000 C CNN
F 2 "" H 4050 5200 50  0000 C CNN
F 3 "" H 4050 5200 50  0000 C CNN
	1    4050 5200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4200 5200 4050 5200
Wire Wire Line
	4250 700  4450 700 
Wire Wire Line
	3150 1600 3350 1600
Wire Wire Line
	850  2450 850  2750
$Comp
L GND #PWR05
U 1 1 591A3947
P 2750 1900
F 0 "#PWR05" H 2750 1650 50  0001 C CNN
F 1 "GND" H 2750 1750 50  0000 C CNN
F 2 "" H 2750 1900 50  0000 C CNN
F 3 "" H 2750 1900 50  0000 C CNN
	1    2750 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 591A39A7
P 3850 1000
F 0 "#PWR06" H 3850 750 50  0001 C CNN
F 1 "GND" H 3850 850 50  0000 C CNN
F 2 "" H 3850 1000 50  0000 C CNN
F 3 "" H 3850 1000 50  0000 C CNN
	1    3850 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 1000 3950 1000
Connection ~ 3850 1000
Wire Wire Line
	2650 1900 2850 1900
Connection ~ 2750 1900
$Comp
L +3.3V #PWR07
U 1 1 591A3EB2
P 6400 2650
F 0 "#PWR07" H 6400 2500 50  0001 C CNN
F 1 "+3.3V" H 6400 2790 50  0000 C CNN
F 2 "" H 6400 2650 50  0000 C CNN
F 3 "" H 6400 2650 50  0000 C CNN
	1    6400 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 2650 6300 2650
$Comp
L +5VD #PWR08
U 1 1 591A4491
P 4050 4900
F 0 "#PWR08" H 4050 4750 50  0001 C CNN
F 1 "+5VD" H 4050 5040 50  0000 C CNN
F 2 "" H 4050 4900 50  0000 C CNN
F 3 "" H 4050 4900 50  0000 C CNN
	1    4050 4900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 4900 4200 4900
$Comp
L GND #PWR09
U 1 1 591A46A6
P 4200 5050
F 0 "#PWR09" H 4200 4800 50  0001 C CNN
F 1 "GND" H 4200 4900 50  0000 C CNN
F 2 "" H 4200 5050 50  0000 C CNN
F 3 "" H 4200 5050 50  0000 C CNN
	1    4200 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 5050 4200 5050
Wire Wire Line
	1650 5300 1600 5300
$Comp
L GND #PWR010
U 1 1 59232B5D
P 1600 5400
F 0 "#PWR010" H 1600 5150 50  0001 C CNN
F 1 "GND" H 1600 5250 50  0000 C CNN
F 2 "" H 1600 5400 50  0000 C CNN
F 3 "" H 1600 5400 50  0000 C CNN
	1    1600 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 5400 1600 5400
$Comp
L GND #PWR011
U 1 1 59232E32
P 2800 5400
F 0 "#PWR011" H 2800 5150 50  0001 C CNN
F 1 "GND" H 2800 5250 50  0000 C CNN
F 2 "" H 2800 5400 50  0000 C CNN
F 3 "" H 2800 5400 50  0000 C CNN
	1    2800 5400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2800 5400 2750 5400
$Comp
L +3.3V #PWR012
U 1 1 5923304D
P 2800 5300
F 0 "#PWR012" H 2800 5150 50  0001 C CNN
F 1 "+3.3V" H 2800 5440 50  0000 C CNN
F 2 "" H 2800 5300 50  0000 C CNN
F 3 "" H 2800 5300 50  0000 C CNN
	1    2800 5300
	0    1    1    0   
$EndComp
$Comp
L GND #PWR013
U 1 1 59233BA5
P 6400 2500
F 0 "#PWR013" H 6400 2250 50  0001 C CNN
F 1 "GND" H 6400 2350 50  0000 C CNN
F 2 "" H 6400 2500 50  0000 C CNN
F 3 "" H 6400 2500 50  0000 C CNN
	1    6400 2500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR014
U 1 1 59234863
P 1050 4550
F 0 "#PWR014" H 1050 4300 50  0001 C CNN
F 1 "GND" H 1050 4400 50  0000 C CNN
F 2 "" H 1050 4550 50  0000 C CNN
F 3 "" H 1050 4550 50  0000 C CNN
	1    1050 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 4550 950  4550
Wire Wire Line
	1050 4650 950  4650
Wire Wire Line
	1650 4750 1650 5100
$Comp
L CONN_01X03 P2
U 1 1 59235017
P 750 5050
F 0 "P2" H 750 5250 50  0000 C CNN
F 1 "PWM" V 850 5050 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 750 5050 50  0001 C CNN
F 3 "" H 750 5050 50  0000 C CNN
	1    750  5050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR015
U 1 1 5923501D
P 1050 4950
F 0 "#PWR015" H 1050 4700 50  0001 C CNN
F 1 "GND" H 1050 4800 50  0000 C CNN
F 2 "" H 1050 4950 50  0000 C CNN
F 3 "" H 1050 4950 50  0000 C CNN
	1    1050 4950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 4950 950  4950
Wire Wire Line
	1050 5050 950  5050
$Comp
L CONN_01X03 P3
U 1 1 592351C6
P 750 5450
F 0 "P3" H 750 5650 50  0000 C CNN
F 1 "PWM" V 850 5450 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 750 5450 50  0001 C CNN
F 3 "" H 750 5450 50  0000 C CNN
	1    750  5450
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR016
U 1 1 592351CC
P 1050 5350
F 0 "#PWR016" H 1050 5100 50  0001 C CNN
F 1 "GND" H 1050 5200 50  0000 C CNN
F 2 "" H 1050 5350 50  0000 C CNN
F 3 "" H 1050 5350 50  0000 C CNN
	1    1050 5350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 5350 950  5350
Wire Wire Line
	1050 5450 950  5450
$Comp
L CONN_01X03 P4
U 1 1 592351DA
P 750 5850
F 0 "P4" H 750 6050 50  0000 C CNN
F 1 "PWM" V 850 5850 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 750 5850 50  0001 C CNN
F 3 "" H 750 5850 50  0000 C CNN
	1    750  5850
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR017
U 1 1 592351E0
P 1050 5750
F 0 "#PWR017" H 1050 5500 50  0001 C CNN
F 1 "GND" H 1050 5600 50  0000 C CNN
F 2 "" H 1050 5750 50  0000 C CNN
F 3 "" H 1050 5750 50  0000 C CNN
	1    1050 5750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 5750 950  5750
Wire Wire Line
	1050 5850 950  5850
$Comp
L CONN_01X03 P5
U 1 1 59235296
P 750 6250
F 0 "P5" H 750 6450 50  0000 C CNN
F 1 "PWM" V 850 6250 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 750 6250 50  0001 C CNN
F 3 "" H 750 6250 50  0000 C CNN
	1    750  6250
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR018
U 1 1 5923529C
P 1050 6150
F 0 "#PWR018" H 1050 5900 50  0001 C CNN
F 1 "GND" H 1050 6000 50  0000 C CNN
F 2 "" H 1050 6150 50  0000 C CNN
F 3 "" H 1050 6150 50  0000 C CNN
	1    1050 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 6150 950  6150
Wire Wire Line
	1050 6250 950  6250
$Comp
L CONN_01X03 P6
U 1 1 592352AA
P 750 6650
F 0 "P6" H 750 6850 50  0000 C CNN
F 1 "PWM" V 850 6650 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 750 6650 50  0001 C CNN
F 3 "" H 750 6650 50  0000 C CNN
	1    750  6650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR019
U 1 1 592352B0
P 1050 6550
F 0 "#PWR019" H 1050 6300 50  0001 C CNN
F 1 "GND" H 1050 6400 50  0000 C CNN
F 2 "" H 1050 6550 50  0000 C CNN
F 3 "" H 1050 6550 50  0000 C CNN
	1    1050 6550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 6550 950  6550
Wire Wire Line
	1050 6650 950  6650
$Comp
L CONN_01X03 P7
U 1 1 592352BE
P 750 7050
F 0 "P7" H 750 7250 50  0000 C CNN
F 1 "PWM" V 850 7050 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 750 7050 50  0001 C CNN
F 3 "" H 750 7050 50  0000 C CNN
	1    750  7050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR020
U 1 1 592352C4
P 1050 6950
F 0 "#PWR020" H 1050 6700 50  0001 C CNN
F 1 "GND" H 1050 6800 50  0000 C CNN
F 2 "" H 1050 6950 50  0000 C CNN
F 3 "" H 1050 6950 50  0000 C CNN
	1    1050 6950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 6950 950  6950
Wire Wire Line
	1050 7050 950  7050
$Comp
L CONN_01X03 P8
U 1 1 592352D2
P 750 7450
F 0 "P8" H 750 7650 50  0000 C CNN
F 1 "PWM" V 850 7450 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 750 7450 50  0001 C CNN
F 3 "" H 750 7450 50  0000 C CNN
	1    750  7450
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR021
U 1 1 592352D8
P 1050 7350
F 0 "#PWR021" H 1050 7100 50  0001 C CNN
F 1 "GND" H 1050 7200 50  0000 C CNN
F 2 "" H 1050 7350 50  0000 C CNN
F 3 "" H 1050 7350 50  0000 C CNN
	1    1050 7350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 7350 950  7350
Wire Wire Line
	1050 7450 950  7450
Wire Wire Line
	950  4750 1650 4750
Wire Wire Line
	950  5150 1400 5150
Wire Wire Line
	1400 5200 1650 5200
Wire Wire Line
	1650 5500 1400 5500
Wire Wire Line
	1400 5500 1400 5550
Wire Wire Line
	1400 5550 950  5550
Wire Wire Line
	1650 5600 1650 5950
Wire Wire Line
	1650 5950 950  5950
Wire Wire Line
	1400 5150 1400 5200
$Comp
L Level_Shifter U3
U 1 1 59235F74
P 2200 6950
F 0 "U3" H 2150 6350 60  0000 C CNN
F 1 "Level_Shifter" H 2200 7300 60  0000 C CNN
F 2 "LIB:level_shifter" H 2150 6650 60  0001 C CNN
F 3 "" H 2150 6650 60  0001 C CNN
	1    2200 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 6900 1600 6900
$Comp
L GND #PWR022
U 1 1 59235F81
P 1600 7000
F 0 "#PWR022" H 1600 6750 50  0001 C CNN
F 1 "GND" H 1600 6850 50  0000 C CNN
F 2 "" H 1600 7000 50  0000 C CNN
F 3 "" H 1600 7000 50  0000 C CNN
	1    1600 7000
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 7000 1600 7000
$Comp
L GND #PWR023
U 1 1 59235F88
P 2800 7000
F 0 "#PWR023" H 2800 6750 50  0001 C CNN
F 1 "GND" H 2800 6850 50  0000 C CNN
F 2 "" H 2800 7000 50  0000 C CNN
F 3 "" H 2800 7000 50  0000 C CNN
	1    2800 7000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2800 7000 2750 7000
$Comp
L +3.3V #PWR024
U 1 1 59235F8F
P 2800 6900
F 0 "#PWR024" H 2800 6750 50  0001 C CNN
F 1 "+3.3V" H 2800 7040 50  0000 C CNN
F 2 "" H 2800 6900 50  0000 C CNN
F 3 "" H 2800 6900 50  0000 C CNN
	1    2800 6900
	0    1    1    0   
$EndComp
Wire Wire Line
	2800 6900 2750 6900
Wire Wire Line
	1650 6350 1650 6700
Wire Wire Line
	950  6350 1650 6350
Wire Wire Line
	950  6750 1400 6750
Wire Wire Line
	1400 6800 1650 6800
Wire Wire Line
	1650 7100 1400 7100
Wire Wire Line
	1400 7100 1400 7150
Wire Wire Line
	1400 7150 950  7150
Wire Wire Line
	1650 7200 1650 7550
Wire Wire Line
	1650 7550 950  7550
Wire Wire Line
	1400 6750 1400 6800
$Comp
L +3.3V #PWR025
U 1 1 59236B0F
P 3750 3400
F 0 "#PWR025" H 3750 3250 50  0001 C CNN
F 1 "+3.3V" H 3750 3540 50  0000 C CNN
F 2 "" H 3750 3400 50  0000 C CNN
F 3 "" H 3750 3400 50  0000 C CNN
	1    3750 3400
	0    1    -1   0   
$EndComp
Wire Wire Line
	3700 3400 3750 3400
$Comp
L +3.3V #PWR026
U 1 1 59236D14
P 10150 3000
F 0 "#PWR026" H 10150 2850 50  0001 C CNN
F 1 "+3.3V" H 10150 3140 50  0000 C CNN
F 2 "" H 10150 3000 50  0000 C CNN
F 3 "" H 10150 3000 50  0000 C CNN
	1    10150 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10200 3000 10150 3000
$Comp
L +3.3V #PWR027
U 1 1 59236D9B
P 1800 1750
F 0 "#PWR027" H 1800 1600 50  0001 C CNN
F 1 "+3.3V" H 1800 1890 50  0000 C CNN
F 2 "" H 1800 1750 50  0000 C CNN
F 3 "" H 1800 1750 50  0000 C CNN
	1    1800 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	1800 1700 1800 1750
$Comp
L +3.3V #PWR028
U 1 1 59236E8B
P 10150 900
F 0 "#PWR028" H 10150 750 50  0001 C CNN
F 1 "+3.3V" H 10150 1040 50  0000 C CNN
F 2 "" H 10150 900 50  0000 C CNN
F 3 "" H 10150 900 50  0000 C CNN
	1    10150 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10200 900  10150 900 
$Comp
L +3.3V #PWR029
U 1 1 59236EBE
P 8050 5750
F 0 "#PWR029" H 8050 5600 50  0001 C CNN
F 1 "+3.3V" H 8050 5890 50  0000 C CNN
F 2 "" H 8050 5750 50  0000 C CNN
F 3 "" H 8050 5750 50  0000 C CNN
	1    8050 5750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8050 5750 8750 5750
$Comp
L +3.3V #PWR030
U 1 1 59237191
P 10150 1700
F 0 "#PWR030" H 10150 1550 50  0001 C CNN
F 1 "+3.3V" H 10150 1840 50  0000 C CNN
F 2 "" H 10150 1700 50  0000 C CNN
F 3 "" H 10150 1700 50  0000 C CNN
	1    10150 1700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10200 1700 10150 1700
$Comp
L GND #PWR031
U 1 1 59237949
P 6400 2350
F 0 "#PWR031" H 6400 2100 50  0001 C CNN
F 1 "GND" H 6400 2200 50  0000 C CNN
F 2 "" H 6400 2350 50  0000 C CNN
F 3 "" H 6400 2350 50  0000 C CNN
	1    6400 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6400 2500 6300 2500
Wire Wire Line
	6400 2350 6300 2350
$Comp
L +5VD #PWR032
U 1 1 59237FEC
P 7950 3150
F 0 "#PWR032" H 7950 3000 50  0001 C CNN
F 1 "+5VD" H 7950 3290 50  0000 C CNN
F 2 "" H 7950 3150 50  0000 C CNN
F 3 "" H 7950 3150 50  0000 C CNN
	1    7950 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8000 3150 7950 3150
$Comp
L GND #PWR033
U 1 1 59238401
P 3750 3300
F 0 "#PWR033" H 3750 3050 50  0001 C CNN
F 1 "GND" H 3750 3150 50  0000 C CNN
F 2 "" H 3750 3300 50  0000 C CNN
F 3 "" H 3750 3300 50  0000 C CNN
	1    3750 3300
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR034
U 1 1 59238547
P 10150 1000
F 0 "#PWR034" H 10150 750 50  0001 C CNN
F 1 "GND" H 10150 850 50  0000 C CNN
F 2 "" H 10150 1000 50  0000 C CNN
F 3 "" H 10150 1000 50  0000 C CNN
	1    10150 1000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR035
U 1 1 592385E5
P 8050 5850
F 0 "#PWR035" H 8050 5600 50  0001 C CNN
F 1 "GND" H 8050 5700 50  0000 C CNN
F 2 "" H 8050 5850 50  0000 C CNN
F 3 "" H 8050 5850 50  0000 C CNN
	1    8050 5850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR036
U 1 1 59238659
P 10150 1800
F 0 "#PWR036" H 10150 1550 50  0001 C CNN
F 1 "GND" H 10150 1650 50  0000 C CNN
F 2 "" H 10150 1800 50  0000 C CNN
F 3 "" H 10150 1800 50  0000 C CNN
	1    10150 1800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR037
U 1 1 592386A3
P 1700 1750
F 0 "#PWR037" H 1700 1500 50  0001 C CNN
F 1 "GND" H 1700 1600 50  0000 C CNN
F 2 "" H 1700 1750 50  0000 C CNN
F 3 "" H 1700 1750 50  0000 C CNN
	1    1700 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 592386ED
P 7950 3050
F 0 "#PWR038" H 7950 2800 50  0001 C CNN
F 1 "GND" H 7950 2900 50  0000 C CNN
F 2 "" H 7950 3050 50  0000 C CNN
F 3 "" H 7950 3050 50  0000 C CNN
	1    7950 3050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR039
U 1 1 59238737
P 10150 3100
F 0 "#PWR039" H 10150 2850 50  0001 C CNN
F 1 "GND" H 10150 2950 50  0000 C CNN
F 2 "" H 10150 3100 50  0000 C CNN
F 3 "" H 10150 3100 50  0000 C CNN
	1    10150 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	8050 5850 8750 5850
Wire Wire Line
	10200 1000 10150 1000
Wire Wire Line
	3700 3300 3750 3300
Wire Wire Line
	8000 3050 7950 3050
Wire Wire Line
	1700 1700 1700 1750
Wire Wire Line
	10200 1800 10150 1800
Wire Wire Line
	10200 3100 10150 3100
Wire Wire Line
	6300 4600 6750 4600
Text GLabel 6750 4600 2    60   Input ~ 0
servo1_signal
Text GLabel 2900 5100 2    60   Input ~ 0
servo1_signal
Wire Wire Line
	2900 5100 2750 5100
Text GLabel 2900 5200 2    60   Input ~ 0
servo2_signal
Text GLabel 2900 5500 2    60   Input ~ 0
servo3_signal
Text GLabel 2900 5600 2    60   Input ~ 0
servo4_signal
Wire Wire Line
	2900 5200 2750 5200
Wire Wire Line
	2900 5500 2750 5500
Wire Wire Line
	2900 5600 2750 5600
Text GLabel 2900 6700 2    60   Input ~ 0
servo5_signal
Text GLabel 2900 6800 2    60   Input ~ 0
servo6_signal
Text GLabel 2900 7100 2    60   Input ~ 0
servo7_signal
Text GLabel 2900 7200 2    60   Input ~ 0
servo8_signal
Wire Wire Line
	2900 6700 2750 6700
Wire Wire Line
	2900 6800 2750 6800
Wire Wire Line
	2900 7100 2750 7100
Wire Wire Line
	2900 7200 2750 7200
Text GLabel 6750 4450 2    60   Input ~ 0
servo2_signal
Text GLabel 6750 4300 2    60   Input ~ 0
servo3_signal
Text GLabel 6750 4150 2    60   Input ~ 0
servo4_signal
Text GLabel 6750 3550 2    60   Input ~ 0
servo6_signal
Text GLabel 6750 3400 2    60   Input ~ 0
servo7_signal
Text GLabel 6750 3250 2    60   Input ~ 0
servo8_signal
Text GLabel 6750 3700 2    60   Input ~ 0
servo5_signal
Wire Wire Line
	6750 4450 6300 4450
Wire Wire Line
	6750 4300 6300 4300
Wire Wire Line
	6300 4150 6750 4150
$Comp
L SD_Card_mini U5
U 1 1 5923DB51
P 3100 2500
F 0 "U5" H 3100 2100 60  0000 C CNN
F 1 "SD_Card_mini" H 3050 2850 60  0000 C CNN
F 2 "LIB:SD-CARD" H 4550 2400 60  0001 C CNN
F 3 "" H 4550 2400 60  0001 C CNN
	1    3100 2500
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR040
U 1 1 5923DFE4
P 3750 2250
F 0 "#PWR040" H 3750 2100 50  0001 C CNN
F 1 "+3.3V" H 3750 2390 50  0000 C CNN
F 2 "" H 3750 2250 50  0000 C CNN
F 3 "" H 3750 2250 50  0000 C CNN
	1    3750 2250
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR041
U 1 1 5923E173
P 3750 2750
F 0 "#PWR041" H 3750 2500 50  0001 C CNN
F 1 "GND" H 3750 2600 50  0000 C CNN
F 2 "" H 3750 2750 50  0000 C CNN
F 3 "" H 3750 2750 50  0000 C CNN
	1    3750 2750
	0    -1   1    0   
$EndComp
Wire Wire Line
	3750 2750 3700 2750
Wire Wire Line
	2000 450  2000 2350
Wire Wire Line
	6300 3100 7550 3100
Wire Wire Line
	7550 3100 7550 2850
Wire Wire Line
	7550 2850 8000 2850
NoConn ~ 8000 2750
Wire Wire Line
	4100 3000 4100 3550
Wire Wire Line
	4100 3550 4200 3550
Wire Wire Line
	3700 3100 4050 3100
Wire Wire Line
	4050 3100 4050 3250
Wire Wire Line
	4150 3100 4150 3200
Wire Wire Line
	4150 3200 3700 3200
Text GLabel 4150 4450 0    60   Input ~ 0
I2C_SDA
Text GLabel 4150 4300 0    60   Input ~ 0
I2C_SCL
Wire Wire Line
	4200 4300 4150 4300
Wire Wire Line
	4200 4450 4150 4450
Text GLabel 10150 3300 0    60   Input ~ 0
I2C_SDA
Text GLabel 10150 3200 0    60   Input ~ 0
I2C_SCL
Wire Wire Line
	10200 3200 10150 3200
Wire Wire Line
	10200 3300 10150 3300
Text GLabel 10150 2000 0    60   Input ~ 0
I2C_SDA
Text GLabel 10150 1900 0    60   Input ~ 0
I2C_SCL
Wire Wire Line
	10200 1900 10150 1900
Wire Wire Line
	10200 2000 10150 2000
Text GLabel 1500 1750 3    60   Input ~ 0
I2C_SDA
Text GLabel 1600 1750 3    60   Input ~ 0
I2C_SCL
Wire Wire Line
	1600 1700 1600 1750
Wire Wire Line
	1500 1700 1500 1750
Text GLabel 10150 1200 0    60   Input ~ 0
I2C_SDA
Text GLabel 10150 1100 0    60   Input ~ 0
I2C_SCL
Wire Wire Line
	10200 1100 10150 1100
Wire Wire Line
	10200 1200 10150 1200
Text GLabel 8050 6050 0    60   Input ~ 0
I2C_SDA
Text GLabel 8050 5950 0    60   Input ~ 0
I2C_SCL
Wire Wire Line
	8050 5950 8750 5950
Wire Wire Line
	8050 6050 8750 6050
Wire Wire Line
	4200 2800 4050 2800
Wire Wire Line
	4050 2800 4050 2450
Wire Wire Line
	4050 2450 3700 2450
Wire Wire Line
	4200 2550 4200 2500
Wire Wire Line
	3700 2550 4200 2550
NoConn ~ 10200 2100
NoConn ~ 10200 2200
NoConn ~ 10200 2400
NoConn ~ 10200 2500
NoConn ~ 10200 2600
NoConn ~ 10200 3400
NoConn ~ 10200 3500
NoConn ~ 10200 3700
NoConn ~ 10200 3800
NoConn ~ 10200 3900
NoConn ~ 8750 6150
NoConn ~ 8750 6250
NoConn ~ 8750 6350
Wire Wire Line
	4050 3400 4050 3550
Wire Wire Line
	4050 3550 3900 3550
Text GLabel 3900 3550 0    60   Input ~ 0
GYRO_CS1
Text GLabel 3900 3850 0    60   Input ~ 0
GYRO_CS2
Text GLabel 10150 2300 0    60   Input ~ 0
GYRO_CS1
Text GLabel 10150 3600 0    60   Input ~ 0
GYRO_CS2
Wire Wire Line
	10200 2300 10150 2300
Wire Wire Line
	10200 3600 10150 3600
Text GLabel 3900 3700 0    60   Input ~ 0
Transceiver_CS
Wire Wire Line
	4200 3850 3900 3850
$Comp
L SI4463_Modul U15
U 1 1 5924B510
P 10800 4900
F 0 "U15" H 10750 4100 60  0000 C CNN
F 1 "SI4463_Modul" H 10750 5450 60  0000 C CNN
F 2 "LIB:SI4463_Modul" H 10700 4800 60  0001 C CNN
F 3 "" H 10700 4800 60  0001 C CNN
	1    10800 4900
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR042
U 1 1 5924B82E
P 10150 5550
F 0 "#PWR042" H 10150 5400 50  0001 C CNN
F 1 "+3.3V" H 10150 5690 50  0000 C CNN
F 2 "" H 10150 5550 50  0000 C CNN
F 3 "" H 10150 5550 50  0000 C CNN
	1    10150 5550
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR043
U 1 1 5924B834
P 10150 4450
F 0 "#PWR043" H 10150 4200 50  0001 C CNN
F 1 "GND" H 10150 4300 50  0000 C CNN
F 2 "" H 10150 4450 50  0000 C CNN
F 3 "" H 10150 4450 50  0000 C CNN
	1    10150 4450
	0    1    1    0   
$EndComp
Wire Wire Line
	10150 5550 10200 5550
Wire Wire Line
	10150 4450 10200 4450
Text GLabel 4000 2200 1    60   Input ~ 0
MOSI
Text GLabel 4150 2200 1    60   Input ~ 0
MISO
Wire Wire Line
	4000 2200 4000 2450
Connection ~ 4000 2450
Wire Wire Line
	4150 2200 4150 2650
Connection ~ 4150 2650
Text GLabel 10100 4950 0    60   Input ~ 0
MOSI
Text GLabel 10100 5050 0    60   Input ~ 0
MISO
Wire Wire Line
	10200 4950 10100 4950
Wire Wire Line
	10200 5050 10100 5050
Text GLabel 10100 4850 0    60   Input ~ 0
Transceiver_CS
Text GLabel 3850 2200 1    60   Input ~ 0
SPI_CLK
Wire Wire Line
	3850 2200 3850 2550
Connection ~ 3850 2550
Text GLabel 10100 5150 0    60   Input ~ 0
SPI_CLK
Wire Wire Line
	10200 5150 10100 5150
Text GLabel 10100 5250 0    60   Input ~ 0
IRQ_SI_transceiver
Text GLabel 4150 4150 0    60   Input ~ 0
IRQ_SI_transceiver
Text GLabel 10100 5450 0    60   Input ~ 0
GPIO0_SI_transceiver
Text GLabel 10100 5350 0    60   Input ~ 0
GPIO1_SI_transceiver
Text GLabel 10100 4750 0    60   Input ~ 0
GPIO2_SI_transceiver
Text GLabel 10100 4650 0    60   Input ~ 0
GPIO3_SI_transceiver
Wire Wire Line
	10200 4650 10100 4650
Wire Wire Line
	10200 4750 10100 4750
Text GLabel 6750 4900 2    60   Input ~ 0
GPIO0_SI_transceiver
Text GLabel 6750 4750 2    60   Input ~ 0
GPIO1_SI_transceiver
Text GLabel 6750 4000 2    60   Input ~ 0
GPIO2_SI_transceiver
Text GLabel 6750 3850 2    60   Input ~ 0
GPIO3_SI_transceiver
Wire Wire Line
	850  1700 850  2150
Wire Wire Line
	850  1700 1300 1700
Wire Wire Line
	1400 1700 1400 2350
Wire Wire Line
	1400 2350 2000 2350
Connection ~ 2000 1600
$Sheet
S 2750 600  700  600 
U 5936309F
F0 "Switch_sheet1" 60
F1 "Switch_sheet.sch" 60
F2 "P_out" I R 3450 700 60 
F3 "GND" I L 2750 1150 60 
F4 "P_in" I L 2750 700 60 
F5 "P_switch" I L 2750 950 60 
$EndSheet
Wire Wire Line
	2750 700  2000 700 
$Comp
L GND #PWR044
U 1 1 5936555F
P 2700 1150
F 0 "#PWR044" H 2700 900 50  0001 C CNN
F 1 "GND" H 2700 1000 50  0000 C CNN
F 2 "" H 2700 1150 50  0000 C CNN
F 3 "" H 2700 1150 50  0000 C CNN
	1    2700 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 1150 2750 1150
Wire Wire Line
	2350 1600 2000 1600
Text GLabel 3900 4000 0    60   Input ~ 0
Servo_switch
Wire Wire Line
	4200 4000 3900 4000
Text GLabel 2700 950  0    60   Input ~ 0
Servo_switch
Wire Wire Line
	2750 950  2700 950 
Text GLabel 4100 2900 0    60   Input ~ 0
Camera_switch
Wire Wire Line
	4200 2950 4200 2900
Wire Wire Line
	4200 2900 4100 2900
Text GLabel 5350 950  0    60   Input ~ 0
Camera_switch
Text GLabel 7000 950  0    60   Input ~ 0
Heat_switch
Text GLabel 8600 950  0    60   Input ~ 0
Beacon_switch
$Comp
L CONN_01X04 I2C_DEBUG1
U 1 1 5936CCBA
P 8400 5500
F 0 "I2C_DEBUG1" H 8400 5750 50  0000 C CNN
F 1 "CONN_01X04" V 8500 5500 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-04_04x2.54mm_Straight" H 8400 5500 50  0001 C CNN
F 3 "" H 8400 5500 50  0000 C CNN
	1    8400 5500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8250 5700 8250 5750
Connection ~ 8250 5750
Wire Wire Line
	8350 5700 8350 5850
Connection ~ 8350 5850
Wire Wire Line
	8450 5700 8450 5950
Connection ~ 8450 5950
Wire Wire Line
	8550 5700 8550 6050
Connection ~ 8550 6050
Text GLabel 4150 4600 0    60   Input ~ 0
Heat_switch
Text GLabel 4150 4750 0    60   Input ~ 0
Beacon_switch
Wire Wire Line
	4200 4600 4150 4600
Wire Wire Line
	4200 4750 4150 4750
$Sheet
S 5400 600  700  600 
U 5936F90A
F0 "Switch_sheet4" 60
F1 "Switch_sheet.sch" 60
F2 "P_out" I R 6100 700 60 
F3 "GND" I L 5400 1150 60 
F4 "P_in" I L 5400 700 60 
F5 "P_switch" I L 5400 950 60 
$EndSheet
Wire Wire Line
	5400 700  4650 700 
$Comp
L GND #PWR045
U 1 1 5936F911
P 5350 1150
F 0 "#PWR045" H 5350 900 50  0001 C CNN
F 1 "GND" H 5350 1000 50  0000 C CNN
F 2 "" H 5350 1150 50  0000 C CNN
F 3 "" H 5350 1150 50  0000 C CNN
	1    5350 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 1150 5400 1150
Wire Wire Line
	5400 950  5350 950 
$Sheet
S 7050 600  700  600 
U 5936FD8E
F0 "Switch_sheet2" 60
F1 "Switch_sheet.sch" 60
F2 "P_out" I R 7750 700 60 
F3 "GND" I L 7050 1150 60 
F4 "P_in" I L 7050 700 60 
F5 "P_switch" I L 7050 950 60 
$EndSheet
Wire Wire Line
	7050 700  6300 700 
$Comp
L GND #PWR046
U 1 1 5936FD95
P 7000 1150
F 0 "#PWR046" H 7000 900 50  0001 C CNN
F 1 "GND" H 7000 1000 50  0000 C CNN
F 2 "" H 7000 1150 50  0000 C CNN
F 3 "" H 7000 1150 50  0000 C CNN
	1    7000 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 1150 7050 1150
Wire Wire Line
	7050 950  7000 950 
$Sheet
S 8650 600  700  600 
U 59370031
F0 "Switch_sheet3" 60
F1 "Switch_sheet.sch" 60
F2 "P_out" I R 9350 700 60 
F3 "GND" I L 8650 1150 60 
F4 "P_in" I L 8650 700 60 
F5 "P_switch" I L 8650 950 60 
$EndSheet
Wire Wire Line
	8650 700  7900 700 
$Comp
L GND #PWR047
U 1 1 59370038
P 8600 1150
F 0 "#PWR047" H 8600 900 50  0001 C CNN
F 1 "GND" H 8600 1000 50  0000 C CNN
F 2 "" H 8600 1150 50  0000 C CNN
F 3 "" H 8600 1150 50  0000 C CNN
	1    8600 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	8600 1150 8650 1150
Wire Wire Line
	8650 950  8600 950 
Wire Wire Line
	4650 700  4650 450 
Wire Wire Line
	2000 450  7900 450 
Connection ~ 2000 700 
Wire Wire Line
	6300 700  6300 450 
Connection ~ 4650 450 
Wire Wire Line
	7900 450  7900 700 
Connection ~ 6300 450 
$Comp
L StepDown U10
U 1 1 59374232
P 6600 1800
F 0 "U10" H 6600 1600 50  0000 C CNN
F 1 "StepDown" H 6600 2000 50  0000 C CNN
F 2 "LIB:step_down" H 6600 1800 50  0001 C CNN
F 3 "" H 6600 1800 50  0000 C CNN
	1    6600 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 5937423F
P 6600 2050
F 0 "#PWR048" H 6600 1800 50  0001 C CNN
F 1 "GND" H 6600 1900 50  0000 C CNN
F 2 "" H 6600 2050 50  0000 C CNN
F 3 "" H 6600 2050 50  0000 C CNN
	1    6600 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 2050 7150 2050
Connection ~ 6600 2050
Wire Wire Line
	6100 700  6200 700 
Wire Wire Line
	6200 700  6200 1750
Wire Wire Line
	7000 1750 7050 1750
Wire Wire Line
	6200 1550 7150 1550
Connection ~ 6200 1550
Connection ~ 6700 2050
Wire Wire Line
	6950 1850 6950 2200
Connection ~ 6950 2050
$Comp
L CONN_01X04 Camera_header1
U 1 1 59376B94
P 7350 1900
F 0 "Camera_header1" H 7350 2150 50  0000 C CNN
F 1 "CONN_01X04" V 7450 1900 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-04_04x2.54mm_Straight" H 7350 1900 50  0001 C CNN
F 3 "" H 7350 1900 50  0000 C CNN
	1    7350 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 1550 7150 1750
Wire Wire Line
	7050 1750 7050 1950
Wire Wire Line
	7050 1950 7150 1950
Wire Wire Line
	6950 1850 7150 1850
$Comp
L CONN_01X02 Heat_header1
U 1 1 5937962E
P 8450 1850
F 0 "Heat_header1" H 8450 2000 50  0000 C CNN
F 1 "CONN_01X02" V 8550 1850 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 8450 1850 50  0001 C CNN
F 3 "" H 8450 1850 50  0000 C CNN
	1    8450 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 700  7850 700 
Wire Wire Line
	7850 700  7850 1800
Wire Wire Line
	7850 1800 8250 1800
Wire Wire Line
	8250 1900 7850 1900
Wire Wire Line
	7850 1900 7850 2200
Wire Wire Line
	6950 2200 9000 2200
$Comp
L CONN_01X02 Beacon_header1
U 1 1 5937A682
P 9600 1850
F 0 "Beacon_header1" H 9600 2000 50  0000 C CNN
F 1 "CONN_01X02" V 9700 1850 50  0000 C CNN
F 2 "Connectors_Molex:Molex_SPOX-5267_22-03-5025_02x2.54mm_Straight" H 9600 1850 50  0001 C CNN
F 3 "" H 9600 1850 50  0000 C CNN
	1    9600 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1800 9400 700 
Wire Wire Line
	9400 700  9350 700 
Wire Wire Line
	9400 1900 9000 1900
Wire Wire Line
	9000 1900 9000 2200
Connection ~ 7850 2200
Wire Wire Line
	10200 4850 10100 4850
Wire Wire Line
	10200 5250 10100 5250
Wire Wire Line
	10200 5350 10100 5350
Wire Wire Line
	10200 5450 10100 5450
NoConn ~ 10200 4550
NoConn ~ 6300 2800
Wire Wire Line
	3750 2250 3700 2250
Wire Wire Line
	4200 2350 3700 2350
Wire Wire Line
	3700 2650 4200 2650
Wire Wire Line
	4100 3000 3700 3000
Wire Wire Line
	4150 3100 4200 3100
Wire Wire Line
	4050 3250 4200 3250
Wire Wire Line
	4050 3400 4200 3400
Wire Wire Line
	3900 3700 4200 3700
NoConn ~ 6300 5200
Wire Wire Line
	6750 4900 6300 4900
Wire Wire Line
	6750 4750 6300 4750
Wire Wire Line
	6750 3850 6300 3850
Wire Wire Line
	6750 3400 6300 3400
Wire Wire Line
	8000 2950 6300 2950
Wire Wire Line
	4200 4150 4150 4150
Wire Wire Line
	6750 3250 6300 3250
Wire Wire Line
	6750 3550 6300 3550
Wire Wire Line
	6750 3700 6300 3700
Wire Wire Line
	6750 4000 6300 4000
$Comp
L CONN_01X02 Heart_header1
U 1 1 59395AD3
P 6750 5100
F 0 "Heart_header1" H 7100 5050 50  0000 C CNN
F 1 "CONN_01X02" H 6850 4950 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 6750 5100 50  0001 C CNN
F 3 "" H 6750 5100 50  0000 C CNN
	1    6750 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 5050 6550 5050
$Comp
L GND #PWR049
U 1 1 59396597
P 6500 5200
F 0 "#PWR049" H 6500 4950 50  0001 C CNN
F 1 "GND" H 6500 5050 50  0000 C CNN
F 2 "" H 6500 5200 50  0000 C CNN
F 3 "" H 6500 5200 50  0000 C CNN
	1    6500 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5150 6500 5150
Wire Wire Line
	6500 5150 6500 5200
Wire Wire Line
	2800 5300 2750 5300
$Comp
L +5VA #PWR050
U 1 1 593FEF67
P 1600 5300
F 0 "#PWR050" H 1600 5150 50  0001 C CNN
F 1 "+5VA" H 1600 5440 50  0000 C CNN
F 2 "" H 1600 5300 50  0000 C CNN
F 3 "" H 1600 5300 50  0000 C CNN
	1    1600 5300
	0    -1   -1   0   
$EndComp
$Comp
L +5VA #PWR051
U 1 1 593FF6A2
P 1600 6900
F 0 "#PWR051" H 1600 6750 50  0001 C CNN
F 1 "+5VA" H 1600 7040 50  0000 C CNN
F 2 "" H 1600 6900 50  0000 C CNN
F 3 "" H 1600 6900 50  0000 C CNN
	1    1600 6900
	0    -1   -1   0   
$EndComp
$Comp
L +5VA #PWR052
U 1 1 59403847
P 1050 4650
F 0 "#PWR052" H 1050 4500 50  0001 C CNN
F 1 "+5VA" H 1050 4790 50  0000 C CNN
F 2 "" H 1050 4650 50  0000 C CNN
F 3 "" H 1050 4650 50  0000 C CNN
	1    1050 4650
	0    1    1    0   
$EndComp
$Comp
L +5VA #PWR053
U 1 1 594047E2
P 1050 5050
F 0 "#PWR053" H 1050 4900 50  0001 C CNN
F 1 "+5VA" H 1050 5190 50  0000 C CNN
F 2 "" H 1050 5050 50  0000 C CNN
F 3 "" H 1050 5050 50  0000 C CNN
	1    1050 5050
	0    1    1    0   
$EndComp
$Comp
L +5VA #PWR054
U 1 1 5940493E
P 1050 5450
F 0 "#PWR054" H 1050 5300 50  0001 C CNN
F 1 "+5VA" H 1050 5590 50  0000 C CNN
F 2 "" H 1050 5450 50  0000 C CNN
F 3 "" H 1050 5450 50  0000 C CNN
	1    1050 5450
	0    1    1    0   
$EndComp
$Comp
L +5VA #PWR055
U 1 1 59404B34
P 1050 5850
F 0 "#PWR055" H 1050 5700 50  0001 C CNN
F 1 "+5VA" H 1050 5990 50  0000 C CNN
F 2 "" H 1050 5850 50  0000 C CNN
F 3 "" H 1050 5850 50  0000 C CNN
	1    1050 5850
	0    1    1    0   
$EndComp
$Comp
L +5VA #PWR056
U 1 1 59404BF6
P 1050 6250
F 0 "#PWR056" H 1050 6100 50  0001 C CNN
F 1 "+5VA" H 1050 6390 50  0000 C CNN
F 2 "" H 1050 6250 50  0000 C CNN
F 3 "" H 1050 6250 50  0000 C CNN
	1    1050 6250
	0    1    1    0   
$EndComp
$Comp
L +5VA #PWR057
U 1 1 59404CB8
P 1050 6650
F 0 "#PWR057" H 1050 6500 50  0001 C CNN
F 1 "+5VA" H 1050 6790 50  0000 C CNN
F 2 "" H 1050 6650 50  0000 C CNN
F 3 "" H 1050 6650 50  0000 C CNN
	1    1050 6650
	0    1    1    0   
$EndComp
$Comp
L +5VA #PWR058
U 1 1 59404F48
P 1050 7050
F 0 "#PWR058" H 1050 6900 50  0001 C CNN
F 1 "+5VA" H 1050 7190 50  0000 C CNN
F 2 "" H 1050 7050 50  0000 C CNN
F 3 "" H 1050 7050 50  0000 C CNN
	1    1050 7050
	0    1    1    0   
$EndComp
$Comp
L +5VA #PWR059
U 1 1 5940500A
P 1050 7450
F 0 "#PWR059" H 1050 7300 50  0001 C CNN
F 1 "+5VA" H 1050 7590 50  0000 C CNN
F 2 "" H 1050 7450 50  0000 C CNN
F 3 "" H 1050 7450 50  0000 C CNN
	1    1050 7450
	0    1    1    0   
$EndComp
$Comp
L CONN_01X16 P10
U 1 1 59516B2C
P 6500 6550
F 0 "P10" H 6500 7400 50  0000 C CNN
F 1 "CONN_01X16" V 6600 6550 50  0000 C CNN
F 2 "Connectors_Molex:Molex_PicoBlade_53261-1771_17x1.25mm_Angled" H 6500 6550 50  0001 C CNN
F 3 "" H 6500 6550 50  0000 C CNN
	1    6500 6550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X16 P9
U 1 1 5951706F
P 6200 6550
F 0 "P9" H 6200 7400 50  0000 C CNN
F 1 "CONN_01X16" V 6300 6550 50  0000 C CNN
F 2 "Connectors_Molex:Molex_PicoBlade_53261-1771_17x1.25mm_Angled" H 6200 6550 50  0001 C CNN
F 3 "" H 6200 6550 50  0000 C CNN
	1    6200 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 5800 6300 5800
Wire Wire Line
	5700 5900 6300 5900
Wire Wire Line
	5700 6000 6300 6000
Wire Wire Line
	5700 6100 6300 6100
Wire Wire Line
	5700 6200 6300 6200
Wire Wire Line
	5700 6300 6300 6300
Wire Wire Line
	5700 6400 6300 6400
Wire Wire Line
	5700 6500 6300 6500
Wire Wire Line
	6000 6600 6800 6600
Wire Wire Line
	5700 6700 6300 6700
Wire Wire Line
	5700 6800 6300 6800
Wire Wire Line
	5700 6900 6300 6900
Wire Wire Line
	5700 7000 6300 7000
Wire Wire Line
	5700 7100 6300 7100
Wire Wire Line
	5700 7200 6300 7200
Wire Wire Line
	5700 7300 6300 7300
Text GLabel 5700 6500 0    60   Input ~ 0
servo1_signal
Text GLabel 5700 6400 0    60   Input ~ 0
servo2_signal
Text GLabel 5700 6300 0    60   Input ~ 0
servo3_signal
Text GLabel 5700 6200 0    60   Input ~ 0
servo4_signal
Text GLabel 5700 6100 0    60   Input ~ 0
servo5_signal
Text GLabel 5700 6000 0    60   Input ~ 0
servo6_signal
Text GLabel 5700 5900 0    60   Input ~ 0
servo7_signal
Text GLabel 5700 5800 0    60   Input ~ 0
servo8_signal
Connection ~ 6000 5800
Connection ~ 6000 5900
Connection ~ 6000 6000
Connection ~ 6000 6100
Connection ~ 6000 6200
Connection ~ 6000 6300
Connection ~ 6000 6400
Connection ~ 6000 6500
Wire Wire Line
	6400 5050 6400 5650
Wire Wire Line
	6400 5650 6800 5650
Wire Wire Line
	6800 5650 6800 6600
Connection ~ 6300 6600
Connection ~ 6400 5050
Text GLabel 5700 6700 0    60   Input ~ 0
Camera_switch
Connection ~ 6000 6700
Text GLabel 5700 6800 0    60   Input ~ 0
Servo_switch
Connection ~ 6000 6800
Text GLabel 5700 6900 0    60   Input ~ 0
Heat_switch
Text GLabel 5700 7000 0    60   Input ~ 0
Beacon_switch
Connection ~ 6000 6900
Connection ~ 6000 7000
Text GLabel 5700 7100 0    60   Input ~ 0
I2C_SCL
Connection ~ 6000 7100
$Comp
L GND #PWR060
U 1 1 5951E721
P 5700 7200
F 0 "#PWR060" H 5700 6950 50  0001 C CNN
F 1 "GND" H 5700 7250 50  0000 C CNN
F 2 "" H 5700 7200 50  0000 C CNN
F 3 "" H 5700 7200 50  0000 C CNN
	1    5700 7200
	0    1    1    0   
$EndComp
Connection ~ 6000 7200
$Comp
L +3.3V #PWR061
U 1 1 5951F1DC
P 5700 7300
F 0 "#PWR061" H 5700 7150 50  0001 C CNN
F 1 "+3.3V" H 5700 7500 50  0000 C CNN
F 2 "" H 5700 7300 50  0000 C CNN
F 3 "" H 5700 7300 50  0000 C CNN
	1    5700 7300
	0    -1   -1   0   
$EndComp
Connection ~ 6000 7300
$Comp
L CONN_01X01 P11
U 1 1 59523ADE
P 6200 7400
F 0 "P11" H 6200 7500 50  0000 C CNN
F 1 "CONN_01X01" V 6300 7400 50  0000 C CNN
F 2 "Connectors_Samtec:SL-101-X-XX_1x01" H 6200 7400 50  0001 C CNN
F 3 "" H 6200 7400 50  0000 C CNN
	1    6200 7400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P12
U 1 1 59523C9D
P 6500 7400
F 0 "P12" H 6500 7500 50  0000 C CNN
F 1 "CONN_01X01" V 6600 7400 50  0000 C CNN
F 2 "Connectors_Samtec:SL-101-X-XX_1x01" H 6500 7400 50  0001 C CNN
F 3 "" H 6500 7400 50  0000 C CNN
	1    6500 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 7400 6300 7400
Connection ~ 6000 7400
$Comp
L +5VD #PWR062
U 1 1 59526758
P 5700 7400
F 0 "#PWR062" H 5700 7250 50  0001 C CNN
F 1 "+5VD" H 5650 7350 50  0000 C CNN
F 2 "" H 5700 7400 50  0000 C CNN
F 3 "" H 5700 7400 50  0000 C CNN
	1    5700 7400
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P13
U 1 1 5963C9D5
P 6200 7500
F 0 "P13" H 6200 7600 50  0000 C CNN
F 1 "CONN_01X01" V 6300 7500 50  0000 C CNN
F 2 "Connectors_Samtec:SL-101-X-XX_1x01" H 6200 7500 50  0001 C CNN
F 3 "" H 6200 7500 50  0000 C CNN
	1    6200 7500
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P14
U 1 1 5963CAB3
P 6500 7500
F 0 "P14" H 6500 7600 50  0000 C CNN
F 1 "CONN_01X01" V 6600 7500 50  0000 C CNN
F 2 "Connectors_Samtec:SL-101-X-XX_1x01" H 6500 7500 50  0001 C CNN
F 3 "" H 6500 7500 50  0000 C CNN
	1    6500 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 7500 6300 7500
Connection ~ 6000 7500
Text GLabel 5700 7500 0    60   Input ~ 0
I2C_SDA
$EndSCHEMATC
