#include "../includes/block.h"

#include "../includes/debug.h"

#ifdef set_status_light

boolean blockInit() {
	INFO_PRINTLN("set_status_light block init");
	// D10 and D12 provide VCC and GND
	// D11 read value from the switch
	// Switch connection: middle pin -> D11, left and right pins -> D10 and D12
	pinMode(10, OUTPUT);
  	pinMode(11, INPUT);
	pinMode(12, OUTPUT);

	digitalWrite(10, LOW);
	digitalWrite(12, HIGH);

	return true;
}

/* Parameters
1 byte: [ccc-----]
c = color [3 bits]
	0: off
	1: green
	2: red
	3: orange
	4: green pulse
	5: red pulse
	6: orange pulse
*/
byte updateParameters(byte* parametersArray) {
	int val = digitalRead(11);

	// @todo Get color from arduino pin
	byte color = val;

	// send only 3 LSB
	parametersArray[0] = color << 5;
	// add zero padding for 5 remaining bits
	parametersArray[0] = parametersArray[0] & 0b11100000;

	INFO_PRINT("Read color ");
	INFO_PRINTLN(color);

	return 1; // one parameter (color), uses 1 byte with padding
}

#endif