/*********************************************************************
 This is an example for our nRF51822 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/*
    Please note the long strings of data sent mean the *RTS* pin is
    required with UART to slow down data sent to the Bluefruit LE!
*/
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

float wheel_angle_poll;
float wheel_angle_difference = 0;
float wheel_angle_total = 0;
float wheel_angle_original = 0;
float wheel_angle_previous = 0;
float wheel_angle_rotation = 0;
float wheel_distance = 0;
int Weight = 80;
float radiuswiel = 0.294;
float DeltaX = 0;
float Speed = 0;
float ArbeidDiff = 0;
//float ArbeidOld = 0;
//float ArbeidTotal = 0;


#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#include "BluefruitConfig.h"

// LED error flag
#define LED_PIN 13

// Create the Bluefruit object for Feather 32u4
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// BNO settings
#define BNO055_SAMPLERATE_DELAY_MS (200)
Adafruit_BNO055 bno = Adafruit_BNO055(55);

// GATT service information
int32_t imuServiceId;
int32_t orientationCharId;

// A small helper
void error(const __FlashStringHelper*err) {
  if (Serial.available()) {
    Serial.println(err);
  }
  // In any case, turn on the LED to signal the error
  analogWrite(LED_PIN, HIGH);
  while (1);
}

// Initializes BNO055 sensor
void initSensor(void) {
  if(!bno.begin()) {
    error(F("No BNO055 detected. Check your wiring or I2C ADDR!"));
  }
  delay(1000);
  bno.setExtCrystalUse(true);
}

// Sets up the HW an the BLE module (this function is called
// automatically on startup)





void setup(void) {
  delay(500);
  boolean success;

  // Set LED error flag

  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, LOW);
  Serial.begin(115200);

  // Initialise the module
  if ( !ble.begin(VERBOSE_MODE) ) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring."));
  }

   // Setup the BNO055 sensor
  initSensor();

  // Perform a factory reset to make sure everything is in a known state
  if (!ble.factoryReset() ){
       error(F("Couldn't factory reset."));
  }

  // Disable command echo from Bluefruit
  ble.echo(false);

  // Print Bluefruit information
  ble.info();
  ble.verbose(true);

  // Change the device name to fit its purpose
  if (! ble.sendCommandCheckOK(F("AT+GAPDEVNAME=sportswheelchair")) ) {
    error(F("Could not set device name."));
  }

  // Add the IMU Service definition
  success = ble.sendCommandWithIntReply( F("AT+GATTADDSERVICE=UUID128=00-11-00-11-44-55-66-77-88-99-AA-BB-CC-DD-EE-FF"), &imuServiceId);
  if (! success) {
    error(F("Could not add Orientation service."));
  }

  // Add the Orientation characteristic
  success = ble.sendCommandWithIntReply( F("AT+GATTADDCHAR=UUID128=02-11-88-33-44-55-66-77-88-99-AA-BB-CC-DD-EE-FF,PROPERTIES=0x10,MIN_LEN=1,MAX_LEN=17,VALUE=\"\""), &orientationCharId);
  if (! success) {
    error(F("Could not add Orientation characteristic."));
  }

  // Add the Orientation Service to the advertising data
  // (needed for Nordic apps to detect the service)
  ble.sendCommandCheckOK( F("AT+GAPSETADVDATA=02-01-06-05-02-0d-18-0a-18") );

  // Reset the device for the new service setting changes to take effect
  ble.reset();
}






void orientation() {

// get rotation of the wheel and determine total rotations

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    wheel_angle_poll  = euler.x();

// wheel moving backwards
    if (wheel_angle_previous<100 && wheel_angle_poll>200)
      {
        wheel_angle_difference = 360-wheel_angle_poll+wheel_angle_previous;
                //Serial.println ("backward");
      }

// wheel moving forwards
    else if (wheel_angle_previous>200 && wheel_angle_poll<100)
      {
        wheel_angle_difference = -1*(wheel_angle_poll+360-wheel_angle_previous);
        //Serial.println ("forward");
      }

     else {
          wheel_angle_difference = wheel_angle_previous - wheel_angle_poll;
     }


    wheel_angle_rotation = (wheel_angle_rotation + wheel_angle_difference);

    wheel_distance = -1*wheel_angle_rotation/360*1.850;



  // Get Gyro data
  imu::Vector<3> Gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  float GyroZ = Gyro.z();

  //arbeid in joule is W = m * a * delta_x

  DeltaX = wheel_angle_difference/360*1.850; //convert angular diff to linear diff
  Speed = GyroZ*radiuswiel;
  //ArbeidDiff = abs(Weight*LinearAccel*DeltaX);
  //ArbeidTotal = ArbeidDiff + ArbeidOld;
  Serial.println(DeltaX);
  //Serial.println(LinearAccel);
  //Serial.println(ArbeidOld);
  //Serial.println(ArbeidDiff);
  //Serial.println(ArbeidTotal);

  // Command is sent when \n (\r) or println is called
  // AT+GATTCHAR=CharacteristicID,value
  ble.print( F("AT+GATTCHAR=") );
  ble.print( orientationCharId );
  ble.print( F(",") );
  ble.print(String(wheel_distance));
  ble.print( F(",") );
  ble.print(String(Speed));
  ble.print( F(",") );
  ble.println(String(DeltaX));



  //ble.println(String(eulerY));

  wheel_angle_previous = wheel_angle_poll;
 // ArbeidOld = ArbeidTotal;


}




void loop(void) {

  orientation();

  // Check if command executed OK
  if ( !ble.waitForOK() ) {
    error(F("Failed to get response!"));
  }

  // Delay before next measurement update
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
