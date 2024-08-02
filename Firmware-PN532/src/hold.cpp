#include "global.h"

bool overTime(long long beginTime, long long Time)
{
    if (millis() - beginTime >= Time)
        return true;
    else
        return false;
}

void onHold() // function to on hold
{
    digitalWrite(HOLD_PIN, HIGH); // for next time Hold_PWR: off
    buzzerBeep(2, 400);
    holdHigh = true;      // hold is high
    holdTime = millis();  // begin time for hold
    setupTime = millis(); // begin time for setup
}

void offHold() // function to on hold
{
    buzzerBeep(2, 400);
    digitalWrite(HOLD_PIN, LOW); // for next time Hold_PWR: off
}

void overTimeOffHold()
{
    if (holdHigh && holdOffFirstTime && !isSetupModeActive() && overTime(holdTime, TIME_NOCARD_MID)) // over 30s (holdHigh = 1 and isSetupModeActive = 0) -> off
    {
        if (!checkBuzzerHold)
        {
            // Serial.println("15s over no scan card");
            buzzerBeepIncreasing(500, 100, 8);
            checkBuzzerHold = true;
        }

        if (overTime(holdTime, TIME_NOCARD_END))
            offHold(); // off Hold
    }
}

void overTimerControlerOffHold()
{
    if (checkReadControler) // check off hold when over time controler
    {
        controlControler();
    }
}