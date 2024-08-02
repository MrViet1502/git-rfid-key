#include "global.h"

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Lectura del UID");

  pinMode(LED_BUILTIN, OUTPUT);              // led for test arduino mini
  pinMode(HOLD_PIN, OUTPUT);                 // hold power
  pinMode(BUZZER_PIN, OUTPUT);               // buzzer
  pinMode(CONTROLER_PIN, OUTPUT);            // power for controler
  pinMode(BUTTON_READ_PIN, INPUT_PULLUP);    // read this button for hold power
  pinMode(READ_CONTROLER_PIN, INPUT_PULLUP); // read from controler
  digitalWrite(HOLD_PIN, LOW);               // hold power: off
  digitalWrite(BUZZER_PIN, HIGH);            // buzzer: off
  digitalWrite(CONTROLER_PIN, HIGH);         // power: off for controler
  loadCardsFromEEPROM();
  // clearEEPROM(); // clear eeprom
}

void loop()
{
  pressButtonRForOpenAndClose(); // check button R for open

  switch (currentState)
  {
  case IDLE_STATE:
    if (isHoldForOpen())
    {
      currentState = WAIT_FOR_CARD;
    }
    break;

  case WAIT_FOR_CARD:
    checkButtonRForSetupMode(); // check button R for setup mode

    if (isSetupModeActive() && !overTime(setupTime, TIME_SETUPMODE))
    {
      currentState = SETUP_MODE;
    }
    else if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
    {
      currentState = CARD_SCANNED;
    }

    // off hold if within 30s isSetupMode = false and card has't been scanned
    overTimeOffHold();

    // off hold if within 10s controler don't send signal
    overTimerControlerOffHold();
    break;

  case CARD_SCANNED:
    Serial.print("Card UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();
    mfrc522.PICC_HaltA();

    if (isCardRegistered(mfrc522.uid.uidByte))
    {
      if (checkReadControler)
      {
        offHold();
      }
      else
      {
        onControl();
        currentState = IDLE_STATE;
      } // Return status IDLE_STATE after processing
    }
    else
    {
      currentState = UNAUTHORIZED;
    }
    break;

  case SETUP_MODE:
    handleSetupMode(); // case setup mode
    if (overTime(configTime, TIME_CONFIG_END))
    {
      exitSetupMode(); // case exit setup mode if time out
      currentState = IDLE_STATE;
    }
    break;

  case UNAUTHORIZED:
    Serial.println("Unauthorized card.");
    currentState = IDLE_STATE; // Return status IDLE_STATE after processing
    break;
  }
}
