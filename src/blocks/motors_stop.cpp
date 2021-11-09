#include "../includes/block.h"

#ifdef motors_stop

void block_setup() {
	Serial.println("Je suis motors_stop");
}

void block_loop() {
	Serial.println("Looping motors_stop");
	delay(1000);
}

#endif