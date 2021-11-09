#include "../includes/block.h"

#ifdef motors_run_direction

void block_setup() {
	Serial.println("Je suis motors_run_direction");
}

void block_loop() {
	Serial.println("Looping motors_run_direction");
	delay(1000);
}

#endif