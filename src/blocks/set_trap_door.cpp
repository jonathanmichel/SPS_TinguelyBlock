#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef set_trap_door

boolean blockInit() {
	// D4 and D6 provide VCC and GND
	// D5 read value from the switch
	// Switch connection: middle pin -> D5, left and right pins -> D4 and D6
	pinMode(4, OUTPUT);
  	pinMode(5, INPUT);
	pinMode(6, OUTPUT);

	digitalWrite(4, LOW);
	digitalWrite(6, HIGH);

	INFO_PRINTLN("set_trap_door block init");
	return true;
}

/* Parameters
1 byte: [s-------]
s = state [1 bits]
	0: close
	1: open
*/
byte readParameters(byte* parametersArray) {
	byte state = TrapDoorState::open;

	state = digitalRead(5);

	parametersArray[0] = (state & 0b1) << 7;

	INFO_PRINT("set_trap_door state: ");
	INFO_PRINTLN(state);

	return 1; // parameters use 1 byte
}

#endif