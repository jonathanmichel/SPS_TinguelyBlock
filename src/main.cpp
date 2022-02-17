#include <Arduino.h>

#include "../includes/block.h"
#include "../includes/com.h"
#include "../includes/debug.h"

#define TX_INTERVAL 200	// ms, period to send frame

unsigned long lastMs;

#define CHILDREN_DATA_SIZE 255 		// bytes
#define RESET_CHILDREN_CNT 5
char childrenData[CHILDREN_DATA_SIZE];
byte childrenDataSize;
byte resetChildren = 0;

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
	int frameSize = processCodeRx();
	//processDebugSerial();

	// If the process function returns that it has read a complete frame (start and end symbol not included)
	// from the children block, save the received data to sent them next time
	if(frameSize > 0) {
		// For safety we check that data length is not bigger that our local buffer
		if(frameSize <= CHILDREN_DATA_SIZE) {
			copyFrameData(childrenData, frameSize);
			childrenDataSize = frameSize;
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
		addChars(parameters, parametersLength);

		// Data from the next blocks will be sent
		if (childrenDataSize > 0) {
			addChar('|');
			addChars(childrenData, childrenDataSize);
			INFO_PRINT("Child is ");
			INFO_PRINT(childrenDataSize);
			INFO_PRINTLN(" char(s) long");
			// Keep children data for the next RESET_CHILDREN_CNT frames sent before removing it completely. It allows to minimise synchronisation issues between blocks that causes fails in discovering childrens ... not ideal ... @todo Improve
			resetChildren++;
			if(resetChildren == RESET_CHILDREN_CNT) {
				childrenDataSize = 0;
				resetChildren = 0;
			}
		} else {
			INFO_PRINTLN("Current block has no child");
		}
		//*/

		addTail();

		// Send frame over serial
		sendFrame();
	} 
}
