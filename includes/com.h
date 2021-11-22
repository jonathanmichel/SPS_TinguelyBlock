#ifndef COM_H
#define COM_H

#include <Arduino.h>

#define RX_BUFFER_SIZE 255 		// bytes
// According to ASCII table
#define START_HEAD 0x1          // [SOH]
#define END_TRANSMISSION 0x4    // [EOT]

void comInit();
void sendByte(byte data);
void sendChar(char data);

void sendHeader();
void sendTail();

int processRx();

void sendData(byte* array, int size);
boolean copyRxData(byte* destArray, int size);

byte getHexAscii(char hex);

#endif // COM_H