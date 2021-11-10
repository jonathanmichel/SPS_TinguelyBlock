#include "../includes/com.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

const byte txPin = 2;
const byte rxPin = 3;

SoftwareSerial softwareSerial(rxPin, txPin);


void serialInit() {
    softwareSerial.begin(9600);              // initialize UART with baud rate of 9600
}

byte getHexAscii(char hex) {
    // Convert 0 to '0' (48), 8 (a) to 'A' (65), ...
    hex = hex & 0x0F;
    if(hex >= 9) {      // 10 to 16: 'A' to 'F'
        return 'A' + (hex - 'A');
    } else {            // 0 to 9: '0' to '9'
        return '0' + hex;
    }
}

// Send raw data as byte
void sendByte(byte data) {
    Serial.write(data);
    Serial.println("");
    // Do not use Serial.print() because it converts 
    // data to its representation as characters
    softwareSerial.write(data);
}

// Convert char as ASCII byte value
void sendChar(char data) {
    sendByte(getHexAscii(data));
}

void sendHeader() {
    sendByte(START_HEAD);
}

void sendTail() {
    sendByte(END_TRANSMISSION);
}