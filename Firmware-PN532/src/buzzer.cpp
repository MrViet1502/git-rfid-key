#include "global.h"

void buzzerBeep(int times, int duration) // The buzzer function sounds times and duration seconds
{
    for (int i = 0; i < times; i++)
    {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(duration);
        digitalWrite(BUZZER_PIN, LOW);
        delay(200); // Delay between calls
    }
}

void buzzerBeepIncreasing(int startDelay, int endDelay, int steps)
{
    int delayStep = (startDelay - endDelay) / steps;
    int currentDelay = startDelay;

    for (int i = 0; i < steps; i++)
    {
        digitalWrite(BUZZER_PIN, HIGH); // Buzzer on
        delay(currentDelay);
        digitalWrite(BUZZER_PIN, LOW); // Buzzer off
        delay(currentDelay);

        if (currentDelay > endDelay)
        {
            currentDelay -= delayStep;
        }
    }
}
