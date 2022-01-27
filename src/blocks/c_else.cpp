#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef c_else

boolean blockInit() {
	INFO_PRINTLN("c_else block init");
	return true;
}

byte readParameters(char* parametersArray) {
	// c_else has no parameters
	return 0; // use 0 char
}

#endif