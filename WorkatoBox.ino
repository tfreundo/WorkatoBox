// Using timer-library: https://playground.arduino.cc/code/timer
#include "Timer.h"

// Common settings
#define DEBUG true

// Button Settings
const int PIN_BUTTON_WORK = 25;
const int PIN_BUTTON_SHORT_PAUSE = 26;
const int PIN_BUTTON_LONG_PAUSE = 27;

// Enum holding the possible button actions that occur and are handled
enum BUTTON_ACTION {
  WORK,
  SHORT_PAUSE,
  LONG_PAUSE,
  NOTHING
};

// Information about the current state of the Workato Box(working, in short pause, in long pause, idle)
enum WORKATO_STATE {
  WORKING,
  IN_SHORT_PAUSE,
  IN_LONG_PAUSE,
  IN_IDLE
};

// TODO Update to the real values
unsigned long WORKATO_STATE_WORKING_DURATION = 5 * 1000; // 5 seconds
int workatoStateWorkingTimerId = -1;
unsigned long WORKATO_STATE_SHORT_PAUSE_DURATION = 5 * 1000; // 5 seconds
int workatoStateShortPauseTimerId = -1;
unsigned long WORKATO_STATE_LONG_PAUSE_DURATION = 5 * 1000; // 5 seconds
int workatoStateLongPauseTimerId = -1;

int lastWorkatoState = WORKATO_STATE::IN_IDLE;
int currentWorkatoState = WORKATO_STATE::IN_IDLE;

Timer workatoTimer;

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
  }
  pinMode(PIN_BUTTON_WORK, INPUT);
  pinMode(PIN_BUTTON_SHORT_PAUSE, INPUT);
  pinMode(PIN_BUTTON_LONG_PAUSE, INPUT);
}

void loop() {
  workatoTimer.update();
  // TODO Use workatoTimer.oscillate(ledPIN, 500, LOW) to let the LED blink while the timer is running
  // TODO Add an led show that signals when a state ended (e.g. work phase is over)

  BUTTON_ACTION buttonAction = handleButtons();

  // Box is in idle and user wants to start something
  if (currentWorkatoState == WORKATO_STATE::IN_IDLE && buttonAction != BUTTON_ACTION::NOTHING) {
    stopAllWorkatoTimers();
    switch (buttonAction) {
      case WORK:
        if (DEBUG) {
          Serial.println("Starting Work of 25min");
        }
        lastWorkatoState = currentWorkatoState;
        currentWorkatoState = WORKATO_STATE::WORKING;
        workatoStateWorkingTimerId = workatoTimer.after(WORKATO_STATE_WORKING_DURATION, workatoStateEnded, 0); // Setting optional context to 0
        break;
      case SHORT_PAUSE:
        if (DEBUG) {
          Serial.println("Starting short Pause of 5min");
        }
        lastWorkatoState = currentWorkatoState;
        currentWorkatoState = WORKATO_STATE::IN_SHORT_PAUSE;
        workatoStateShortPauseTimerId = workatoTimer.after(WORKATO_STATE_SHORT_PAUSE_DURATION, workatoStateEnded, 0); // Setting optional context to 0
        break;
      case LONG_PAUSE:
        if (DEBUG) {
          Serial.println("Starting long Pause of 10min");
        }
        lastWorkatoState = currentWorkatoState;
        currentWorkatoState = WORKATO_STATE::IN_LONG_PAUSE;
        workatoStateLongPauseTimerId = workatoTimer.after(WORKATO_STATE_LONG_PAUSE_DURATION, workatoStateEnded, 0); // Setting optional context to 0
        break;
      case NOTHING:
      default:
        break;
    }
  }
  // Box is not in idle and user wants to stop something (when the box is running any button will stop the current state)
  else if (currentWorkatoState != WORKATO_STATE::IN_IDLE && buttonAction != BUTTON_ACTION::NOTHING) {
    if (DEBUG) {
      Serial.print("Interrupting Workato State ");
      Serial.println(currentWorkatoState);
      Serial.println("Going in Workato State IDLE");
    }
    stopAllWorkatoTimers();
    lastWorkatoState = currentWorkatoState;
    currentWorkatoState = WORKATO_STATE::IN_IDLE;
  }
}

void workatoStateEnded(void* context) {
  if (DEBUG) {
    Serial.print("Finished Workato State ");
    Serial.println(currentWorkatoState);
  }
  stopAllWorkatoTimers();
  currentWorkatoState = WORKATO_STATE::IN_IDLE;
  // TODO Run the led show
}

void stopAllWorkatoTimers() {
  if (DEBUG) {
    Serial.println("Stopping all timers");
  }
  workatoTimer.stop(workatoStateWorkingTimerId);
}


