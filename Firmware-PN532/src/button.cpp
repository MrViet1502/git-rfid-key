#include "global.h"

bool isSetupModeActive() // enter mode Setup
{
  return isSetupMode;
}

void checkButtonRemoveAll()
{
  if (digitalRead(BUTTON_READ_PIN) == LOW)
  {
    if (buttonPressTime_R == 0)
    {
      buttonPressTime_R = millis();
      check_millis = true;
    }

    if (millis() - buttonPressTime_R >= 4000 && isSetupMode)
    {
      removeAll();
      check_millis = false;
      buzzerBeep(3, 500); // Buzzer sounds 3 times for 1 second each time
    }
    if (check_millis)
    {
      buttonPressTime_R = 0;
      check_millis = false;
    }
  }
  else
  {
    buttonPressTime_R = 0;
  }
}

// button R
bool isHoldForOpen() // check button in 10s
{
  return checkBTRead;
}

// test setupmode button R replace button config
void checkButtonRForSetupMode() // Check button R 2 times
{
  // Read status of button
  bool reading = digitalRead(BUTTON_READ_PIN);

  // if button state has changed since last read
  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // if button state has changed
    if (reading != buttonState)
    {
      buttonState = reading;

      // Count number of button presses
      if (buttonState == LOW)
      { // Button is pressed
        unsigned long currentTime = millis();
        // Limit number of button presses to min (200ms) and max (1000ms)
        if (currentTime - lastPressTime >= minPressInterval && currentTime - lastPressTime <= maxPressInterval)
        {
          pressCounter++;
        }
        else
        {
          pressCounter = 1; // Reset press counter
        }
        lastPressTime = currentTime;

        // if (pressCounter = 2 and isSetupMode = false) => setup mode start
        if (pressCounter == 2 && !isSetupMode)
        {
          // Serial.println("Entering setup mode...");
          isSetupMode = true;    // setup mode active
          holdTime = millis();   // set hold time to millis
          configTime = millis(); // set config time to millis
          buzzerBeep(3, 300);    // Buzzer sounds 3 times for 1 second each time
        }
      }
    }
  }

  // store button state for next time
  lastButtonState = reading;

  // Reset count
  if (pressCounter == 2)
  {
    pressCounter = 0;
  }
}

// open and close door
void pressButtonRForOpenAndClose() // check button in 4s
{
  if (digitalRead(BUTTON_READ_PIN) == LOW)
  {
    if (buttonPressTime_R == 0) // first time press
    {
      buttonPressTime_R = millis();
      // Serial.println(buttonPressTime_R);
    }
    if (millis() - buttonPressTime_R >= 300 && !checkBTRead)
    {
      buttonPressTime_R = 0;
      checkBTRead = true;
      // Serial.println("Opening door...");
      onHold();
    }
    else if (millis() - buttonPressTime_R >= 2000 && checkBTRead && !isSetupMode)
    {
      buttonPressTime_R = 0;
      checkBTRead = false;
      // Serial.println("Closing door..."); // one time beep for 2 seconds
      offHold();
    }
  }

  else
  {
    buttonPressTime_R = 0;
  }
  buttonPressTime_R == 0;
}