#include "global.h"
// #include "main.cpp"
void exitSetupMode()
{
  // Serial.println("Exiting setup mode...");
  isSetupMode = false;
  awaitingMasterCard = false; // Reset the flag for next time
  config = false;
  isRemoveAll = false;
  holdTime = millis(); // mark for next time (30s power off)
  buzzerBeep(2, 500);
  currentStateSetup = IDLE_SETUP; // Reset trạng thái về IDLE_SETUP
  return;
}

void handleSetupMode()
{
  switch (currentStateSetup)
  {
  case IDLE_SETUP:
    if (cardCount == 0)
    {
      // No cards present, store the first card as master
      if (readNFC())
      {
        buzzerBeep(4, 300);
        memcpy(registeredCards[cardCount].uid, uid, uidLength);
        registeredCards[cardCount].uidLength = uidLength;
        cardCount++;
        saveCardsToEEPROM(); // Save the new master card to EEPROM
        // mfrc522.PICC_HaltA();
        //  Serial.println("Master card stored. Press the button to exit setup mode.");
      }
    }
    else
    {
      currentStateSetup = WAIT_FOR_MASTER_CARD;
    }
    configTime = millis(); // mark changes in setup mode
    break;

  case WAIT_FOR_MASTER_CARD:
    if (readNFC())
    {
      if (isMasterCard(uid))
      {
        awaitingMasterCard = true;
        buzzerBeep(2, 300);
        // mfrc522.PICC_HaltA();
        //  Serial.println("Master card detected. You can now add or remove cards.");
        currentStateSetup = MASTER_CARD_DETECTED;
      }
      else
      {
        buzzerBeep(1, 300);
        // mfrc522.PICC_HaltA();
        //  Serial.println("Not a master card, please try again");
      }
    }
    configTime = millis(); // mark changes in setup mode
    break;

  case MASTER_CARD_DETECTED:
    if (awaitingMasterCard)
    {
      currentStateSetup = ADD_OR_REMOVE_CARD;
    }
    configTime = millis(); // mark changes in setup mode
    break;

  case ADD_OR_REMOVE_CARD:
    if (readNFC())
    {
      if (!isCardRegistered(uid) && !config)
      {
        storeCard(uid); // insert card
        // mfrc522.PICC_HaltA();
        config = true;
        // Serial.println("Card stored. Press the button to exit setup mode.");
      }
      else if (isCardRegistered(uid) && !config)
      {
        removeCard(uid); // remove card
        // mfrc522.PICC_HaltA();
        config = true;
        // Serial.println("Card removed. Press the button to exit setup mode.");
      }
    }

    if (digitalRead(BUTTON_READ_PIN) == LOW && buttonPressTime_R == 0 && config)
    {
      delay(100); // Debounce delay
      while (digitalRead(BUTTON_READ_PIN) == LOW)
      {
        // Wait for the button to be released
      }
      exitSetupMode();           // out setup mode
      currentState = IDLE_STATE; // reset state
      return;
    }
    checkButtonRemoveAll();
    configTime = millis(); // mark changes in setup mode
    break;
  }
  setupTime = millis();
}