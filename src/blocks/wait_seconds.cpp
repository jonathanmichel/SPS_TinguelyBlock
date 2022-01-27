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
2 chars: [ss]
s = seconds [2 chars]
	00-99
*/
byte readParameters(char* parametersArray) {
	int val = analogRead(A0);  	// Read analog value
	// 10 bits ADC - Max value is 1023, NOT LINEAR !
	// limit for seconds value from 1 to 10
	int limit[] = { 732, 918, 977, 986, 994, 998, 1003, 1005, 1008, 1017 };

	int limitCtn;
	for (limitCtn = 0; limitCtn < 10; limitCtn ++) {
		if (val >= limit[limitCtn] ) {
			continue;
		} else {
			break;
		}
	}

	Serial.print("Value is ");
  	Serial.println(val);

	Serial.print("Delay is ");
  	Serial.print(limitCtn);
	Serial.println(" second(s)");

	// Convert limitCtn (seconds) has a 2 chars value representation 
    sprintf(parametersArray, "\%02u", limitCtn);
	
	return 2; // parameters use 2 chars
}

#endif