// libraries for NeoPixel
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//libraries for orientation
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//stuff for orientation processing
float angle = 0;
float AngleBaseY = 0;
float AngleDeltaY = 0;

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

int32_t imuServiceId;
int32_t orientationCharId;

//Stuff for LED ring and Serial processing
#define PINring      2
#define NUMring      36

Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMring, PINring, NEO_RGBW + NEO_KHZ800);

int pixON = 0;
unsigned long HR_int = 0;

void setup() {
  Serial.begin(9600);
  ring.begin();
  ring.show();

  if(!bno.begin()) // initialise sensor
  {
    while(1);
  }

for(int i=0;i<NUMring;i++){                       // LED startup animation -- REPLACE WITH DELAY(1000) IF YOU WANT TO REMOVE
    ring.setPixelColor(i, ring.Color(0,25,0,0));
    delay(30);ring.show();
  }
ringDO(0,50,0,0);
delay(20);
ringDO(0,25,0,0);

  bno.setExtCrystalUse(true);
}

void loop() {

// add property marker
Serial.print("chair-base-99fa");
Serial.print( F(",") );

imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
Serial.println(euler.x());
//Serial.print( F(",") );
//Serial.print(euler.y());
//Serial.print( F(",") );


imu::Vector<3> Gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
//Serial.println(Gyro.x());

//Left Right warning light

if (Gyro.x() < -2){ //LEDs 1-4,12-21,34-36 go on if right
  for(int i=12;i<=20;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(20,50,0,0));
  }
  for(int i=33;i<=36;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(20,50,0,0));
  }
  ring.show();
}
else if (Gyro.x() > 2){
  for(int i=21;i<33;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(40,50,0,0));
  }
  ring.show();
}
else{
  ringDO(0,25,0,0);
}

//Single LED showing direction
/*pixON = map(euler.x(),0,360,0,24)+12;
for(int i=0;i<NUMring;i++){                       // for each LED, set color
    if(i == pixON){
      ring.setPixelColor(i, ring.Color(0,0,0,25));
    }
    else{
      ring.setPixelColor(i, ring.Color(0,20,0,0));
    }

  }
  ring.show();*/

// HR flash


if(Serial.available() > 0){
  String HR = Serial.readString();
  HR_int = HR.toInt()/60;
}




delay(BNO055_SAMPLERATE_DELAY_MS);

}

void ringDO(int g, int r, int b, int w){
  for(int i=0;i<NUMring;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(g,r,b,w));
  }
  ring.show();
}
