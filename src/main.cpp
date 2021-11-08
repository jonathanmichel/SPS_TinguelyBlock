#include <Arduino.h>
#include <SoftwareSerial.h>

/*
  Receiver code
/*/
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
  Serial.println("Waiting...");
  while (input.available() >= 0) {
    char receivedData = input.read();   // read one byte from serial buffer and save to receivedData
    if (receivedData == '1') {
      digitalWrite(LED_BUILTIN, HIGH);  // switch LED Off
      Serial.println("Received high");
    }
    else if (receivedData == '0') {
      digitalWrite(LED_BUILTIN, LOW);  // switch LED Off
      Serial.println("Received low");
    }
  }
}

//*/

/*
  Transmitter code
//
const byte txPin = 2;
const byte rxPin = 3;

SoftwareSerial output(rxPin, txPin);

void sendData(char data) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  output.println(data);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);             // initialize serial communication at 9600 bits per second:
  output.begin(9600);             // initialize UART with baud rate of 9600
}

void loop() {
  sendData('1');
  Serial.println("Send high");
  delay(1000);                       // wait for a second
  sendData('0');
  Serial.println("Send low");
  delay(1000);                       // wait for a second
}

//*/