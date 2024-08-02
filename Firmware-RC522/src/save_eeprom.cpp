#include "global.h"

void loadCardsFromEEPROM() // Load cards from EEPROM to array of cards
{
    int numCards = EEPROM.read(0); // Read number cards from EEPROM
    if (numCards > MAX_CARDS)
    {
        numCards = MAX_CARDS; //
    }

    cardCount = numCards; // Update number of cards
    int address = 1;      // address start store UID cards

    for (int i = 0; i < numCards; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            registeredCards[i].uid[j] = EEPROM.read(address++); // Read a UID card to  EEPROM
        }
    }
}
void saveCardsToEEPROM() // save cards to EEPROM
{
    int numCards = cardCount;
    if (numCards > MAX_CARDS)
    {
        numCards = MAX_CARDS; //
    }

    EEPROM.write(0, numCards); // Save number cards to EEPROM
    int address = 1;           // Address start store card UID

    for (uint8_t i = 0; i < numCards; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            EEPROM.write(address++, registeredCards[i].uid[j]); // write a byte from EEPROM
        }
    }
}

void clearEEPROM()
{
    // Delete eeprom
    for (uint8_t i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0);
    }
}
