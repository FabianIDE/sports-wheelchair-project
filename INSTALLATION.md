## PROJECT DOCUMENTATION

* [Project Description](README.md)
* [Sensors & Actuators](SENSORS_ACTUATORS.md)
* [Components](COMPONENTS.md)
* [Installation](INSTALLATION.md)
* [Testing](TESTING.md)
* [Changelog](CHANGELOG.md)


## INSTALLATION

 After collecting all the components as specified in [Components](COMPONENTS.md), follow these steps how to set everything up!

### 2 Arduino

Download and install the (latest) Arduino software from the Arduino website (we used v 1.8.5) https://www.arduino.cc/en/Main/Software

The Arduino IDE already comes with everything needed for the Arduino Mega.

The Bluefruit does need to be added manually:
For this you will also have to install the following library (Bluefruit nRF51), which you can do in Sketch -> Include Library -> Manage Libraries :

![](images/library.png)




### 1 Python

Power up and connect to your Raspberry Pi in the way you prefer (i.e. over SSH or connect it to a monitor)

Then install the requirements as listed in the requirements.txt file through its terminal

On Mac:

```bash
pip3 install -r requirements.txt --user
```
On Windows:

```bash
python -m pip install -r requirements.txt --user
```









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
