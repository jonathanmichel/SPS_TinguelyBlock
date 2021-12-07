#include "../includes/block.h"
#include "../includes/debug.h"
#include "../includes/boolean.h"

#ifdef c_if

boolean blockInit() {
	INFO_PRINTLN("c_if block init");
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

#endif // c_if
