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
1 char: [s]
s = state [1 char]
	c: close
	o: open
*/
byte readParameters(char* parametersArray) {
	byte button = digitalRead(5);

	char state = 'c';	// close
	if(button) {	// open
		state = 'o';
	}

	INFO_PRINT("set_trap_door button: ");
	INFO_PRINTLN(button);

	parametersArray[0] = state;

	return 1; // parameters use 1 char
}

#endif