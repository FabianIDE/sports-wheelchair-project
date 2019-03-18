/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

unsigned long timeStart = 0;
unsigned long time = 0;
unsigned long timeoffset = 0;
bool ledOFF = true;
unsigned long delayer = 2000;
unsigned long ontime = 500;

void setup()
{
  pinMode(13, OUTPUT);
  
  timeStart = millis();
  
}

void loop()
{
  time = millis()-timeoffset;
  
  if (ledOFF && time > delayer){
    ledOFF = false;
    digitalWrite(13, HIGH);
    timeoffset = millis();
    time = 0;
  }
  if(ledOFF == false && time > ontime){
    ledOFF = true;
    digitalWrite(13, LOW);
  }
  
}