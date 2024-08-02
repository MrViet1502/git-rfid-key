#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
// #include <MFRC522.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <EEPROM.h>
#include "button.h"
#include "buzzer.h"
#include "card.h"
#include "setup_mode.h"
#include "save_eeprom.h"
#include "hold.h"
#include "controler.h"
// Arduino mini
// Pin definitions
// #define RST_PIN 9
// #define SS_PIN 10         // Pin 10 Arduino Mini
// #define HOLD_PIN 7        // Pin 7 Arduino Mini relay
// #define BUZZER_PIN 8      // Pin 8  Arduino Mini buzzer
// #define BUTTON_READ_PIN 5 // Pin 5 Arduino Mini
// #define LED_BUILTIN 13
// #define CONTROLER_PIN 4      // Pin 4 Arduino Mini
// #define READ_CONTROLER_PIN 6 // pin 6 Arduino Mini
// Mega 2560
#define RST_PIN 9
#define SS_PIN 53     // Pin 10 Arduino Mini
#define HOLD_PIN 40   // Pin 7 Arduino Mini relay
#define BUZZER_PIN 41 // Pin 8  Arduino Mini buzzer
#define BUTTON_PIN 30 // Pin 6 Arduino Mini button
#define LED_BUILTIN 13
#define BUTTON_READ_PIN 28 // Pin 5 Arduino Mini

#define CONTROLER_PIN 34      // Pin 0  RX
#define READ_CONTROLER_PIN 26 // pin 1 TX

// State
enum State
{
  IDLE_STATE,
  WAIT_FOR_CARD,
  CARD_SCANNED,
  SETUP_MODE,
  UNAUTHORIZED
};

extern State currentState;

// State Setup Mode
enum SetupState
{
  IDLE_SETUP,
  WAIT_FOR_MASTER_CARD,
  MASTER_CARD_DETECTED,
  ADD_OR_REMOVE_CARD
};

extern SetupState currentStateSetup; // Status begin

// Time
#define TIME_SETUPMODE 15000  // 15s
#define TIME_NOCARD_MID 15000 // 15s
#define TIME_NOCARD_END 30000 // 30s
#define TIME_NOPULSE 30000    // 30s
#define TIME_CONFIG_END 30000 // 30s
extern PN532_I2C pn532_i2c;
extern NfcAdapter nfc;
extern String tagId;
extern byte nuidPICC[4];
// RFID
#define MAX_CARDS 4 // max number of cards
// extern MFRC522 mfrc522;
// struct Card
// {
//   byte uid[4];
// };
extern unsigned int uidLength;
extern byte uid[10];
struct Card
{
  byte uid[10];           // Tăng kích thước mảng để chứa UID dài hơn nếu cần
  unsigned int uidLength; // Thêm biến để lưu độ dài UID
};
extern Card registeredCards[MAX_CARDS];

extern uint8_t cardCount; // size current number of cards
extern bool masterCardConfirmed;

// Button R
extern unsigned long buttonPressTime_R;

// Hold
extern bool holdOffFirstTime; // off hold first time
extern bool holdHigh;         // check status hold
extern unsigned int holdTime; // time hold
extern bool checkBTRead;      // check when button R is pressed 4s first time
extern bool checkBuzzerHold;  // for buzzer hold: off

// Setup Mode
extern bool check_millis;              // for remove all
extern bool buttonState;               // store button state
extern bool lastButtonState;           // store last button state
extern uint8_t pressCounter;           // count number of button presses
extern unsigned long lastDebounceTime; // time of last debounce
extern unsigned long debounceDelay;    // debounce time
extern unsigned long lastPressTime;    // time of last button press
extern unsigned int minPressInterval;  // minimum time between button presses
extern unsigned int maxPressInterval;  // maximum time between button presses
extern bool isSetupMode;               // false: normal mode, true: setup mode
extern bool isRemoveAll;               // state remove all
extern bool config;                    // end add, delete, delete all
extern unsigned int setupTime;         // time for setup (over this time -> off setup mode)
extern unsigned int configTime;        // over this time without scanning the master card -> off config mode
extern bool awaitingMasterCard;        // check master card

// Controler
extern bool inputState;              // state current input
extern bool lastInputState;          // state last input
extern unsigned long lastChangeTime; // last change time
extern bool checkReadControler;      // check controler
extern unsigned long controlerTime;  // over this time -> off hold
extern bool checkBuzzerControl;      // for buzzer control: off and hold: off
#endif                               // GLOBAL_H
