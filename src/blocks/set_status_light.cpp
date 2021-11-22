#include "../includes/block.h"

#ifdef set_status_light

boolean blockInit() {
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
	// @todo Get color from arduino pin
	byte color = 5;

	// send only 3 LSB
	parametersArray[0] = color << 5;
	// add zero padding for 5 remaining bits
	parametersArray[0] = parametersArray[0] & 0b11100000;


	return 1; // one parameter (color), uses 1 byte with padding
}

#endif