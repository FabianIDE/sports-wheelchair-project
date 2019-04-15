#### MENU

[Project Description](README.md) - [Sensors & Actuators](SENSORS_ACTUATORS.md) - [Components](COMPONENTS.md) - [Installation](INSTALLATION.md) - [Testing](TESTING.md) - [Changelog](CHANGELOG.md)

## CHANGELOG

2019.04.02

Most updated versions

bno055_gatt_distance_measurement.ino |	1.0.0* * | REDUNDANT
Collect_and_label.py | 1.0.0 | REDUNDANT
WheelFeather+Mega.py | 2.2.0 |
BluefruitConfig.h | 1.0.0 |
WheelFeatherEulerx_Gyroz.ino | 1.0.0 | REDUNDANT
Subscribe_GATT_orientation.py | 1.0.0 | REDUNDANT
bno055_gatt_orientation.ino | 1.0.0* * |* REDUNDANT
Chairbase.ino | 3.1.0 |
subscribe_hrm_pexpect.py | 1.0.1 | REDUNDANT
wieldraaiing.ino | 2.0.0 | REDUNDANT
Arduino_code_BNO055.Arduino | 1.1.0 | REDUNDANT
subscribe_gatt_hrm.py | 1.0.4 |
DC-1561_magnetic_surface_mount.ino | 1.0.0 | REDUNDANT
readme.md | 1.1.0 |
serial_example.py | 1.0.0 | REDUNDANT
Heartrateexample.ino | 1.1.0 | REDUNDANT
wheeliemeter.ino | 1.0.0 | REDUNDANT
project description | 1.0.0 | REDUNDANT



2019.04.02 CHANGED WheelFeather+Mega.py 2.2.0
* Changed the value arbeid to DeltaX.
* Changed output from gyro values to speed calculation.
* Changed dimensions to facilitate Kcal sending.

2019.04.01 Chairbase.ino 3.3.0
* Added calculation of used Joules based on Accel X.
* Added convertion to Kcal.

2019.04.01 CHANGED bno055_gatt_distance_measurement.ino 1.1.0
* Removed sending arbeid value, only send DeltaX to Raspberry Pi.

2019.04.01 CHANGED Collect_and_label.py 2.0.0
* Combined example collect and label with wheelfeather+mega file.
* Rewrite property creation and dimensions.
* PROBLEM data collection over Serial and Bluetooth cannot run simultaneously.

2019.04.01 DEBUG WheelFeather+Mega.py 2.1.1
* Debugged the arbeid value format.

2019.03.25 ADDED WheelFeather+Mega.py 2.1.0
* Added dimension to correctly communicate with Bluefruit Feather.

2019.03.25 ADDED bno055_gatt_distance_measurement.ino 1.0.0
* Added arbeid calculation.
* Sends arbeid value to Raspberry Pi.

2019.03.25 ADDED Collect_and_label.py 1.0.0
* Added correct labels.

2019.03.25 ADDED Chairbase.ino 3.1.0
* Wheelie angle calibration.
* Wheelie angle accuracy.

2019.03.18 CHANGED Chairbase.ino 3.0.0
* Added heartrate display by LED ring.

2019.03.18 CHANGED WheelFeather+Mega.py 2.0.0 (WheelFeather+MegaV1.py)
* Fixed numerous connectivity issues.
* Solved data formatting issues.
* Confirmed working prototype.
* Added threading.

2019.03.11 CHANGED ChairBase.ino 2.1.0
* Added property marker.

2019.03.11 ADDED WheelFeather+Mega.py 1.0.0 (WheelFeather+MegaV1.py)
* Added code which allows the Arduino Mega and Adafruit Bluefruit to simultaneously transfer data to the Raspberry Pi.
* Replaced Subscribe_GATT_orientation, serial_example.py.
* Imported serial library
* CODE IS NOT TESTED

2019.03.11 CHANGED ChairBase.ino 2.0.0 (ChairBaseV1.ino)
* Changed functionality to display movement to the right or movement to the left.

2019.03.11 ADDED BluefruitConfig.h 1.0.0
* Enabled Bluefruit pins by changing to correct settings.

