#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

float angle = 0;
float AngleBaseY = 0;
float AngleDeltaY = 0;

/* This driver reads raw data from the BNO055

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

int32_t imuServiceId;
int32_t orientationCharId;

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/


/*
void orientation() {
  // Get Quaternion data (no 'Gimbal Lock' like with Euler angles)
  imu::Quaternion quat = bno.getQuat();
  float quatX = quat.x();
  float quatY = quat.y();
  float quatZ = quat.z();

  // Command is sent when \n (\r) or println is called
  // AT+GATTCHAR=CharacteristicID,value
  Serial.print( F("AT+GATTCHAR=") );
  Serial.print( orientationCharId );
  Serial.print( F(",") );
  Serial.print(String(quatX));
  Serial.print( F(",") );
  Serial.print(String(quatY));
  Serial.print( F(",") );
  Serial.println(String(quatZ));
}
*/

void setup(void)
{
  Serial.begin(9600);
  //Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
   // Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  //Serial.print("Current Temperature: ");
  //Serial.print(temp);
  //Serial.println(" C");
  //Serial.println("");




  

  bno.setExtCrystalUse(true);

 // Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/

void loop(void) {
//    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//    AngleBaseY = euler.y();
//  Serial.println(AngleBaseY);

/*
  imu::Quaternion quat = bno.getQuat();
  float quatX = quat.x();
  float quatY = quat.y();
  float quatZ = quat.z();
//  Serial.print( F("AT+GATTCHAR=") );
//  Serial.print( orientationCharId );
//  Serial.print( F(",") );
  Serial.print(String(quatX));
  Serial.print( F(",") );
  Serial.print(String(quatY));
  Serial.print( F(",") );
  Serial.println(String(quatZ));
  */

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//Serial.print("eulerdata");
Serial.print(euler.y());
Serial.print( F(",") );
Serial.print(euler.x());
Serial.print( F(",") );
Serial.print(euler.z());
Serial.print( F(",") );


imu::Vector<3> Gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
Serial.print(Gyro.y());
Serial.print( F(",") );
Serial.print(Gyro.x());
Serial.print( F(",") );
Serial.println(Gyro.z());

  // Delay before next measurement update
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
