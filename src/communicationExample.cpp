#include <Arduino.h>
#include <SoftwareSerial.h>

#include "../includes/com.h"

// Change here to programm RX or TX arduino
// Comment to use main code in main.cpp

// #define RX // RX or TX

// COM3 (Tx) or COM4 (Rx)

#ifdef RX
/*
  Receiver code
*/
const byte txPin = 2;
const byte rxPin = 3;

SoftwareSerial input(rxPin, txPin);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);             // initialize serial communication at 9600 bits per second:
  input.begin(9600);              // initialize UART with baud rate of 9600
  Serial.println("Setup");
}

void loop() {
  Serial.println("Reading data...");
  while(true) {
    int res = input.available();
    if(res == 0) {
      // no data
    } else if (res == -1) {
      // serial unavailable
      break;
    } else {
      byte receivedData = input.read();
      if (receivedData == START_HEAD) {
        Serial.println("New message:");
      } else if (receivedData == END_TRANSMISSION) {
        Serial.println("\n\r------------");
      } else {
        if (receivedData >= '0' && receivedData <= '1') {
          Serial.write(receivedData);
        }
      }

      /*
      if (receivedData == 1) {
        digitalWrite(LED_BUILTIN, HIGH);  // switch LED On
        Serial.println("Received high");
      }
      else if (receivedData == 0) {
        digitalWrite(LED_BUILTIN, LOW);  // switch LED Off
        Serial.println("Received low");
      }
      */
    }
  }
  Serial.println("Exiting");  
}

#endif // RX

#ifdef TX

/*
  Transmitter code
/*/
const byte txPin = 2;
const byte rxPin = 3;

SoftwareSerial output(rxPin, txPin);

void sendValue(char data) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  output.print(data);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);             // initialize serial communication at 9600 bits per second:
  output.begin(9600);             // initialize UART with baud rate of 9600
}

void loop() {
  sendValue(0x1);
  Serial.println("Send high");
  delay(1000);                       // wait for a second
  sendValue(0x0);
  Serial.println("Send low");
  delay(1000);                       // wait for a second
}

#endif // TX