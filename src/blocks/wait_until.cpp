#include "../includes/block.h"
#include "../includes/boolean.h"
#include "../includes/debug.h"

#ifdef wait_until

boolean blockInit() {
	INFO_PRINTLN("wait_until block init");
	return true;
}

/* Parameters
1 byte + x: [ssssssss][bbbbbbbb][...]
s = boolean size [ 8 bits]
b = boolean [x bytes]
	binary value
*/
byte readParameters(byte* parametersArray) {
	// Change boolean chose is boolean.h
	byte length = updateBoolean(parametersArray);
	return length;
}

#endif
