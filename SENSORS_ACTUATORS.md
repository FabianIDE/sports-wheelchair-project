#### MENU

[Project Description](README.md) - [Sensors & Actuators](SENSORS_ACTUATORS.md) - [Components](COMPONENTS.md) - [Installation](INSTALLATION.md) - [Testing](TESTING.md) -  [Changelog](CHANGELOG.md)

## SENSORS & ACTUATORS

To achieve the project goal, data will be collected using the following sensors.

*Orientation sensor*

The orientation sensor consists of a gyroscope, accelerometers and magnetometers. The standard module from Adafruit will provide the relative position the sensor is in, with which the direction of travel, can be determined. Combined with the speedometer, the position relative to the starting position can be determined.

*Heartrate sensor*

An expansion on the wheelchair project is a heartrate monitor wearable. This can be placed on the arm of the athlete in order to more reliably predict the energy usage.

*Of the sensors above, the speedometer (Hall sensor + magnet) and the Arduino HR sensor are not in the list.*


## ACTUATORS

To communicate the gained insights back to the user, the wheelchair will use certain actuators to notify the user.

*RGB LED ring (Neopixel)*

To display fatigue, heart rate and more, an LED ring will be used, preferably Adafruit's Neopixel ring. The ease of the Neopixel is that it is expandable to almost infinite length while still using only three cables (positive, ground and data) and thus three pins on the Arduino.

A disadvantage is that it can only be controlled by the Arduino, not for the Raspberry Pi.
With the Neopixel ring, it is possible to create patterns of coloured LED's, which allow for easy communication to the end user.

*Of the actuators above, the RGB LED Ring can be provided by us if necessary.*
