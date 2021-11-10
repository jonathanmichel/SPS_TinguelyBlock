#include <Arduino.h>

//

#include "../includes/block.h"
#include "../includes/com.h"

byte rxBuffer[RX_BUFFER_SIZE];  // rx buffer for code received from other blocks
int rxCtn;      // incremented to fill rxBuffer
int binaryCtn;  // decremented to count data to receive

void setup() {
	// Initialize serial communication for debug
	Serial.begin(9600);
	// Initialize software serial for UART communication
	serialInit();

	Serial.print("Id: ");
	Serial.print(BLOCK_ID);
	Serial.print(", size: ");
	Serial.print(BLOCK_SIZE);
	Serial.print(", type: ");
	Serial.println(BLOCK_TYPE);

	if(blockInitGlobal() == false) {
		Serial.println("/!\\ Unable to initialize block");
		exit(0);
	}
}

void loop() {
	char parameters[PARAMETERS_MAX_SIZE];
	byte parametersLength = updateParameters(parameters);

	// 1 byte for block id + parameters length
	byte frameLength = 1 + parametersLength;

	// Frame [SOH][frame length][... data padded ...][EOT]
	sendHeader();
	sendByte(frameLength);
	sendByte(BLOCK_ID);
	sendData(parameters, parametersLength);
	//sendChildren();
	sendTail();

	delay(1000);
}

//*/
