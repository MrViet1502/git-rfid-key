#include "global.h"

void buzzerBeep(int times, int duration) // The buzzer function sounds times and duration seconds
{
    for (int i = 0; i < times; i++)
    {
        digitalWrite(BUZZER_PIN, LOW);
        delay(duration);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(200); // Delay between calls
    }
}

void buzzerBeepIncreasing(int startDelay, int endDelay, int steps)
{
    int delayStep = (startDelay - endDelay) / steps;
    int currentDelay = startDelay;

    for (int i = 0; i < steps; i++)
    {
        digitalWrite(BUZZER_PIN, LOW); // Buzzer on
        delay(currentDelay);
        digitalWrite(BUZZER_PIN, HIGH); // Buzzer off
        delay(currentDelay);

        if (currentDelay > endDelay)
        {
            currentDelay -= delayStep;
        }
    }
}
