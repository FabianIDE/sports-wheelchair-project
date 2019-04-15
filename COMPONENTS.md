## PROJECT DOCUMENTATION

* [Project Description](README.md)
* [Sensors & Actuators](SENSORS_ACTUATORS.md)
* [Components](COMPONENTS.md)
* [Installation](INSTALLATION.md)
* [Testing](TESTING.md)
* [Changelog](CHANGELOG.md)

# COMPONENTS

The components and their connections are listed below.

##### ARDUINO MEGA

*_Location_*

The wheelchair main frame  

*_Script_*

Chairbase.ino  

*_Connected to_*

1.	RASPBERRY PI (Physical, USB B
1.	RING (Physical, wires
1.	BNO055 (Physical, wires)  


##### ADAFRUIT FEATHER BLUEFRUIT

*_Location_*

The right wheel.

*_Script_*

Rightsportswheelblefeather.ino  

*_Connected to_*

1. RASPBERRY PI (Bluetooth connection
1. BNO055 (Physical, wires)
1. POWERBANK (Physical, Micro USB)

##### RASPBERRY PI

*_Location_*

The wheelchair main frame.

*_Script_*

Rpi_sportswheelchair.py

*_Connected to_*

1. ARDUINO MEGA (Physical, wires)
1. POWERBANK (Physical, Micro USB)

##### LED RING

*_Location_*

The back of the wheelchair backseat.

*_Connected to_*

1. ARDUINO MEGA (Physical, wires)

##### BNO055 IMU x2

*_Location_*

The center turning point of the wheelchair.

*_Location_*

The center turning point of the right wheel.

*_Connected to_*		

1. ARDUINO MEGA (Physical, wires)
1. ADAFRUIT FEATHER (Physical, wires)

##### HEARTRATE MONITOR WRISTBAND (MIO LINK)

*_Location_*

The user's wrist.

*_Connected to_*

1. RASPBERRY PI (Bluetooth)

##### POWERBANK x2

*_Location_*

The wheelchair main frame.

*_Location_*

The right wheel.

*_Connected to_*		

1. RASPBERRY PI (Physical, USB)
1. ADAFRUIT FEATHER (Physical, Micro USB)

##### USB CABLE

*_Location_*

Between the Raspberry Pi and the Powerbank.

##### MICRO USB CABLE

*_Location_*

Between the Adafruit Bluefruit and the Powerbank

##### USB B CABLE

*_Location_*

Between the Raspberry Pi and the Arduino Mega.

##### MALE - MALE JUMPERWIRES

##### FEMALE - MALE JUMPERWIRES

##### HEADERS BNO055
