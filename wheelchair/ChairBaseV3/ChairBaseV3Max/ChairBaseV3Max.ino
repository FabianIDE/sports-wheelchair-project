//libraries for orientation
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(55);

float wheel_angle_poll;
float wheel_angle_difference = 0;
float wheel_angle_total = 0;
float wheel_angle_original = 0;
float wheel_angle_previous = 0;
float wheel_angle_rotation = 0;

int32_t imuServiceId;
int32_t orientationCharId;

//stuff for orientation processing


void setup() {
  Serial.begin(9600);
  if(!bno.begin()){while(1);} // initialise sensor
  bno.setExtCrystalUse(true);
}
  
void loop() 
  {
//  rotation();

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    wheel_angle_poll  = euler.x();

// wheel moving backwards
    if (wheel_angle_previous<100 && wheel_angle_poll>200) 
      {
        wheel_angle_difference = 360-wheel_angle_poll+wheel_angle_previous;
                Serial.println ("backward");
      }

// wheel moving forwards
    else if (wheel_angle_previous>200 && wheel_angle_poll<100) 
      {
        wheel_angle_difference = -1*(wheel_angle_poll+360-wheel_angle_previous);
        Serial.println ("forward");
      }

     else {
          wheel_angle_difference = wheel_angle_previous - wheel_angle_poll;
     }
    

    wheel_angle_rotation = (wheel_angle_rotation + wheel_angle_difference);
  
 
    Serial.print("wheel_angle_poll: ");
    Serial.print(wheel_angle_poll);
    Serial.print(" wheel_angle_difference: ");
    Serial.print(wheel_angle_difference);
    Serial.print(" wheel_angle_previous: ");
    Serial.print(wheel_angle_previous);
    Serial.print(" wheel_angle_rotation: ");
    Serial.println(wheel_angle_rotation);
    
    
  //Serial.print("chair-base-99fa");
  //Serial.print( F(",") );
  //Serial.print(turns); 
  //Serial.print(" , ");   
  //Serial.print(angledifference); 
  //Serial.print(" , ");  
  //Serial.println(angle);
  //Serial.println(euler.x());
  //Serial.print( F(",") );
  //Serial.print(euler.y());
  //Serial.print( F(",") );
  
  delay(BNO055_SAMPLERATE_DELAY_MS);
  wheel_angle_previous = wheel_angle_poll;
  }
