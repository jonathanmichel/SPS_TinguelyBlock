#include "../includes/block.h"

#include "../includes/debug.h"

#ifdef wait_seconds

boolean blockInit() {
	INFO_PRINTLN("wait_seconds block init");
	// D10 and D12 provide VCC and GND
	// D11 read value from the switch
	// Switch connection: middle pin -> D11, left and right pins -> D10 and D12
	pinMode(10, OUTPUT);
  	pinMode(A0, INPUT);
	pinMode(12, OUTPUT);

	digitalWrite(10, LOW);

	digitalWrite(10, LOW);
	digitalWrite(12, HIGH);

	return true;
}

/* Parameters
1 byte: [ssssssss]
s = seconds [8 bits]
	"0
	…
	255"
*/
byte readParameters(byte* parametersArray) {
	int val = analogRead(A0);  	// Read analog value
	// 10 bits ADC - Max value is 1023
	// shit 5 times (/32) to have a range between 0 and 32 seconds
	byte seconds = val >> 5;

	Serial.print("Delay is ");
  	Serial.print(seconds);
	Serial.println(" second(s)");

	// send 8 bytes
	parametersArray[0] = seconds;
	// no padding required
	
	return 1; // one parameter (color), uses 1 byte with padding
}

#endif