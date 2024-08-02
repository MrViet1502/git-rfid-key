#ifndef CARD_H
#define CARD_H

#include "global.h"

bool isCardRegistered(byte *uid);
void storeCard(byte *uid);
void removeCard(byte *uid);
void removeAll();
bool isMasterCard(byte *uid);
bool readNFC();
#endif // CARD_H
