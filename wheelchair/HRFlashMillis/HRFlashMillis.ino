#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINring      3
#define NUMring      36

Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMring, PINring, NEO_RGBW + NEO_KHZ800);

/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

unsigned long timeStart = 0;
unsigned long timer = 0;
unsigned long timeoffset = 0;
bool ledOFF = true;
unsigned long delayer = 2000;
unsigned long HR_int = 0;
unsigned long ontime = 200;

void setup()
{
  ring.begin();
  ring.show();
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  timeStart = millis();
}

void loop()
{
  if(Serial.available() > 0){
    String HR = Serial.readStringUntil(',');
    HR_int = HR.toInt()*1000;
    unsigned long tussen = HR_int/60;
    delayer = 1000000/tussen;
  }
  
  Serial.print("Delayer: ");
  Serial.print(delayer);
  Serial.print(", HR: ");
  Serial.println(HR_int/1000);
  
  timer = millis()-timeoffset;
  
  if (ledOFF && timer > delayer){
    ledOFF = false;
    digitalWrite(13, HIGH);
    ringDO(0,255,0,0);
    timeoffset = millis();
    timer = 0;
  }
  if(ledOFF == false && timer > ontime){
    ledOFF = true;
    digitalWrite(13, LOW);
    ringDO(0,80,0,0);
  }
  
}


void ringDO(int g, int r, int b, int w){
  for(int i=0;i<NUMring;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(g,r,b,w));
  }
  ring.show();
}
