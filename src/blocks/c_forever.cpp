#include "../includes/block.h"

#ifdef c_forever

void block_setup() {
	Serial.println("Je suis c_forever");
}

void block_loop() {
	Serial.println("Looping c_forever");
	delay(1000);
}

#endif
