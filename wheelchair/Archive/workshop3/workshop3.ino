#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINring      2
#define NUMring      36

int b = 0;
boolean increase = true;
boolean flash_enabled = false;

Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMring, PINring, NEO_RGBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  ring.begin();
  ring.show();

}

void loop() {

    char command = Serial.read();
  if (command == '1') {
    Serial.println("Turning on Flash...");
    flash_enabled = true;
  } else if (command == '0') {
    Serial.println("Turning off Flash...");
    flash_enabled = false;
    
    for(int i=0;i<NUMring;i++){
      ring.setPixelColor(i, ring.Color(0,0,0,0));
    }
    ring.show();
  }
  if (flash_enabled) {
    flash_pattern();
  }
  delay(50);

}


void flash_pattern() {  
  if (increase) {
    b+=10;
  }
  else {
    b-=10;
  }
  if (b > 249){
    increase = false;
  }
  else if (b < 50){
    increase = true;
  }
  for(int i=0;i<NUMring;i++){
    ring.setPixelColor(i, ring.Color(0,0,0,b));
  }
  ring.show();
  //Serial.println(b);
}

