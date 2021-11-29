#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef c_forever

boolean blockInit() {
	INFO_PRINTLN("c_forever block init");
	return true;
}

byte readParameters(byte* parametersArray) {
	// c_forever has no parameters
	return 0; // use 0 byte
}

#endif
