## PROJECT DESCRIPTION
*by Max, Fabian and Daniël*

Creating a smart sports wheelchair which monitors and measures the position and energy consumed of a player in real time, providing valuable insights for both player and coach.

__*INPUT*__
* Relative Position (speed, acceleration)
* Orientation
* Weight

__*OUTPUT*__
* Basic information on Grafana
* LED strip indicating fatigue or calorie counter

__*OPTIONAL EXPANTION*__
* Heartrate
* Webapp showing the live position and direction of players


## SENSORS

To archieve the project goal, data will be collected using the following sensors.

__*INPUT*__
* Speedometer (Hall sensor)
The speedometer collects data by counting the amount of revelations of the wheels during a certain time. The speedometer conists of a Hall sensor connected to the frame of the wheelchair and a magnet connected to one of the spokes of the wheel. The Arduino is able to count the time of each wheel revelation.

* Orientation sensor
The orientation sensor consists of a gyroscope, accelerometers and magnetometers. The standard module from Adafruit will provide the relative position the sensor is in, with which the direction of travel, can be determined. Combined with the speedometer, the position relative to the starting position can be determined.

* Pressure sensors
With a pressure sensor the weight of the player can be determined, which, in combination with the sensors above, can be used for calculations in energy usage.

* OPTIONAL: Arduino HR sensor
An expansion, if time allows, is to use heartrate data to more reliably predict the energy usage of the sporter.
