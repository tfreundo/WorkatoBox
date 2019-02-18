// Variables for Button Work
int buttonState_work;
int lastButtonState_work = LOW;
unsigned long lastDebounceTime_work = 0; // The last time the output pin was toggled

// Variables for Button Short Pause
int buttonState_shortPause;
int lastButtonState_shortPause = LOW;
unsigned long lastDebounceTime_shortPause = 0; // The last time the output pin was toggled

// Variables for Button Long Pause
int buttonState_longPause;
int lastButtonState_longPause = LOW;
unsigned long lastDebounceTime_longPause = 0; // The last time the output pin was toggled

const unsigned long DEBOUNCE_DELAY = 150; // The debounce time (should be increased if flickering occurs)



BUTTON_ACTION handleButtons(){
  BUTTON_ACTION result = BUTTON_ACTION::NOTHING;

  // ###################
  // ### Button Work ###
  // ###################
  int reading_work = digitalRead(PIN_BUTTON_WORK);
  
  // Debouncing logic (checking twice to make sure it was no noise but an actual press by the user)
  if(reading_work != lastButtonState_work){
    lastDebounceTime_work = millis();
  }

  if((millis()-lastDebounceTime_work) > DEBOUNCE_DELAY){
    // It's an acutal press by the user, handle accordingly
    if(reading_work != buttonState_work){
      buttonState_work = reading_work;

      if(buttonState_work == HIGH){
        result = BUTTON_ACTION::WORK;
      }
    }
  }

  lastButtonState_work = reading_work;

  // ##########################
  // ### Button Short Pause ###
  // ##########################
  int reading_shortPause = digitalRead(PIN_BUTTON_SHORT_PAUSE);
  
  // Debouncing logic (checking twice to make sure it was no noise but an actual press by the user)
  if(reading_shortPause != lastButtonState_shortPause){
    lastDebounceTime_shortPause = millis();
  }

  if((millis()-lastDebounceTime_shortPause) > DEBOUNCE_DELAY){
    // It's an acutal press by the user, handle accordingly
    if(reading_shortPause != buttonState_shortPause){
      buttonState_shortPause = reading_shortPause;

      if(buttonState_shortPause == HIGH){
        result = BUTTON_ACTION::SHORT_PAUSE;
      }
    }
  }

  lastButtonState_shortPause = reading_shortPause;

  // #########################
  // ### Button Long Pause ###
  // #########################
  int reading_longPause = digitalRead(PIN_BUTTON_LONG_PAUSE);
  
  // Debouncing logic (checking twice to make sure it was no noise but an actual press by the user)
  if(reading_longPause != lastButtonState_longPause){
    lastDebounceTime_longPause = millis();
  }

  if((millis()-lastDebounceTime_longPause) > DEBOUNCE_DELAY){
    // It's an acutal press by the user, handle accordingly
    if(reading_longPause != buttonState_longPause){
      buttonState_longPause = reading_longPause;

      if(buttonState_longPause == HIGH){
        result = BUTTON_ACTION::LONG_PAUSE;
      }
    }
  }

  lastButtonState_longPause = reading_longPause;
  
  return result;
}

