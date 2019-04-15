#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINring      2
#define NUMring      36

int b = 0;
int red_int = 0;
int green_int = 0;
int blue_int = 0;
int white_int = 0;
boolean increase = true;
boolean flash_enabled = false;

Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMring, PINring, NEO_RGBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  ring.begin();
  ring.show();
  Serial.println("Boot sequence completed, enter RGB value: r,g,b (0-255)");
  rainbow(10);

}

void loop() {

  if(Serial.available() > 0){
    String red = Serial.readStringUntil(',');       // read the entered string
    if(red == "stop"){                              // if the input is 'stop', turn the LEDs off
      ringDO(0,0,0,0);
      Serial.println("LED ring turned off. Enter RGB value: r,g,b (0-255)");
    }
    else                                            
    {
      String green = Serial.readStringUntil(',');   // if it's not stop, read to next comma
      String blue = Serial.readStringUntil('\0');   // read to end
      Serial.println("red " + red);
      Serial.println("green " + green);
      Serial.println("blue " + blue);
      red_int = red.toInt();                        // convert strings to integers
      green_int = green.toInt();
      blue_int = blue.toInt();
      if(red_int == green_int && green_int == blue_int && red_int != 0){
        ringDO(0,0,0,red_int);                      // if the input of rgb is equal, use the white LEDs instead of the color ones to create white light
      }
      else{
        ringDO(green_int,red_int,blue_int,0);       // write color to LEDs
      }
      
    }
  }

  
  
  
/*
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
  delay(50);*/

}

void ringDO(int g, int r, int b, int w){
  for(int i=0;i<NUMring;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(g,r,b,w));
  }
  ring.show();
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

// below here is for the rainbow fun

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<ring.numPixels(); i++) {
      ring.setPixelColor(i, Wheel((i+j) & 255));
    }
    ring.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return ring.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return ring.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return ring.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

