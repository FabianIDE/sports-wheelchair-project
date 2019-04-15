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

_*Location*_

The wheelchair main frame  

_*Script*_

Chairbase.ino  

_*Connected to*_

1.	RASPBERRY PI (Physical, USB B
1.	RING (Physical, wires
1.	BNO055 (Physical, wires)  


##### ADAFRUIT FEATHER BLUEFRUIT

_*Location*_

The right wheel.

_*Script*_

Rightsportswheelblefeather.ino  

_*Connected to*_

1. RASPBERRY PI (Bluetooth connection
1. BNO055 (Physical, wires)
1. POWERBANK (Physical, Micro USB)

##### RASPBERRY PI

_*Location*_

The wheelchair main frame.

_*Script*_

Rpi_sportswheelchair.py

_*Connected to*_

1. ARDUINO MEGA (Physical, wires)
1. POWERBANK (Physical, Micro USB)

##### LED RING

_*Location*_

The back of the wheelchair backseat.

_*Connected to*_

1. ARDUINO MEGA (Physical, wires)

##### BNO055 IMU x2

_*Location*_

The center turning point of the wheelchair.

_*Location*_

The center turning point of the right wheel.

_*Connected to*_		

1. ARDUINO MEGA (Physical, wires)
1. ADAFRUIT FEATHER (Physical, wires)

##### HEARTRATE MONITOR WRISTBAND (MIO LINK)

_*Location*_

The user's wrist.

_*Connected to*_

1. RASPBERRY PI (Bluetooth)

##### POWERBANK x2

_*Location*_

The wheelchair main frame.

_*Location*_

The right wheel.

_*Connected to*_		

1. RASPBERRY PI (Physical, USB)
1. ADAFRUIT FEATHER (Physical, Micro USB)

##### USB CABLE

_*Location*_

Between the Raspberry Pi and the Powerbank.

##### MICRO USB CABLE

_*Location*_

Between the Adafruit Bluefruit and the Powerbank

##### USB B CABLE

_*Location*_

Between the Raspberry Pi and the Arduino Mega.

##### MALE - MALE JUMPERWIRES

##### FEMALE - MALE JUMPERWIRES

##### HEADERS BNO055
