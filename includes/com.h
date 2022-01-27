#ifndef COM_H
#define COM_H

#include <Arduino.h>

#define BUFFER_SIZE 255 		// chars
#define START_SYMBOL '#'
#define END_SYMBOL '!'

void comInit();
void resetFrame();

boolean addChar(char data);
boolean addString(char* array, byte size);
boolean addHeader();
boolean addTail();

void sendFrame();

int processCodeRx();
void processDebugSerial();

boolean copyRxData(char* destArray, int size);

#endif // COM_H