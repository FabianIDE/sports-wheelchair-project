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

//Stuff for HR Flash
unsigned long timeStart = 0;
unsigned long timer = 0;
unsigned long timeoffset = 0;
bool ledOFF = true;
unsigned long delayer = 2000;
unsigned long HR_int = 0;
unsigned long ontime = 200;                     // time the LED is on at blinking



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
ringDO(0,50,0,0,0,NUMring);
delay(20);
ringDO(0,25,0,0,0,NUMring);

  bno.setExtCrystalUse(true);

  timeStart = millis();
}

void loop() {

// add property marker
Serial.print("chair-base-15e3");
Serial.print( F(",") );

imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
Serial.print(euler.x());
Serial.print( F(",") );
Serial.print(euler.y());
Serial.print( F(",") );

imu::Vector<3> Gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
Serial.println(Gyro.x());

//Left Right warning light

if (Gyro.x() < -2){ //LEDs 1-4,12-21,34-36 go on if right
  /*for(int i=12;i<=20;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(20,50,0,0));
  }
  for(int i=33;i<=36;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(20,50,0,0));
  }
  ring.show();*/
  ringDO(20,50,0,0,13,21);
  ringDO(20,50,0,0,33,36);
}
else if (Gyro.x() > 2){
  /*for(int i=21;i<33;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(40,50,0,0));
  }
  ring.show();*/
  ringDO(40,50,0,0,21,33);
}
else{
  ringDO(0,25,0,0,13,36);
}

// HR flash

if(Serial.available() > 0){                   // Read serial port
    String HR = Serial.readStringUntil(',');
    HR_int = HR.toInt()*1000;                   // long & int discard anything beyond the decimal point, so before dividing multiply by 1000 
    unsigned long tussen = HR_int/60;           // from BPM to BPS (Beats per second)
    delayer = 1000000/tussen;                   // from BPS to delay after each flash trigger
  }
  
  /*Serial.print("Delayer: ");
  Serial.print(delayer);
  Serial.print(", HR: ");
  Serial.println(HR_int/1000);*/
  
  timer = millis()-timeoffset;                  // time since last flash = current time - timestamp last flash
  
  if (ledOFF && timer > delayer){               // if the flash is not active and current time > delay
    ledOFF = false;
    ringDO(0,255,0,0,0,12);                          // flash LED
    timeoffset = millis();                      // set timestamp last flash
    timer = 0;                                  // reset timer
  }
  if(ledOFF == false && timer > ontime){        // turn the LED off after 'ontime' seconds
    ledOFF = true;
    ringDO(0,25,0,0,0,12);
  }




//delay(BNO055_SAMPLERATE_DELAY_MS);

}

void ringDO(int g, int r, int b, int w, int beginled, int endled){
  for(int i=beginled;i<endled;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(g,r,b,w));
  }
  ring.show();
}
