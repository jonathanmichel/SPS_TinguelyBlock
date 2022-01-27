#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef c_end

boolean blockInit() {
	INFO_PRINTLN("c_end block init");
	return true;
}

byte readParameters(char* parametersArray) {
	// c_end has no parameters
	return 0; // use 0 char
}

#endif