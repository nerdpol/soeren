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
Sheet 3 5
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
L BC817-40 Q1
U 1 1 593634BF
P 4750 2550
AR Path="/5936309F/593634BF" Ref="Q1"  Part="1" 
AR Path="/5936F90A/593634BF" Ref="Q2"  Part="1" 
AR Path="/5936FD8E/593634BF" Ref="Q3"  Part="1" 
AR Path="/59370031/593634BF" Ref="Q4"  Part="1" 
F 0 "Q2" H 4950 2625 50  0000 L CNN
F 1 "BC817-40" H 4950 2550 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4950 2475 50  0000 L CIN
F 3 "" H 4750 2550 50  0000 L CNN
	1    4750 2550
	1    0    0    -1  
$EndComp
$Comp
L R 1k1
U 1 1 593634C6
P 4400 2550
AR Path="/5936309F/593634C6" Ref="1k1"  Part="1" 
AR Path="/5936F90A/593634C6" Ref="1k2"  Part="1" 
AR Path="/5936FD8E/593634C6" Ref="1k3"  Part="1" 
AR Path="/59370031/593634C6" Ref="1k4"  Part="1" 
F 0 "1k2" V 4480 2550 50  0000 C CNN
F 1 "R" V 4400 2550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4330 2550 50  0001 C CNN
F 3 "" H 4400 2550 50  0000 C CNN
	1    4400 2550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR063
U 1 1 593634CD
P 4850 2800
AR Path="/5936309F/593634CD" Ref="#PWR063"  Part="1" 
AR Path="/5936F90A/593634CD" Ref="#PWR064"  Part="1" 
AR Path="/5936FD8E/593634CD" Ref="#PWR065"  Part="1" 
AR Path="/59370031/593634CD" Ref="#PWR066"  Part="1" 
F 0 "#PWR064" H 4850 2550 50  0001 C CNN
F 1 "GND" H 4850 2650 50  0000 C CNN
F 2 "" H 4850 2800 50  0000 C CNN
F 3 "" H 4850 2800 50  0000 C CNN
	1    4850 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2800 4850 2750
Wire Wire Line
	4550 2550 4550 2550
Wire Wire Line
	4850 2350 4850 2300
Wire Wire Line
	4200 2000 4650 2000
$Comp
L R 100k1
U 1 1 593634DF
P 4500 2200
AR Path="/5936309F/593634DF" Ref="100k1"  Part="1" 
AR Path="/5936F90A/593634DF" Ref="100k2"  Part="1" 
AR Path="/5936FD8E/593634DF" Ref="100k3"  Part="1" 
AR Path="/59370031/593634DF" Ref="100k4"  Part="1" 
F 0 "100k2" V 4580 2200 50  0000 C CNN
F 1 "R" V 4500 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 2200 50  0001 C CNN
F 3 "" H 4500 2200 50  0000 C CNN
	1    4500 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 2050 4500 2000
Connection ~ 4500 2000
Wire Wire Line
	4500 2350 4850 2350
$Comp
L Q_PMOS_GSD DMP3099L1
U 1 1 59363580
P 4850 2100
AR Path="/5936309F/59363580" Ref="DMP3099L1"  Part="1" 
AR Path="/5936F90A/59363580" Ref="DMP3099L2"  Part="1" 
AR Path="/5936FD8E/59363580" Ref="DMP3099L3"  Part="1" 
AR Path="/59370031/59363580" Ref="DMP3099L4"  Part="1" 
F 0 "DMP3099L2" H 5050 2150 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 5050 2050 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 5050 2200 50  0001 C CNN
F 3 "" H 4850 2100 50  0000 C CNN
	1    4850 2100
	0    1    -1   0   
$EndComp
Wire Wire Line
	5050 2000 5600 2000
Wire Wire Line
	4200 2750 5600 2750
Connection ~ 4850 2750
$Comp
L R R1
U 1 1 59363765
P 4850 1800
AR Path="/5936309F/59363765" Ref="R1"  Part="1" 
AR Path="/5936F90A/59363765" Ref="R2"  Part="1" 
AR Path="/5936FD8E/59363765" Ref="R3"  Part="1" 
AR Path="/59370031/59363765" Ref="R4"  Part="1" 
F 0 "R2" V 4930 1800 50  0000 C CNN
F 1 "R" V 4850 1800 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4780 1800 50  0001 C CNN
F 3 "" H 4850 1800 50  0000 C CNN
	1    4850 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 1800 4650 1800
Wire Wire Line
	4650 1800 4650 2000
Wire Wire Line
	5000 1800 5050 1800
Wire Wire Line
	5050 1800 5050 2000
Text HLabel 5600 2000 2    60   Input ~ 0
P_out
Text HLabel 5600 2750 2    60   Input ~ 0
GND
Text HLabel 4200 2750 0    60   Input ~ 0
GND
Text HLabel 4200 2000 0    60   Input ~ 0
P_in
Text HLabel 4200 2550 0    60   Input ~ 0
P_switch
Wire Wire Line
	4250 2550 4200 2550
$EndSCHEMATC
