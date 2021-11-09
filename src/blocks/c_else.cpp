#include "../includes/block.h"

#ifdef c_else

void block_setup() {
	Serial.println("Je suis c_else");
}

void block_loop() {
	Serial.println("Looping c_else");
	delay(1000);
}

#endif