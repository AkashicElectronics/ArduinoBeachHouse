# ArduinoBeachHouse
Code used in ArduinoBeachHouse project  

PINOUT:

(see attached jpg for LCD screen schematic)

0 - Bluetooth    //remember that rx goes to tx of bluetooth
1 - Bluetooth   //remember that tx goes to rx of bluetooth
2 - LCD
3 - LCD
4 - LCD
5 - LCD
6 - Data WS2812 array 
7 - Button Input
8 - N/A
9 - Servo 1
10 - Servo 2
11 - LCD
12 - LCD
13 - N/A

HARDWARE:
Arduino Uno
HC-06 Blueetooth Receiver
Servo Motors ; generic rc type 180 degree radius
LCD Screen ; 1602 type
Button ; generic
LED Array : 8 x 8 WS2812 strips hand wired and powered on front and back sides for color balance and heat alleviation 

120Vac --> 5Vdc power supply
Hardware is powered directly from power supply
Arduino is also powered directly from power supply
Common ground is established via GND bus of power supply

Arduino CAN be programmed while the unit is powered up from the power supply.  Two 5V power supplies in parrallel are still 5V.  The current is summative however the contribution of millamps from the computer will by no means overheat the circuit.  

AKASHIC ELECTRONICS
July 2020, -EL










