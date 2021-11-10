#ifndef COM_H
#define COM_H

#include <Arduino.h>

#define RX_BUFFER_SIZE 255 		// bytes
// According to ASCII table
#define START_HEAD 0x1          // [SOH]
#define END_TRANSMISSION 0x4    // [EOT]

extern byte rxBuffer[RX_BUFFER_SIZE];  // rx buffer for code received from other blocks
extern int rxCtn;      // incremented to fill rxBuffer
extern int binaryCtn;  // decremented to count data to receive

void serialInit();
void sendByte(byte data);
void sendChar(char data);

void sendHeader();
void sendTail();

void sendData(char* array, int size);
void sendChildren();

byte getHexAscii(char hex);

#endif // COM_H