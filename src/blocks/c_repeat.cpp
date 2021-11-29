#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef c_repeat

boolean blockInit() {
	INFO_PRINTLN("c_repeat block init");
	return true;
}

/* Parameters
1 byte: [tttttttt]
t = times [8 bits]
	0-255
*/
byte readParameters(byte* parametersArray) {
	int times = 8;

	Serial.print("Repeat ");
  	Serial.print(times);
	Serial.println(" time(s)");

	// send 8 bytes
	parametersArray[0] = times;
	// no padding required
	
	return 1; // parameters use 1 byte
}

#endif
