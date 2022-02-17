#include "../includes/block.h"
#include "../includes/boolean.h"
#include "../includes/debug.h"

#ifdef c_repeat_until

boolean blockInit() {
	INFO_PRINTLN("c_repeat_until block init");
	return true;
}

/* Parameters
1 + x chars: [sb...]
s = char representing the boolean size in hex [1 char]
b = boolean [x chars]
	binary value
*/
byte readParameters(char* parametersArray) {
	// Change boolean chose is boolean.h
	byte length = updateBoolean(parametersArray);
	return length;
}

#endif
