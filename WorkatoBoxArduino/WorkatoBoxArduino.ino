#define DEBUG
// LED Settings
#define D0 16 // Green LED
#define D1 5 // Green LED
#define D2 4 // Green LED
#define D3 0 // Blue LED
#define D4 2 // Blue LED
#define D5 14 // Blue LED
#define D6 12 // Blue LED

int workLedPins[] = {D0, D1, D2};
int currentWorkLedStatus = LOW;
int pauseLedPins[] = {D3, D4, D5, D6};
int currentPauseLedStatus = LOW;

String serialData;

void setup() {
  delay(500);
  Serial.begin(115200);
  delay(1000);
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
    // preprocess the data string by replacing any extra characters
    serialData.trim();
    serialData.replace("\n", "");
    serialData.replace("\t", "");
    serialData.replace("\r", "");

#ifdef DEBUG
    Serial.println(serialData);
#endif
    if (serialData == "work") {
#ifdef DEBUG
      Serial.println("Work phase");
#endif
      allLeds(LOW, false, 0);
      allWorkLeds(HIGH, true, 200);
    }
    else if (serialData == "shortpause") {
#ifdef DEBUG
      Serial.println("Short pause phase");
#endif
      allLeds(LOW, false, 0);
      allPauseLeds(HIGH, true, 200);
    }
    else if (serialData == "longpause") {
#ifdef DEBUG
      Serial.println("Long pause phase");
#endif
      allLeds(LOW, false, 0);
      allPauseLeds(HIGH, true, 400);
    }
    else if (serialData == "stop") {
#ifdef DEBUG
      Serial.println("Stopping current phase");
#endif
      allLeds(LOW, false, 0);
    }
    else {
#ifdef DEBUG
      Serial.print("Unknown Serial command: ");
      Serial.println(serialData);
#endif
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
  allLeds(HIGH, true, 300);
  delay(2000);
  allLeds(LOW, false, 0);
}

void allLeds(int stat, boolean stairEffect, int stairEffectDelay) {
  allWorkLeds(stat, stairEffect, stairEffectDelay);
  if (stairEffect) delay(stairEffectDelay);
  allPauseLeds(stat, stairEffect, stairEffectDelay);
}

void allWorkLeds(int stat, boolean stairEffect, int stairEffectDelay) {
  digitalWrite(workLedPins[0], stat);
  if (stairEffect) delay(stairEffectDelay);
  digitalWrite(workLedPins[1], stat);
  if (stairEffect) delay(stairEffectDelay);
  digitalWrite(workLedPins[2], stat);
}

void allPauseLeds(int stat, boolean stairEffect, int stairEffectDelay) {
  digitalWrite(pauseLedPins[0], stat);
  if (stairEffect) delay(stairEffectDelay);
  digitalWrite(pauseLedPins[1], stat);
  if (stairEffect) delay(stairEffectDelay);
  digitalWrite(pauseLedPins[2], stat);
  if (stairEffect) delay(stairEffectDelay);
  digitalWrite(pauseLedPins[3], stat);
}
