// LED Settings
#define D0 16 // Green LED
#define D1 5 // Green LED
#define D2 4 // Green LED
#define D3 0 // Blue LED
#define D4 2 // Blue LED
#define D5 14 // Blue LED
#define D6 12 // Blue LED

int workLedPins[] = {D0, D1, D2};
int pauseLedPins[] = {D3, D4, D5, D6};

String serialData;

void setup() {

  Serial.begin(115200);

  // Init Leds as Outputs
  for (int i = 0; i < sizeof(workLedPins); i++) {
    pinMode(workLedPins[i], OUTPUT);
  }
  for (int i = 0; i < sizeof(pauseLedPins); i++) {
    pinMode(pauseLedPins[i], OUTPUT);
  }
  blinkSetupDone();
}

void loop() {
  if (Serial.available() > 0) {
    serialData = Serial.readString();

    if (serialData == "work") {
      allWorkLeds(HIGH);
      allPauseLeds(LOW);
    }
    else if (serialData == "shortpause") {
      allWorkLeds(LOW);
      allPauseLeds(HIGH);
    }
    else if (serialData == "longpause") {
      allWorkLeds(LOW);
      allPauseLeds(HIGH);
    }
    else if (serialData == "stop") {
      allWorkLeds(HIGH);
      allPauseLeds(LOW);
    }
  }
}

/**
   Indicates that the setup is done by blinking all LEDs 3 times
*/
void blinkSetupDone() {
  digitalWrite(workLedPins[0], HIGH);
  delay(300);
  digitalWrite(workLedPins[0], LOW);
  digitalWrite(workLedPins[1], HIGH);
  delay(300);
  digitalWrite(workLedPins[1], LOW);
  digitalWrite(workLedPins[2], HIGH);
  delay(300);
  digitalWrite(workLedPins[2], LOW);
  digitalWrite(pauseLedPins[0], HIGH);
  delay(300);
  digitalWrite(pauseLedPins[0], LOW);
  digitalWrite(pauseLedPins[1], HIGH);
  delay(300);
  digitalWrite(pauseLedPins[1], LOW);
  digitalWrite(pauseLedPins[2], HIGH);
  delay(300);
  digitalWrite(pauseLedPins[2], LOW);
  digitalWrite(pauseLedPins[3], HIGH);
  delay(300);
  digitalWrite(pauseLedPins[3], LOW);
  delay(300);
  allWorkLeds(HIGH);
  allPauseLeds(HIGH);
  delay(2000);
  allWorkLeds(LOW);
  allPauseLeds(LOW);
}

/**
   Sets all work LEDs to the given status (HIGH, LOW)
*/
void allWorkLeds(int stat) {
  for (int i = 0; i < sizeof(workLedPins); i++) {
    digitalWrite(workLedPins[i], stat);
  }
}

/**
   Sets all pause LEDs to the given status (HIGH, LOW)
*/
void allPauseLeds(int stat) {
  for (int i = 0; i < sizeof(pauseLedPins); i++) {
    digitalWrite(pauseLedPins[i], stat);
  }
}
