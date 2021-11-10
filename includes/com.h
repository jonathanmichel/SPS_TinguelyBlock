#ifndef COM_H
#define COM_H

#include <Arduino.h>

// According to ASCII table
#define START_HEAD 0x1
#define END_TRANSMISSION 0x4

void serialInit();
void sendByte(byte data);
void sendChar(char data);
void sendId();
void sendHeader();
void sendTail();

byte getHexAscii(char hex);

#endif // COM_H