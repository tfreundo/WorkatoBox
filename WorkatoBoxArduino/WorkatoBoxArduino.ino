// LED Settings
const int PIN_LED_WORK = 18; // Blue LED
const int PIN_LED_PAUSE = 19; // Green LED

String serialData;

void setup() {

  Serial.begin(115200);

  pinMode(PIN_LED_WORK, OUTPUT);
  digitalWrite(PIN_LED_WORK, LOW);
  pinMode(PIN_LED_PAUSE, OUTPUT);
  digitalWrite(PIN_LED_PAUSE, LOW);
  blinkSetupDone();
}

void loop() {
  if (Serial.available() > 0) {
    serialData = Serial.readString();

    if (serialData == "work") {
      digitalWrite(PIN_LED_WORK, HIGH);
      digitalWrite(PIN_LED_PAUSE, LOW);
    }
    else if (serialData == "shortpause") {
      digitalWrite(PIN_LED_WORK, LOW);
      digitalWrite(PIN_LED_PAUSE, HIGH);
    }
    else if (serialData == "longpause") {
      digitalWrite(PIN_LED_WORK, LOW);
      digitalWrite(PIN_LED_PAUSE, HIGH);
    }
    else if (serialData == "stop") {
      digitalWrite(PIN_LED_WORK, LOW);
      digitalWrite(PIN_LED_PAUSE, LOW);
    }
  }
}

/**
   Indicates that the setup is done by blinking all LEDs 3 times
*/
void blinkSetupDone() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(PIN_LED_WORK, HIGH);
    digitalWrite(PIN_LED_PAUSE, HIGH);
    delay(500);
    digitalWrite(PIN_LED_WORK, LOW);
    digitalWrite(PIN_LED_PAUSE, LOW);
    delay(500);
  }
}

