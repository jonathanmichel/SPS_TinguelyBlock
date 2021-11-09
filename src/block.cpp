#include <Arduino.h>

#include "../includes/block.h"

void setup() {
  Serial.begin(9600);             // initialize serial communication at 9600 bits per second:
  block_setup();
  Serial.print("Id: ");
  Serial.print(BLOCK_ID);
  Serial.print(" (0b");
  Serial.print(BLOCK_ID_BIN);
  Serial.print("), size: ");
  Serial.print(BLOCK_SIZE);
  Serial.print(", type: ");
  Serial.println(BLOCK_TYPE);
}

void loop() {
  block_loop();
}