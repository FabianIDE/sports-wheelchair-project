#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//Include LED ring library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

float angle = 0;
float AngleBaseY = 0;
float AngleDeltaY = 0;
float AngleBaseZ = 0;
float AngleDeltaZ = 0;
int LEDon = 0;

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

#define NUMPIXELSring      36
#define PINring            2

Adafruit_BNO055 bno = Adafruit_BNO055(55);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMPIXELSring, PINring, NEO_RGBW + NEO_KHZ800);

int32_t imuServiceId;
int32_t orientationCharId;

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/



void orientation() {
  // Get Quaternion data (no 'Gimbal Lock' like with Euler angles)
  imu::Quaternion quat = bno.getQuat();
  float quatX = quat.x();
  float quatY = quat.y();
  float quatZ = quat.z();

  // Command is sent when \n (\r) or println is called
  // AT+GATTCHAR=CharacteristicID,value
  /*Serial.print( F("AT+GATTCHAR=") );
  Serial.print( orientationCharId );
  Serial.print( F(",") );
  Serial.print(String(quatX));
  Serial.print( F(",") );
  Serial.print(String(quatY));
  Serial.print( F(",") );
  Serial.println(String(quatZ));*/
}


void setup(void)
{
  Serial.begin(9600);
  //Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
  
  ring.begin();//initiate ring
  ring.show();//send ring values (=nothing, so off).

  int test = 0;
  
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

imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  AngleBaseY = euler.y();
    //Serial.print("AngleBaseY=");
    //Serial.println(AngleBaseY);
  AngleBaseZ = euler.x();
  

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

  orientation();

  
imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  AngleDeltaZ = euler.x();
  LEDon = map(AngleDeltaZ, 0, 360, 0, 23)+12;
  Serial.print(euler.x());
  Serial.print( F(",") );
  Serial.print(euler.y());
  Serial.print( F(",") );
  Serial.print(euler.z());
  Serial.print( F(",") );
  Serial.println(LEDon);

  for(int i=0;i<NUMPIXELSring;i++){
    if (i == LEDon){
      ring.setPixelColor(i, ring.Color(255,0,0,0));
    }
    else
    {
      ring.setPixelColor(i, ring.Color(0,50,0,0));
    }
    
  }
  ring.show();
  
  // Delay before next measurement update
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
