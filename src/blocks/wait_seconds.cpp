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
	0-255
*/
byte readParameters(byte* parametersArray) {
	int val = analogRead(A0);  	// Read analog value
	// 10 bits ADC - Max value is 1023, NOT LINEAR !
	// limit for seconds value from 1 to 10
	int limit[] = { 732, 918, 977, 986, 994, 998, 1003, 1005, 1008, 1017 };

	int currentLimit;
	for (currentLimit = 0; currentLimit < 10; currentLimit ++) {
		if (val >= limit[currentLimit] ) {
			continue;
		} else {
			break;
		}
	}

	Serial.print("Value is ");
  	Serial.println(val);

	Serial.print("Delay is ");
  	Serial.print(currentLimit);
	Serial.println(" second(s)");

	// send 8 bytes
	parametersArray[0] = currentLimit;
	// no padding required
	
	return 1; // parameters use 1 byte
}

#endif