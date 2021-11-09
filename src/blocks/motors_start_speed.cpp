#include "../includes/block.h"

#ifdef motors_start_speed

void block_setup() {
	Serial.println("Je suis motors_start_speed");
}

void block_loop() {
	Serial.println("Looping motors_start_speed");
	delay(1000);
}

#endif