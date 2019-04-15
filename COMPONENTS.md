## PROJECT DOCUMENTATION

* [Project Description](README.md)
* [Sensors & Actuators](SENSORS_ACTUATORS.md)
* [Components](COMPONENTS.md)
* [Installation](INSTALLATION.md)
* [Testing](TESTING.md)
* [Changelog](CHANGELOG.md)

# COMPONENTS

The components and their connections are listed below.

### ARDUINO MEGA

   Location: the wheelchair main frame  
   Script:	Chairbase.ino  
   Connected to:
	 1.	RASPBERRY PI (Physical, USB B
	 1.	RING (Physical, wires
	 1.	BNO055 (Physical, wires)  


### ADAFRUIT FEATHER BLUEFRUIT
   Location: the right wheel
   Script:Rightsportswheelblefeather.ino  
   Connected to: 		RASPBERRY PI (Bluetooth connection)
  									BNO055 (Physical, wires)
  									POWERBANK (Physical, Micro USB)

### RASPBERRY PI

   Location: the wheelchair main frame
   Script:Rpi_sportswheelchair.py
   Connected to: 	ARDUINO MEGA (Physical, wires)
  								POWERBANK (Physical, Micro USB)

### LED RING
   Location: the back of wheelchair backseat
   Connected to:		ARDUINO MEGA (Physical, wires)

### BNO055 IMU x2

   Location: the center turning point of the wheelchair
   Location: the center turning point of the right wheel
   Connected to:		ARDUINO MEGA (Physical, wires)
  									ADAFRUIT FEATHER (Physical, wires)

### HEARTRATE MONITOR WRISTBAND (MIO LINK)

   Location: the user's wrist.
   Connected to:		RASPBERRY PI (Bluetooth)

### POWERBANK x2

   Location:	the wheelchair main frame
   Location: the right wheel
   Connected to:		RASPBERRY PI (Physical, USB)
  									ADAFRUIT FEATHER (Physical, Micro USB)

### USB CABLE

   Location: between Raspberry Pi and Powerbank

### MICRO USB CABLE

   Location: between Adafruit Bluefruit and Powerbank

### USB B CABLE

   Location: between Raspberry Pi and Arduino Mega.

### MALE - MALE JUMPERWIRES

### FEMALE - MALE JUMPERWIRES

### HEADERS BNO055
