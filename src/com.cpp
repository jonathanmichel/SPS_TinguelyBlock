#include "../includes/com.h"

#include "../includes/debug.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

const byte txPin = 2;
const byte rxPin = 3;

SoftwareSerial softwareSerial(rxPin, txPin);

byte rxBuffer[RX_BUFFER_SIZE];  // rx buffer for code received from other blocks
int rxCtn;      // incremented to fill childrenData
int binaryCtn;  // decremented to count data to receive

void comInit() {
    softwareSerial.begin(9600);              // initialize UART with baud rate of 9600
    // Initialize counters
    rxCtn = 0;
    binaryCtn = 0;
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
    INFO_PRINTLN(data, HEX);
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

void sendData(byte* array, int size) {
    DEBUG_PRINT("-- Send raw data ");
    DEBUG_PRINT(size);
    DEBUG_PRINTLN(" byte(s):");
    for(int i = 0; i < size; i++) {
        sendByte(array[i]);
    }
}

int processRx() {
    int res = softwareSerial.available();
    if(res == 0) {
        // no data
    } else if (res == -1) {
        // serial unavailable
        FATAL_PRINTLN("Serial unavailable");
    } else {
        byte receivedData = softwareSerial.read();

        // If binaryCtn is not 0, we are currently receiving data ...
        if(binaryCtn > 0) { 
            // ... so we fill the array
            rxBuffer[rxCtn++] = receivedData;
            // ... and decrement binaryCtn 
            binaryCtn--;

            // Print receivedData in hex with 2 digits
            DEBUG_PRINT("Rx: ");
            DEBUG_PRINT(receivedData < 16 ? "0" : "");
            DEBUG_PRINTLN(receivedData, HEX);

            if(rxCtn == RX_BUFFER_SIZE) {
                ERROR_PRINTLN("rxBuffer full");
                binaryCtn = 0;
                // @todo possible bug if EOT is not checked below !
            }

            if(binaryCtn == 0) {
                DEBUG_PRINT("Full frame received: ");
                DEBUG_PRINTLN(rxCtn);

                return rxCtn;

                /*/ @Todo - Read and check EOT
                if(receivedData == END_TRANSMISSION) {
                    // ... and save the received frame
                    Serial.print("Full frame received: ");
                    Serial.println(rxCtn);
                } else {
                    // ... or discard it otherwise
                    Serial.println("Incorrect frame received");
                    binaryCtn = 0;
                }
                //*/
            }
        } else if (binaryCtn == -1) { // current byte is supposed to be frame length (0-255)
            binaryCtn = receivedData;
            if (binaryCtn > RX_BUFFER_SIZE) {
                ERROR_PRINTLN("Frame is too big for current rxBuffer");
                binaryCtn = 0;
            } else {
                DEBUG_PRINT("Start reading frame: ");
                DEBUG_PRINTLN(binaryCtn);
            }
        } else if (receivedData == START_HEAD) {  // If we are not receiving new data, we wait SOH
            // Once SOH is received, the next byte indicates the data length
            // By changing binaryCtn, we activate binary receiving. Next step will be to read frame length
            binaryCtn = -1; 
            rxCtn = 0;
            // Serial.println("Begin of frame detected");
        }
    }

    return 0;
}

boolean copyRxData(byte* destArray, int size) {
    if(size > RX_BUFFER_SIZE) {
        ERROR_PRINTLN("Unable to copy rx data, not enough data in RxBuffer");
    } else {
        for(int i = 0; i < size; i ++) {
            destArray[i] = rxBuffer[i];
        }
        return true;
    }
    return false;
}