#include "global.h"

void onControl()
{
    Serial.println("Power on controler");
    digitalWrite(CONTROLER_PIN, HIGH);
    buzzerBeep(1, 1000);
    checkReadControler = true; // for scan card again when off hold
    holdOffFirstTime = false;  // for on hold
    lastChangeTime = millis(); // time for HB
}

// Read pulse from controler
// if over 10s then off hold
void controlControler()
{
    inputState = digitalRead(READ_CONTROLER_PIN);

    if (inputState != lastInputState)
    {
        lastChangeTime = millis();
        lastInputState = inputState;
        Serial.println("HB");
    }

    if (millis() - lastChangeTime > TIME_NOPULSE)
    {
        // Serial.println("over time for HB");
        offHold();
    }
}
