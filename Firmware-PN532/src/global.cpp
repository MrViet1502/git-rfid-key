#include "global.h"

// State
State currentState = IDLE_STATE;           // fisrt state
SetupState currentStateSetup = IDLE_SETUP; // fisrt state setup mode

// RFID
// MFRC522 mfrc522(SS_PIN, RST_PIN);
// Card registeredCards[MAX_CARDS];     // save cards

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
// String tagId = "None";
// byte nuidPICC[4];
byte uid[10];
unsigned int uidLength;

Card registeredCards[MAX_CARDS] = {};

uint8_t cardCount = 0;            // count number of cards
bool masterCardConfirmed = false; // check master card

// Button R
unsigned long buttonPressTime_R = 0; // button does not pressed

// Hold
bool holdOffFirstTime = true; // begin hold on if no card
bool holdHigh = false;        // on relay.cpp , check state relay on/ of
unsigned int holdTime = 0;    // time for hold: 10s to use device
bool checkBTRead = false;     // on relay.cpp , check state relay on/ of
bool checkBuzzerHold = false; // buzzer on 15s

// Setup Mode
bool check_millis = false;   // on button.cpp , check millis() function
bool buttonState = HIGH;     // normal state
bool lastButtonState = HIGH; // store last state of button R
uint8_t pressCounter = 0;    // count number of button presses
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long lastPressTime = 0;
unsigned int minPressInterval = 100;  // (100ms)
unsigned int maxPressInterval = 1000; // (1000ms)
bool isSetupMode = false;             // false: normal mode, true: setup mode
bool isRemoveAll = false;             // state remove all cards
bool config = false;                  // add and remove card in one card
unsigned int setupTime = 0;           // time for setup mode
unsigned int configTime = 0;          // time for config mode
bool awaitingMasterCard = false;      // New flag to handle waiting for the master card

// Controler
bool inputState = HIGH;
bool lastInputState = HIGH;
unsigned long lastChangeTime;
bool checkReadControler = false;
unsigned long controlerTime = 0;
bool checkBuzzerControl = false;
