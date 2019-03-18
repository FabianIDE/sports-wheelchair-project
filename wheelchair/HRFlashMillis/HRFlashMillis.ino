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
unsigned long ontime = 200;                     // time the LED is on at blinking

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
    digitalWrite(13, HIGH);
    ringDO(0,255,0,0,0,12);                          // flash LED
    timeoffset = millis();                      // set timestamp last flash
    timer = 0;                                  // reset timer
  }
  if(ledOFF == false && timer > ontime){        // turn the LED off after 'ontime' seconds
    ledOFF = true;
    digitalWrite(13, LOW);
    ringDO(0,80,0,0,0,12);
  }
  
}


void ringDO(int g, int r, int b, int w, int beginled, int endled){
  for(int i=beginled;i<endled;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(g,r,b,w));
  }
  ring.show();
}
