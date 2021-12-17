#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef start_crawler

boolean blockInit() {
	INFO_PRINTLN("set_crawler block init");
	return true;
}

/* Parameters
1 byte: [s-------]
s = state [1 bits]
	0: close
	1: open
*/
byte readParameters(byte* parametersArray) {
	byte direction = TrapDoorState::open;

	parametersArray[0] = (direction & 0b1) << 7;

	INFO_PRINT("set_crawler direction: ");
	INFO_PRINTLN(direction);

	return 1; // parameters use 1 byte
}

#endif