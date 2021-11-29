#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef wait_touch

boolean blockInit() {
	INFO_PRINTLN("wait_touch block init");
	return true;
}

/* Parameters
1 byte: [pps-----]
p = ports [2 bits]
	00: 1
	01: 2
	10: 3
	11: 4
s = state [1 bit]
	0: pressed
	1: released
*/
byte readParameters(byte* parametersArray) {
	byte port = SensorsPorts::INPUT_4;
	byte state = State::released;

	port &= 0b11;
	state &= 0b1;

	parametersArray[0] = (port << 6) + (state << 5);

	INFO_PRINT("wait_touch port: ");
	INFO_PRINT(port);
	INFO_PRINT(", port: ");
	INFO_PRINT(port);
	INFO_PRINT(", state:");
	INFO_PRINTLN(state);

	return 1; // parameters use 1 byte
}

#endif
