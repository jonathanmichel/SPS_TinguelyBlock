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
// @ todo - Deprecated implementation, format parameters to match protocol
1 byte: [ccc-----]
c = color [3 bits]
	000: off
	001: green
	010: red
	011: orange
	100: green pulse
	101: red pulse
	110: orange pulse
	111: <not supported>
*/
byte readParameters(byte* parametersArray) {
	FATAL_PRINTLN("Deprecated implementation, please update it !");
	int val = digitalRead(11);

	byte color = val;

	// send only 3 LSB
	parametersArray[0] = color << 5;
	// add zero padding for 5 remaining bits
	parametersArray[0] = parametersArray[0] & 0b11100000;

	INFO_PRINT("Read color ");
	INFO_PRINTLN(color);

	return 1; // parameters use 1 byte
}

#endif