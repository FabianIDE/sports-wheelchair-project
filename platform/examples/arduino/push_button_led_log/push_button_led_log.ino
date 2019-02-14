int BUTTON_PIN = 22;   // choose the input pin for the push button
int LED_PIN = 13;      // Choose the output pin for the LED

long LONG_PRESS_TIME = 500;

long buttonActiveSince = 0;
boolean longPressActive = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT);    // declare pushbutton as input
  pinMode(LED_PIN, OUTPUT);    // declare LED as input

  Serial.begin(9600); // setting baud speed for Serial (a baud is a pulse)
  Serial.println("Lets start using the button!");
}

void loop() {
  // Is button active?
  if (digitalRead(button) == LOW) {
    // if the button was not yet pressed
    if (buttonActiveSince == 0) {
        buttonActiveSince = millis();
    } else if ((millis() - buttonActiveSince > LONG_PRESS_TIME)
                && longPressActive == false) {
          longPressActive = true;
          digitalWrite(led, HIGH);  // turn LED ON
        }
    }

  // Was button active?
  } else {
    // Was Long Press event?
    if (buttonActiveSince > 0) {
      // End Long Press event
      if (longPressActive == true) {
        Serial.println("button-action,2");
        digitalWrite(led, LOW);  // turn LED OFF
        longPressActive = false;

      // End Short Press event
      } else {
        Serial.println("button-action,1");
      }
      buttonActiveSince = 0;
    }
  }

}