#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef h_on_start

boolean blockInit() {
	INFO_PRINTLN("h_on_start block init");
	return true;
}

byte readParameters(byte* parametersArray) {
	// h_on_start has no parameters
	return 0; // use 0 byte
}

#endif