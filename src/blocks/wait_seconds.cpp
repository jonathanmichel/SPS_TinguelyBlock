#include "../includes/block.h"

#ifdef wait_seconds

boolean blockInit() {
	return true;
}

/* Parameters
1 byte: [ssssssss]
s = seconds [8 bits]
	"0
	…
	255"
*/
byte updateParameters(byte* parametersArray) {
	// @todo Get seconds from arduino pin
	byte seconds = 0x5D;

	// send 8 bytes
	parametersArray[0] = seconds;
	// no padding required
	
	return 1; // one parameter (color), uses 1 byte with padding
}

#endif