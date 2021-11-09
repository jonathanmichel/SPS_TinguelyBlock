#include "../includes/block.h"

#ifdef h_on_start

void block_setup() {
	Serial.println("Je suis h_on_start");
}

void block_loop() {
	Serial.println("Looping h_on_start");
	delay(1000);
}

#endif