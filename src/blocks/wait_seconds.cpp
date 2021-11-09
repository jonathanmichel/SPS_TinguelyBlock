#include "../includes/block.h"

#ifdef wait_seconds

void block_setup() {
	Serial.println("Je suis wait_seconds");
}

void block_loop() {
	Serial.println("Looping wait_seconds");
	delay(1000);
}

#endif