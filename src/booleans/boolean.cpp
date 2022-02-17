#include "../includes/boolean.h"
#include "../includes/block.h"
#include "../includes/debug.h"

/*  Boolean binary is formatted as followed
[sii...]
s = boolean size in hexadecimal [1 char]
ii = boolean id [2 chars]
p = boolean parameters [x char(s)]
*/

// Boolean header size: 1 char for the boolean size and two for its ID
#define BOOLEAN_HEADER 3

byte updateBoolean(char* parametersArray) {
    byte booleanSize = readBoolean(parametersArray + BOOLEAN_HEADER);

    if (BOOLEAN_SIZE != booleanSize) {
        FATAL_PRINT("Check readBoolean() implementation for boolean 0x");
        FATAL_PRINT(BOOLEAN_ID);
        FATAL_PRINT(". It does not correspond to BOOLEAN_SIZE definition in boolean.h. ");
        FATAL_PRINT(booleanSize);
        FATAL_PRINT(" char(s) returned by readBoolean() for ")
        FATAL_PRINT(BOOLEAN_SIZE);
        FATAL_PRINTLN(" char(s) required for parameters according to BOOLEAN_SIZE.");
	}

    if (booleanSize > 0xF) {
        FATAL_PRINTLN("Boolean is to big for current implementation. Maximum size allowed is 15 chars.");
    }

    sprintf(parametersArray, "\%X", booleanSize);   // Convert booleanSize in hex and fill parametersArray[0] with it 

    char booleanId[] = BOOLEAN_ID;		// BOOLEAN_ID has to be 2 chars in boolean.h !
    parametersArray[1] = booleanId[0];
    parametersArray[2] = booleanId[1];

    return booleanSize + BOOLEAN_HEADER;
}
