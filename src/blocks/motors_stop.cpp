#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef motors_stop

boolean blockInit() {
	INFO_PRINTLN("motors_stop block init");
	return true;
}

/* Parameters
// @ todo - Deprecated implementation, format parameters to match protocol
1 byte: [pp------]
p = port [2 bits]
	00: A
	01: B
	10: C
	11: D
*/
byte readParameters(byte* parametersArray) {
	FATAL_PRINTLN("Deprecated implementation, please update it !");
	byte port = MotorsPorts::A;

	parametersArray[0] = (port & 0b11) << 6;

	INFO_PRINT("motors_stop port: ");
	INFO_PRINTLN(port);

	return 1; // parameters use 1 byte
}

#endif