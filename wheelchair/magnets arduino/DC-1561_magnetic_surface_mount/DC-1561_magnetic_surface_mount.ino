int inPinA = 52;    // DC-1561 connected to digital pin 52
int inPinB = 53;    // DC-1561 connected to digital pin 53
int valA = 0;      // variable to store the read value A
int valB = 0;      // variable to store the read value B

void setup() {
  Serial.begin(9600);
  pinMode(inPinA, INPUT);    // sets the digital pin 52 as input
  pinMode(inPinB, INPUT);    // sets the digital pin 53 as input
}

void loop() {
  valA = digitalRead(inPinA);
  valB = digitalRead(inPinB);
  Serial.print("Pin A: ");
  Serial.println(valA);
  Serial.print("Pin B: ");
  Serial.println(valB);
}
