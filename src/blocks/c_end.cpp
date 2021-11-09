#include "../includes/block.h"

#ifdef c_end

void block_setup() {
	Serial.println("Je suis c_end");
}

void block_loop() {
	Serial.println("Looping c_end");
	delay(1000);
}

#endif