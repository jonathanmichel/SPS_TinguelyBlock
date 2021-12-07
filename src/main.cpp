#include <Arduino.h>

#include "../includes/block.h"
#include "../includes/com.h"
#include "../includes/debug.h"

#define TX_INTERVAL 1000	// ms, period to send frame

boolean childrenCodeFound = false;
unsigned long lastMs;

#define CHILDREN_DATA_SIZE 255 		// bytes
byte childrenData[CHILDREN_DATA_SIZE];
int childrenDataSize;

void setup() {
	debugInit();
	// Initialize software serial for UART communication
	comInit();

	INFO_PRINT("Id: 0x");
	INFO_PRINT(BLOCK_ID, HEX);
	INFO_PRINT(", size: ");
	INFO_PRINT(BLOCK_SIZE);
	INFO_PRINT(", type: ");
	INFO_PRINTLN(BLOCK_TYPE);

	if(blockInitGlobal() == false) {
		FATAL_PRINTLN("/!\\ Unable to initialize block");
		exit(0);
	}

	// Initialise timer
	lastMs = 0;	

	childrenDataSize = 0;
}

void loop() {
	// Read rx and process frame
	// 0 is returned is not frame is read from children,
	// otherwise, the children data size is returned
	int dataRead = processRx();

	// If the process function returns that it has read a complete frame from the children block
	// Save the received data to sent them next time
	if(dataRead > 0) {
		// For safety we check that data length is not bigger that our local buffer
		if(dataRead <= CHILDREN_DATA_SIZE) {
			if(copyRxData(childrenData, dataRead)) {
				childrenDataSize = dataRead;
			}
		} else  {
			ERROR_PRINTLN("ChildrenData array too small to store children code");
		}
	}
	
	// Send frame each second
	if (millis() - lastMs > TX_INTERVAL) {
		lastMs = millis();

		byte parameters[PARAMETERS_MAX_SIZE];
		byte parametersLength = updateParameters(parameters);

		// 1 byte for block id + parameters length
		byte frameLength = 1 + parametersLength + childrenDataSize;
		// Frame [SOH][frame length][... data padded ...][... children data ...][EOT]
		sendHeader();
		sendByte(frameLength);
		sendByte(BLOCK_ID);
		sendData(parameters, parametersLength);

		// Data from next blocs will be sent
		if (childrenDataSize > 0) {
			sendData(childrenData, childrenDataSize);
			INFO_PRINT("Child is ");
			INFO_PRINT(childrenDataSize);
			INFO_PRINTLN(" byte(s) long");
		} else {
			INFO_PRINTLN("Current block has no child");
		}
		childrenDataSize = 0;

		sendTail();

		DEBUG_PRINTLN("-----");

	} 
}
