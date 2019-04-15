#Weelchair tracking for basketball players


## PROJECT DESCRIPTION
*by Max, Fabian and Daniël*

The goal of this project is to create a smart sports wheelchair which is able to monitor the consumed energy of a wheelchair basketball player in real time. This provides valuable insights for player and coach during training exercises. For example, the current system allows a coach to view the energy the player has spent in relation to the heartrate of the user. The system then determines the fitness level of the user based on these parameters.

#Current functionality

-	Displays heartrate and fitness level on LED ring.
- Enables insight in multiple variables of movement on Grafana.
						- Velocity
						-	Acceleration
						- Distance moved
						- Rotation angle
						- Spent kcal
						- Heartrate
						- Fitness rating (calculated from spent kcal versus heartrate)
						- Tilt angle (wheelie meter)					

#Data flow

#COMPONENTS

The components and their connections are listed below.

ARDUINO MEGA
	Location: the wheelchair main frame
	Script:	Chairbase.ino
	Connected to: 	RASPBERRY PI (Physical, USB B)
									LED RING (Physical, wires)
									BNO055 (Physical, wires)


ADAFRUIT FEATHER BLUEFRUIT 32u4
	Location: the right wheel
	Script:Rightsportswheelblefeather.ino
	Connected to: 	RASPBERRY PI (Bluetooth connection)
									BNO055 (Physical, wires)
									POWERBANK (Physical, Micro USB)

RASPBERRY PI
	Location: the wheelchair main frame
	Script:Rpi_sportswheelchair.py
	Connected to: 	ARDUINO MEGA (Physical, wires)
									POWERBANK (Physical, Micro USB)
LED RING
	Location: the back of wheelchair backseat
	Connected to:		ARDUINO MEGA (Physical, wires)

BNO055 IMU x2
	Location: the center turning point of the wheelchair
	Location: the center turning point of the right wheel
	Connected to:		ARDUINO MEGA (Physical, wires)
									ADAFRUIT FEATHER (Physical, wires)

HEARTRATE MONITOR WRISTBAND (MIO LINK)
	Location: the user's wrist.
	Connected to:		RASPBERRY PI (Bluetooth)

POWERBANK x2
	Location:	the wheelchair main frame
	Location: the right wheel
	Connected to:		RASPBERRY PI (Physical, USB)
									ADAFRUIT FEATHER (Physical, Micro USB)

USB CABLE
	Location: between Raspberry Pi and Powerbank

MICRO USB CABLE
	Location: between Adafruit Bluefruit and Powerbank

USB B CABLE
	Location: between Raspberry Pi and Arduino Mega.

MALE - MALE JUMPERWIRES

FEMALE - MALE JUMPERWIRES

HEADERS BNO055

#INSTALLATION

The collection of data and the display of user performance is achieved by the use of multiple components.

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


__*INPUT*__
* Relative Position (speed, linear acceleration)
* Rotation, Rotational acceleration
* Heartbeat

__*OUTPUT*__
* Basic information on Grafana
* LED ring indicating fatigue and heartbeat

## SENSORS

To achieve the project goal, data will be collected using the following sensors.

__*INPUT*__
* Orientation sensor
The orientation sensor consists of a gyroscope, accelerometers and magnetometers. The standard module from Adafruit will provide the relative position the sensor is in, with which the direction of travel, can be determined. Combined with the speedometer, the position relative to the starting position can be determined.

* Heartrate sensor
An expansion on the wheelchair project is a heartrate monitor wearable. This can be placed on the arm of the athlete in order to more reliably predict the energy usage.

*Of the sensors above, the speedometer (Hall sensor + magnet) and the Arduino HR sensor are not in the list.*


## ACTUATORS

To communicate the gained insights back to the user, the wheelchair will use certain actuators to notify the user.

__*OUTPUT*__
* RGB LED ring (Neopixel)
To display fatigue, heart rate and more, an LED ring will be used, preferably Adafruit's Neopixel ring. The ease of the Neopixel is that it is expandable to almost infinite length while still using only three cables (positive, ground and data) and thus three pins on the Arduino. A disadvantage is that it can only be controlled by the Arduino, not for the Raspberry Pi.
With the Neopixel ring, it is possible to create patterns of coloured LED's, which allow for easy communication to the end user.

*Of the actuators above, the RGB LED Ring can be provided by us if neccesairy.*

__*Testing*__
* The testing method consisted of an iterative process which first enabled the Arduino to collect data from the orientation sensors. After that, connection between Bluefruit and Raspberry Pi were added and tested. This was followed by adding the other sensors part by part, continuously testing using serial data and the LED display as reference points. At the end of the project, all sensors, calculation and connection methods worked as intended. The data was also successfully displayed using Grafana.
