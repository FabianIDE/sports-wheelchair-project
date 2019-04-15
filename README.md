## PROJECT DOCUMENTATION

* [Sensors & Actuators](SENSORS_ACTUATORS.md)
* [Components](COMPONENTS.md)
* [Installation](INSTALLATION.md)
* [Testing](TESTING.md)
* [Changelog](changelog.md)

## PROJECT DESCRIPTION

The goal of this project is to create a smart sports wheelchair which is able to monitor the consumed energy of a wheelchair basketball player in real time. This provides valuable insights for player and coach during training exercises. For example, the current system allows a coach to view the energy the player has spent in relation to the heartrate of the user. The system then determines the fitness level of the user based on these parameters.

#Current functionality

__*INPUT*__
* Relative Position (speed, linear acceleration)
* Rotation, Rotational acceleration
* Heartbeat

__*OUTPUT*__
-	Displays heartrate and fitness level on LED ring.
- Enables insight in multiple variables of movement on Grafana.
						- Velocity
						-	Acceleration
						- Distance moved
						- Rotation angle
						- Spent kcal
						- Heartrate
						- Fitness rating (calculated from spent kcal versus heartrate)
						- Tilt angle (wheelie meter)					


*Project by Max Weetzel, Fabian Bosman and Daniël Eikelenboom*
