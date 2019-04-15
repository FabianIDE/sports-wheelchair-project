## INSTALLATION



 After collecting all the components as specified in [Components](workshops/GettingStarted.md)


STEPS
1.	Download 	the folllowing files from github (wheelchair-design-platform/SportsTracker_V1_Stable):
							Chairbase.ino
							Rightsportswheelblefeather.ino
							Rpi_sportswheelchair.py
							BluefruitConfig.h
2.	Download & install Libraries: BNO055
												ADAFRUIT NEOPIXEL
												ADAFRUIT nRF51 BLE
4.  Upload Chairbase.ino to the Arduino Mega.
5.	Upload Rightsportswheelblefeather.ino to the Adafruit Feather.
6.	Upload Rpi_sportswheelchair.py to the Raspberry Pi.				
7.	Secure Arduino Mega to the wheelchair main frame.
8.	Secure Adafruit Feather to the right wheel.
9.	Secure Powerbank to the right wheel.
10.	Secure Powerbank to the wheelchair main frame.
11.	Secure Raspberry Pi to the wheelchair main frame.
12.	Secure LED ring to the back of the wheelchair.
13.	Secure BNO055 to the wheelchair main frame.
14.	Secure BNO055 on the central turning point of the right wheel.
15.	Connect the wires between the Arduino Mega and the BNO055 according to image (1).
16. Connect the wires between the Arduino Mega and the LED ring according to image (2).
17. Connect the Arduino Mega and Raspberry Pi using USB B cable.
18. Connect the Raspberry Pi and Powerbank using USB cable.
19. Connect the wires between the Adafruit Feather and the BNO055 according to image (3).
20. Connect the Adafruit Feather and Powerbank using Micro USB cable.
21.	Find & set Feather UUID.
22.	Find & set DCD thing token (see DCD website).
23. Find and select the correct data to display in Grafana.
24.	Equip the heartrate monitor.
25.	Start the heartrate monitor.
26.	Find the Raspberry Pi on your network.
27. Connect to the Raspberry Pi using ssh.
28. Execute the Rpi_sportswheelchair.py file.
29. Read values from the Grafana webpage.

The steps which the program takes in order to display the fitness rating to the coach are:

1.  Measure the rotation of the right wheel.
2.  Measure the travelled distance of the wheelchair.
3.  Measure the heartrate of the user.
4.  Combine the collected data to define how much energy the user has spend so far.
5.	Judge fitness based on heartrate and energy usage.
7.  Use the LED ring to display this data to the coach.
