#include "../includes/block.h"

#ifdef set_status_light

void block_setup() {
	Serial.println("Je suis set_status_light");
}

void block_loop() {
	Serial.println("Looping set_status_light");
	delay(1000);
}

#endif