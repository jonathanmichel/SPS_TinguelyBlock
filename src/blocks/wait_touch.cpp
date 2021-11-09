#include "../includes/block.h"

#ifdef wait_touch

void block_setup() {
	Serial.println("Je suis wait_touch");
}

void block_loop() {
	Serial.println("Looping wait_touch");
	delay(1000);
}

#endif
