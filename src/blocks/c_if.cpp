#include "../includes/block.h"
#include "../includes/debug.h"
#include "../includes/boolean.h"

#ifdef c_if

boolean blockInit() {
	INFO_PRINTLN("c_if block init");
	return true;
}

/* Parameters
1 + x chars: [sb...]
s = char representing the boolean size in hex [1 char]
b = boolean [x chars]
	binary value
*/
byte readParameters(char* parametersArray) {
	// Change boolean choice is boolean.h
	byte length = updateBoolean(parametersArray);
	return length;
}

#endif // c_if
