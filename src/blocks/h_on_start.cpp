#include "../includes/block.h"

#ifdef h_on_start

boolean blockInit() {
	INFO_PRINTLN("h_on_start block init");
	return true;
}

byte updateParameters(byte* parametersArray) {
	// h_on_start has no parameters
	return 0;
}

#endif