2019.03.11 ADDED WheelFeatherEulerx_Gyroz.ino 1.0.0 (WheelFeatherEulerx_Gyroz_V1.ino)
* Enabled bluetooth communication of Euler.x() and Gyro.z() data between Adafruit feather and Raspberry Pi.
* Replaced wheeliemeter, DC-1561_magnetic_surface_mount,Arduino_code_BNO055, wielverdraaiing, bno055_gatt_orientation.

2019.03.11 ADDED Subscribe_GATT_orientation.py 1.0.0
* Enabled the transfer of orientation data between Arduino and Raspberry Pi.

* 2019.03.11 bno055_gatt_orientation.Arduino 1.0.0
* Allowed connection between Adafruit_bluefruit and Raspberry Pi.

2019.03.11 ADDED Chairbase.ino 1.0.0 (ChairBaseV1.ino)
* Added LED colour display possibilities.
* Added Flashing in a set pattern.
* Added rainbow colour display.
* Added wheel rotation display by led colour change.

2019.03.11 ADDED wielverdraaiing.ino 2.1.0 (wielverdraaiingV2_gyro)
* Added IMU gyroscope measurement outputs.

2019.03.11 CHANGED subscribe_gatt_hrm.py 1.0.8
* Changed bluetooth device name.

2019.03.11 CHANGED wielverdraaiing.ino 2.1.0
* Changed the output to print euler.x() and euler.y().

2019.03.11 CHANGED wielverdraaiing.ino 2.0.0 (wielverdraaiingV2.ino)
* Changed the use of quaternations to the use of euler angles.

2019.03.08 FIXED subscribe_hrm_pexpect.py 1.0.1
* Changed "RETRY_CONNECTION = 1" to "RETRY_CONNECTION = 2".

2019.03.08 CHANGED Arduino_code_BNO055.ino 1.1.0
* Added functionality which allows a LED ring to display the euler.x() angle.

2019.03.08 ADDED wieldraaiing.ino 1.0.0
* Enabled rotation measurement of the right wheelchair wheel.
* The meaning of outputted data is unclear.

2019.03.08 ADDED subscribe_hrm_pexpect.py 1.0.0
* Subscribed to the heartrate monitor.
* Corrected the MAC address.

2019.03.08 ADDED Arduino_code_BNO055.Arduino 1.0.0
* Enabled IMU to output quaternion based angles in X,Y,Z direction.
* The meaning of outputted data is unclear.

2019.03.05 FIXED subscribe_gatt_hrm.py 1.0.4
* Changed GATT charactericts.

2019.03.04 FIXED subscribe_gatt_hrm.py 1.0.3
* Solved naming issues
* Solved GATT charactericts.

2019.03.04 ADDED README.md 1.1.0
* Added actuator description.

2019.03.04 FIXED subscribe_gatt_hrm.pu 1.0.2
* Solved naming issues to connect to the Heartrate monitor.

2019.03.04 FIXED subscribe_gatt_hrm.py 1.0.1
* Changed the property_type to "ONE_DIMENSION".

2019.03.04 ADDED subscribe_gatt_hrm.py 1.0.0
* Enabled communication between heartrate monitor and Raspberry Pi.
* Changed name to "Heartrate monitor"

2019.03.04 ADDED DC-1561_magnetic_surface_mount.ino 1.0.0
* Enabled wheel rotation measurement by logging magnet passages.

2019.03.04 ADDED readme.md 1.0.0
* Converted project description to readme.md.

2019.03.04 CHANGED Heartrateexample.ino 1.1.0
* Changed the name of used Adafruit_bluefruit to Bluefruit_sportswheelchair.

2019.03.04 ADDED serial_example.py 1.0.0
* Enabled communication between Arduino and DCD HUB using Raspberry Pi.

2019.03.04 ADDED Heartrateexample.ino 1.0.0
* Enabled bluetooth connection for Adafruit_bluefruit.
* Measured heartrate from heartrate monitor.

2019.02.26 ADDED Wheeliemeter.ino 1.0.0
* Measured euler.y from BNO055.
* Measured button press.

2019.02.25 ADDED project description 1.0.0
* Defined goals and required materials.
