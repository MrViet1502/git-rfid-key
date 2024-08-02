#ifndef CARD_H
#define CARD_H

#include "global.h"

bool isCardRegistered(byte *uid);
void storeCard(MFRC522::Uid uid);
void removeCard(byte *uid);
void removeAll();
bool isMasterCard(byte *uid);
#endif // CARD_H
