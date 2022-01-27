#include <Arduino.h>

#include "../includes/block.h"
#include "../includes/com.h"
#include "../includes/debug.h"

#define TX_INTERVAL 1000	// ms, period to send frame

unsigned long lastMs;

#define CHILDREN_DATA_SIZE 255 		// bytes
char childrenData[CHILDREN_DATA_SIZE];
byte childrenDataSize;

void setup() {
	debugInit();
	// Initialize software serial for UART communication
	comInit();

	INFO_PRINT("Id: 0x");
	INFO_PRINT(BLOCK_ID);
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
	int codeDataRead = processCodeRx();
	//processDebugSerial();

	// If the process function returns that it has read a complete frame (start and end symbol + data)
	// from the children block, save the received data to sent them next time
	if(codeDataRead > 2) {
		// We remove the START_SYMBOL and the END_SYMBOL from the data stored
		codeDataRead = codeDataRead - 2;
		// For safety we check that data length is not bigger that our local buffer
		if(codeDataRead <= CHILDREN_DATA_SIZE) {
			if(copyRxData(childrenData, codeDataRead)) {
				childrenDataSize = codeDataRead; // start and end symbol are removed
			}
		} else  {
			ERROR_PRINTLN("ChildrenData array too small to store children code");
		}
	}
	
	// Send frame each second
	if (millis() - lastMs > TX_INTERVAL) {
		lastMs = millis();

		char parameters[PARAMETERS_MAX_SIZE];
		byte parametersLength = updateParameters(parameters);

		// Create frame: 
		// 'START_SYMBOL'[block id][... parameters ...]'|'[... children data ...]'END_SYMBOL'
		resetFrame();
		addHeader();
		char blockId[] = BLOCK_ID;		// BLOCK_ID has to be 2 chars in block.h !
		addChar(blockId[0]);
		addChar(blockId[1]);
		addString(parameters, parametersLength);

		/*/ Data from next blocs will be sent
		if (childrenDataSize > 0) {
			addChar('|');
			addData(childrenData, childrenDataSize);
			INFO_PRINT("Child is ");
			INFO_PRINT(childrenDataSize);
			INFO_PRINTLN(" byte(s) long");
		} else {
			INFO_PRINTLN("Current block has no child");
		}
		childrenDataSize = 0;
		//*/

		addTail();

		// Send frame over serial
		sendFrame();
	} 
}
