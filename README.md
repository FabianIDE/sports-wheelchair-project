#Weelchair tracking for basketball players


## PROJECT DESCRIPTION
*by Max, Fabian and Daniël*

The goal of this project is to create a smart sports wheelchair which is able to monitor the consumed energy of a wheelchair basketball player in real time. This provides valuable insights for player and coach during training exercises.

INSTALLATION

ARDUINO MEGA
	Location: the wheelchair main frame
	Script:	Chairbase.ino
	Connected to: 	RASPBERRY PI (Physical, wires)
			LED RING (Physical, wires)
ADAFRUIT FEATHER BLUEFRUIT 32u4
	Location: the right wheel
	Script:Rightsportswheelblefeather.ino
	Connected to: 	RASPBERRY PI (Bluetooth connection)
			BNO055
RASPBERRY PI	
	Location: the wheelchair main frame
	Script:Rpi_sportswheelchair.py
	Connected to: 	ARDUINO MEGA (Physical, wires)
			
LED RING
	Location: the back of wheelchair backseat
	Connected to:
BNO055 IMU x2
	Location: the center turning point of the wheelchair
	Location: the center turning point of the right wheel
	Connected to:
HEARTRATE MONITOR WRISTBAND
	Location: the user's wrist.
	Connected to:






#steps as defined on 08.03.2019

1.  Measure the rotation of the right wheel.
2.  Measure the rotation of the whole wheelchair.
3.  Combine both measurements to define the movement of both wheels.
4.  Use the movement of both wheels to determine how much energy is used by the user.
5.  Measure the heartrate of the user.
6.  Combine the collected data to define how much energy the user has spend so far.   
7.  Use the LED ring to display this data to the coach.


__*INPUT*__
* Relative Position (speed, acceleration)
* Rotation
* Weight
* Heartbeat

__*OUTPUT*__
* Basic information on Grafana
* LED strip indicating fatigue and heartbeat

__*OPTIONAL EXPANTION*__
* A webapp showing the live position and direction of players


## SENSORS

To archieve the project goal, data will be collected using the following sensors.

__*INPUT*__	
* Speedometer (Hall sensor)
The speedometer collects data by counting the amount of revelations of the wheels during a certain time. The speedometer conists of two Hall sensors connected to the frame of the wheelchair and a magnet connected to one of the spokes of the wheel. The Arduino is able to count the time of each wheel revelation and the direction the revelation is in.

* Orientation sensor
The orientation sensor consists of a gyroscope, accelerometers and magnetometers. The standard module from Adafruit will provide the relative position the sensor is in, with which the direction of travel, can be determined. Combined with the speedometer, the position relative to the starting position can be determined.

* Pressure sensors
With a pressure sensor the weight of the player can be determined, which, in combination with the sensors above, can be used for calculations in energy usage.

* Heartrate sensor
An expansion on the wheelchair project is a heartrate monitor wearable. This can be placed on the arm of the athlete in order to more reliably predict the energy usage.

*Of the sensors above, the speedometer (Hall sensor + magnet) and the Arduino HR sensor are not in the list.*


## ACTUATORS

To communicate the gained insights back to the user, the wheelchair will use certain actuators to notify the user.

__*OUTPUT*__
* RGB LED ring (Neopixel)
To display fatigue, heart rate and more, an LED ring will be used, preferably Adafruit's Neopixel ring. The ease of the Neopixel is that it is expandable to almost infinite length while still using only three cables (positive, ground and data) and thus three pins on the Arduino. A disadvantage is that it can only be controlled by the Arduino, not for the Raspberry Pi.
With the Neopixel ring, it is possible to create patterns of coloured LED's, which allow for easy communication to the end user.

* Speaker
A speaker can be used to send the user audio signals regarding the performance at a certain time. For example, when a player's heartrate exceeds a certain threshold for a prolonged time.

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
