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
float WheelieZero = 10;
float WheelieAngle = 10;
int HR_color = 0;


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

//Variables for energy counter
int Weight = 75; //set weight of athlete incl chair
long DeltaX_int = 0;
long Joules_max = 50000; // set Joules amount of 1 full LED ring //defide by 4184 to get Kcal
long Energy = 0;
int Energy_ON = 0;
float Joules = 0;
float Kcal = 0;
float KcalOld = 0;
float KcalTotal = 0;

//Fitness variables
int Inactive =0;
float Fitness = 0;

int n = 0;
int m = 12;                                     // Wheelie rotating light loop counter

void setup() {
  Serial.begin(9600);

  ring.begin();
  ring.show();

  if(!bno.begin()) // initialise sensor
  {
    while(1);
  }

delay(1500); //delay to startup the BNO otherwise we always read a 0 the first second(s)

//Setting calibration value for the wheeliemeter
imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); 
WheelieZero = euler.y();
//Serial.println(WheelieZero);
//Serial.println(euler.y());

for(int i=0;i<NUMring;i++){                       // LED startup animation -- REPLACE WITH DELAY(1000) IF YOU WANT TO REMOVE
    ring.setPixelColor(i, ring.Color(0,25,0,0));
    delay(30);ring.show();
  }
ringDO(0,50,0,0,0,NUMring);
delay(20);
ringDO(0,25,0,0,0,NUMring);

  bno.setExtCrystalUse(true);

  Energy = Joules_max;

  timeStart = millis();
}

 

void loop() {

  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2

// add property marker

imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
WheelieAngle = euler.y() - WheelieZero; //calculate wheelie angle based on startup value

imu::Vector<3> Gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

imu::Vector<3> Accel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

//Left Right warning light

/*if (Gyro.x() < -3){ //LEDs 13-21,34-36 go on if right
  ringDO(20,50,0,0,12,21);
  ringDO(20,50,0,0,33,36);
}
else if (Gyro.x() > 3){
  ringDO(40,50,0,0,21,33);
}
else{
  ringDO(0,25,0,0,12,36);
}*/

// HR flash
    
DeltaX_int = 0; //set to zero to prevent non updating values
Joules = 0;     //set to zero to prevent non updating values

if(Serial.available() > 0){                   // Read serial port
    String HR = Serial.readStringUntil(',');
    HR_int = HR.toInt()*1000;                   // long & int discard anything beyond the decimal point, so before dividing multiply by 1000
    unsigned long tussen = HR_int/60;           // from BPM to BPS (Beats per second)
    delayer = 1000000/tussen;                   // from BPS to delay after each flash trigger
    
    String DeltaX = Serial.readStringUntil(','); // read second string from serial port
    DeltaX_int = DeltaX.toInt();
  }
  
  Joules = abs(Weight*DeltaX_int*Accel.x());
    
  Kcal = Joules/4184;                   // converting Joules to Kcal
  KcalTotal = KcalOld + Kcal;           //increase total joules used

  Energy = Energy - Joules;                     // substract used energy from stack
  Energy_ON = map(Energy, 0, Joules_max, 0, 24)+12; // convert to LEDs to turn on


  if (Joules > 100) {                    //set amount of joule defined as inactvity of wheelchair
    Inactive = 0;                         //set counter to 0
    Fitness = KcalTotal/HR_int*4184*100;      //Only update when active

  }

  else {
    Inactive ++;
  }

  if (Inactive >= 200){                 //set interactivy counter in 10ths of sec.
    KcalTotal = 0;
    Inactive = 200;
  }

  
  
  if (isnan(Fitness)) {                     // removes NaN (not a number) print from dividing a zero
    Fitness = 0;
  }

  ringDO(0,0,20,40,12,Energy_ON);
  ringDO(0,0,0,0,Energy_ON,36);


  if (Energy < 0){                              // for testing: If energy is empty, refill
    Energy = Joules_max;
  }

  /*Serial.print("Delayer: ");
  Serial.print(delayer);
  Serial.print(", HR: ");
  Serial.println(HR_int/1000);*/

  timer = millis()-timeoffset;                  // time since last flash = current time - timestamp last flash

  if (ledOFF && timer > delayer){               // if the flash is not active and current time > delay
    ledOFF = false;
    HR_color = map (HR_int/1000, 30 , 200 , 0 , 255);
    
    ringDO(255-HR_color,HR_color,0,0,0,12);                          // flash LED
    timeoffset = millis();                      // set timestamp last flash
    timer = 0;                                  // reset timer
  }
  if(ledOFF == false && timer > ontime){        // turn the LED off after 'ontime' seconds
    ledOFF = true;
    ringDO((255-HR_color)/10,HR_color/10,0,0,0,12);
  }

  if (WheelieAngle > 15) {                      // if a wheelie is taking place, do cool LED pattern
    ringDO(0,255,0,0,n+12,n+14);                
    n = n+3;
    if (n >= 24){
      n = 0;
    }
    ringDO(0,0,255,0,m+12,m+14);
    m = m+3;
    if (m >= 24){
      m = 0;
    }
  }


Serial.print(euler.x());
Serial.print( F(",") );
Serial.print(WheelieAngle);
Serial.print( F(",") );
Serial.print(Joules);
Serial.print( F(",") );
Serial.print(KcalTotal,3);
Serial.print( F(",") );
Serial.print(Fitness);
Serial.println( F(",") );

KcalOld = KcalTotal;
  ring.show();                                  // send data (color etc from entire loop) to LED ring
delay(BNO055_SAMPLERATE_DELAY_MS);

}

void ringDO(int g, int r, int b, int w, int beginled, int endled){
  for(int i=beginled;i<endled;i++){                       // for each LED, set color
    ring.setPixelColor(i, ring.Color(g,r,b,w));
  }
  //ring.show();
}
