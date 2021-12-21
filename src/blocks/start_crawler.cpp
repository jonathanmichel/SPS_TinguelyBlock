#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef start_crawler

boolean blockInit() {
	// D10 and D12 provide VCC and GND
	// D11 read value from the switch
	// Switch connection: middle pin -> D11, left and right pins -> D10 and D12
	pinMode(10, OUTPUT);
  	pinMode(11, INPUT);
	pinMode(12, OUTPUT);

	digitalWrite(10, LOW);
	digitalWrite(12, HIGH);

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
	byte direction = Direction::clockwise;

    direction = digitalRead(11);

	parametersArray[0] = (direction & 0b1) << 7;

	INFO_PRINT("set_crawler direction: ");
	INFO_PRINTLN(direction);

	return 1; // parameters use 1 byte
}

#endif