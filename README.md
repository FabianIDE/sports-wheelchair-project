#Weelchair tracking for basketball players


## PROJECT DESCRIPTION
*by Max, Fabian and Daniël*

The goal of this project is to create a smart sports wheelchair which is able to monitor the consumed energy of a wheelchair basketball player in real time. This provides valuable insights for player and coach during training exercises. For example, the current system allows a coach to view the energy the player has spent in relation to the heartrate of the user. The system then determines the fitness level of the user based on these parameters.

INSTALLATION

The collection of data and the display of user performance is achieved by the use of multiple components.

STEPS
1.	Download 	the folllowing files from github (wheelchair-design-platform/SportsTracker_V1_Stable):
							Chairbase.ino
							Rightsportswheelblefeather.ino
							Rpi_sportswheelchair.py
							BluefruitConfig.h
2.	Download Libraries: [FIMXE]
3.	Install Libraries:	[FIXME]
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
17. Connect the Arduino Mega and Raspberry Pi using datacable [FIXME].
18. Connect the Raspberry Pi and Powerbank using USB cable.
19. Connect the wires between the Adafruit Feather and the BNO055 according to image (3).
20. Connect the Adafruit Feather and Powerbank using Micro USB cable.
21.	Bluetooth connection settings [FIXME].
22.	DCD connection settings [FIXME]. TOKENS ETC.
23. Grafana connection settings [FIXME].
24.	Equip the heartrate monitor.
25.	Start the heartrate monitor.
26.	Find the Raspberry Pi on your network.
27. Connect to the Raspberry Pi using ssh.
28. Execute the Rpi_sportswheelchair.py file.
29. Read values from the Grafana webpage.

The components and their connections are listed below.

ARDUINO MEGA
	Location: the wheelchair main frame
	Script:	Chairbase.ino
	Connected to: 	RASPBERRY PI (Physical, SERIAL)
									LED RING (Physical, wires)
									BNO055 (Physical, wires)


ADAFRUIT FEATHER BLUEFRUIT 32u4
	Location: the right wheel
	Script:Rightsportswheelblefeather.ino
	Connected to: 	RASPBERRY PI (Bluetooth connection)
									BNO055 (Physical, wires)
									POWERBANK (Physical, USB)

RASPBERRY PI
	Location: the wheelchair main frame
	Script:Rpi_sportswheelchair.py
	Connected to: 	ARDUINO MEGA (Physical, wires)
									POWERBANK (Physical, USB)
LED RING
	Location: the back of wheelchair backseat
	Connected to:		ARDUINO MEGA (Physical, wires)

BNO055 IMU x2
	Location: the center turning point of the wheelchair
	Location: the center turning point of the right wheel
	Connected to:		ARDUINO MEGA (Physical, wires)
									ADAFRUIT FEATHER (Physical, wires)

HEARTRATE MONITOR WRISTBAND
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

SERIAL DATACABLE
	Location: between Raspberry Pi and Arduino Mega.

MALE - MALE JUMPERWIRES

FEMALE - MALE JUMPERWIRES

PINSTRIP BNO055


#Program steps

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

__*OPTIONAL EXPANTION*__
* A webapp showing the live position and direction of players


## SENSORS

To archieve the project goal, data will be collected using the following sensors.

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



















-----------------------------------------------------------------------------------

Wheelchair Design Platform is a repository that contains some resources to help
designers and developers speak the same language, and work together towards
addressing relevant challenges for wheelchair users. It is a collection of
workshop materials, code examples and also a compilation of resources to foster
a prospering research and design community around wheelchair users.


![IoT1 Exhibition](/docs/workshops/images/iot1_exhibition.jpg)

## Workshops

* [Getting started](/docs/workshops/GettingStarted.md)
* [Workshop 1: Building an Internet-Connected Wheelchair](/docs/workshops/Workshop1.md)
* [Workshop 2: Integrating and Visualising Sensor-Based Data](/docs/workshops/Workshop2.md)
* [Workshop 3: Developing Algorithms and Controlling Actuators](/docs/workshops/Workshop3.md)
* [Workshop 4: Developing and Conducting a Data Collection Campaign](/docs/workshops/Workshop4.md)
* [Workshop 5: Implementing a Machine Learning Pipeline](/docs/workshops/Workshop5.md)
* [Workshop 6: Developing a Product Analytics Dashboard](/docs/workshops/Workshop6.md)

## Resources

* This platform uses two programming languages, Python on computers and C on
micro-controllers. While descriptions and examples of code should help you
get started, you can find some additional resources
[here](/docs/resources/software.md "Python and C resources").

* Documentation of your project is key,
[here are some tips and examples](/docs/resources/documentation.md "Documentation tips and examples").

* [Git manipulation such as Pull Request](/docs/resources/git.md "Git manipulation").

## Main Components

__**Disclaimer:**__ the design of this platform focuses on flexibility and
technology exploration rather than optimisation.

The main design includes a Raspberry Pi 3 and an Arduino Mega 2560 on the wheelchair frame.

The Arduino Mega is the micro-controller of the platform. Fixed on the main frame of the wheelchair,
it can collect data from sensors (e.g. force sensors, accelerometers), and trigger actions from actuators
(e.g. LEDs, vibration motors).

More on the Arduino Mega can be found [here](/docs/resources/arduino.md "Arduino resources").

Raspberry Pi is a small computer. It is also fixed to the main frame of the wheelchair,
where it can:
* interact with the Arduino Mega via USB to receive data and transmit commands;
* interact with the Internet to transmit commands and receive data;
* store data locally in files;
* run (machine learning) algorithms.

More on the Raspberry Pi can be found [here](/docs/resources/raspberrypi.md "Raspberry Pi resources").

These components fit together as shown on the following diagram. A large powerbank
powers the Raspberry Pi. The Arduino Mega communicates and receives power from the
Raspberry Pi via USB. A Feather (Arduino-like development board) on the wheel connects to
the Raspberry Pi via Bluetooth to sense and actuate from the wheel.

![Main Wheelchair components](/docs/workshops/images/wheechair-components.png)

## List of suggested components:

On the frame:

* 1 Raspberry Pi 3B;
* 1 SD card (Some come directly with NOOBS installed);
* 1 Arduino Mega;
* 1 Large power bank;
* 1 large breadboard;
* 1 USB cable A/micro (Powerbank to Raspberry Pi);
* 1 USB cable A/B (Raspberry Pi to Arduino Mega).

On the wheel:

* 1 Feather (Bluetooth enabled);
* 1 small power bank;
* 1 small breadboard;
* 1 USB cable A/B (power bank to Arduino Uno).


## Contact and Existing projects

* [The hiking wheelchair](https://github.com/cprecioso/wheelchair-design-platform)
* [The EDU wheelchair](https://github.com/ctsai-1/wheelchair-design-platform)
* [Weelchair tracking for basketball players](https://github.com/FabianIDE/wheelchair-design-platform)
* [Disco Wheelchair](https://github.com/MatthijsBrem/wheelchair-design-platform)
* [Wheelchair Madness 2222](https://github.com/pherkan/wheelchair-design-platform/tree/master/wheelchair)
* [Who is sitting?](https://github.com/Rosanfoppen/wheelchair-design-platform/tree/master/wheelchair)
* [Magic Wheelchair](https://github.com/Yuciena/wheelchair-design-platform)
* [Yoga Wheelchair](https://github.com/artgomad/wheelchair-design-platform)


Feel free to contact us at jacky@datacentricdesign.org. We welcome feedback, pull requests
or links to your project.
