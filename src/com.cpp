#include "../includes/com.h"

#include "../includes/debug.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

const byte codeSerialTxPin = 2;
const byte codeSerialRxPin = 3;
const byte debugSerialTxPin = 4;
const byte debugSerialRxPin = 5;

// Use for "up" communication to receive code from the lower block 
// and sent it to the upper one
SoftwareSerial codeSerial(codeSerialRxPin, codeSerialTxPin);  
// Used for "down" communication to receive debug counter from 
// the upper block and send it to the lower one
SoftwareSerial debugSerial(debugSerialRxPin, debugSerialTxPin); 


byte rxBuffer[BUFFER_SIZE];  // rx buffer for code received from lowers blocks
byte txBuffer[BUFFER_SIZE];  // tx buffer for code to send to the upper block
int rxCtn;      // incremented to fill rxBuffer
int txCtn;      // increment to fill txBuffer
boolean readingFrame;  // indicates if we are reading a frame or not

void comInit() {
    // debugSerial.begin(9600);    // initialize debug serial with baud rate of 9600
    codeSerial.begin(9600);     // initialize code serial with baud rate of 9600
    codeSerial.listen();
    pinMode(LED_BUILTIN, OUTPUT);   // set led built in output as output
    // Initialize counters
    rxCtn = 0;
    txCtn = 0;
    // Wait for frame a to read
    readingFrame = false;
}

void resetFrame() {
    txCtn = 0;
}

boolean addHeader() {
    return addChar(START_SYMBOL);
}

boolean addTail() {
    return addChar(END_SYMBOL);
}

boolean addChar(char data) {
    // Clear buffer if too big
    if (txCtn >= BUFFER_SIZE) {
        ERROR_PRINTLN("TxBuffer full !");
        txCtn = 0;
        return false;
    }
    // ... fill buffer otherwise
    txBuffer[txCtn] = data;
    txCtn++;
    return true;
}

boolean addString(char* array, byte size) {
    for(int i = 0; i < size; i++) {
        if(addChar(array[i]) == false) {
            break;
        }
    }
}

void sendFrame() {
    if(txCtn >= BUFFER_SIZE) {
        ERROR_PRINT("Unable to send frame, txCtn (");
        ERROR_PRINT(txCtn);
        ERROR_PRINT(") is bigger than BUFFER_SIZE (");
        ERROR_PRINTLN(BUFFER_SIZE);
    }

    INFO_PRINT("Send frame (");
    INFO_PRINT(txCtn - 1);  // txCtn is incremented when the last char has been added
    INFO_PRINT(" chars long): ");
    for(int i = 0; i < txCtn; i++) {
        Serial.write(txBuffer[i]);
        codeSerial.write(txBuffer[i]);
    }
    INFO_PRINTLN("");

}

int readCodeRx() {
    return 0;
}

int processCodeRx() {
    int res = codeSerial.available();
    if(res == 0) {
        // no data
    } else if (res == -1) {
        // serial unavailable
        FATAL_PRINTLN("Serial unavailable");
    } else {
        char receivedData = codeSerial.read();

        // If the start symbol is received, start frame reading
        if(receivedData == START_SYMBOL) {
            readingFrame = true;
            rxCtn = 0;
        } else if (readingFrame == true) {  // If we are reading frame
            // If the end symbol is received, frame is completed
            if(receivedData == END_SYMBOL) {
                return rxCtn;
            } else if (rxCtn == BUFFER_SIZE) {  // if the buffer is full (we missed the end symbol ?)
                // we reset frame reading
                readingFrame = false;
                rxCtn = 0;
            } else { // if not, we simply store data
                rxBuffer[rxCtn] = receivedData;
                rxCtn++;
            }
        }
    }

    return 0;
}

void processDebugSerial() {
    int res = debugSerial.available();
    if(res == 0) {
        // no data
        // INFO_PRINTLN("Debug serial - No data");
    } else if (res == -1) {
        // serial unavailable
        //FATAL_PRINTLN("Debug serial unavailable");
    } else {
        byte serialDebugCounter = debugSerial.read();
        if (serialDebugCounter == 0) {
            // If current block receives "0", it turns it built-in led on
            INFO_PRINTLN("Debug serial - Current block is addressed");
            digitalWrite(LED_BUILTIN, HIGH);
        } else {
            // otherwise, debug counter is decremented and sent to the lower block
            INFO_PRINT("Debug serial - Send to lower block: ")
            INFO_PRINTLN(serialDebugCounter - 1)
            digitalWrite(LED_BUILTIN, LOW);
            debugSerial.write(serialDebugCounter - 1);
        }
    }
}

boolean copyRxData(char* destArray, int size) {
    if(size > BUFFER_SIZE) {
        ERROR_PRINTLN("Unable to copy rx data, not enough data in RxBuffer");
    } else {
        for(int i = 0; i < size; i ++) {
            // we remove the first char that is the START_SYMBOL
            destArray[i] = rxBuffer[i + 1];
        }
        return true;
    }
    return false;
}
