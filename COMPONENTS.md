#### MENU

[Project Description](README.md) - [Sensors & Actuators](SENSORS_ACTUATORS.md) - [Components](COMPONENTS.md) - [Installation](INSTALLATION.md) - [Testing](TESTING.md) -  [Changelog](CHANGELOG.md)

# COMPONENTS

The components and their connections are listed below.

##### ARDUINO MEGA

**Location**

The wheelchair main frame  .

**Script**

Chairbase.ino  

**Connected to**

1.	RASPBERRY PI (Physical, USB B
1.	RING (Physical, wires
1.	BNO055 (Physical, wires)  


##### ADAFRUIT FEATHER BLUEFRUIT

**Location**

The right wheel.

**Script**

Rightsportswheelblefeather.ino  

**Connected to**

1. RASPBERRY PI (Bluetooth connection
1. BNO055 (Physical, wires)
1. POWERBANK (Physical, Micro USB)

##### RASPBERRY PI

**Location**

The wheelchair main frame.

**Script**

Rpi*sportswheelchair.py

**Connected to**

1. ARDUINO MEGA (Physical, wires)
1. POWERBANK (Physical, Micro USB)

##### LED RING

**Location**

The back of the wheelchair backseat.

**Connected to**

1. ARDUINO MEGA (Physical, wires)

##### BNO055 IMU x2

**Location**

The center turning point of the wheelchair.

**Location**

The center turning point of the right wheel.

**Connected to**		

1. ARDUINO MEGA (Physical, wires)
1. ADAFRUIT FEATHER (Physical, wires)

##### HEARTRATE MONITOR WRISTBAND (MIO LINK)

**Location**

The user's wrist.

**Connected to**

1. RASPBERRY PI (Bluetooth)

##### POWERBANK x2

**Location**

The wheelchair main frame.

**Location**

The right wheel.

**Connected to**		

1. RASPBERRY PI (Physical, USB)
1. ADAFRUIT FEATHER (Physical, Micro USB)

##### USB CABLE

**Location**

Between the Raspberry Pi and the Powerbank.

##### MICRO USB CABLE

**Location**

Between the Adafruit Bluefruit and the Powerbank.

##### USB B CABLE

**Location**

Between the Raspberry Pi and the Arduino Mega.

##### MALE - MALE JUMPERWIRES

##### FEMALE - MALE JUMPERWIRES

##### HEADERS BNO055
