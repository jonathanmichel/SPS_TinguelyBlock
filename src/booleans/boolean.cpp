#include "../includes/boolean.h"
#include "../includes/block.h"
#include "../includes/debug.h"

/*  Boolean binary is formatted as followed
[ssssssss][bbbbbbbb][pppppppp][...]
s = boolean size in bytes [8 bits]
b = boolean id [8 bits]
p = boolean parameters [x byte(s)]
*/

#define BOOLEAN_HEADER 2

byte updateBoolean(char* parametersArray) {
    byte booleanSize = readBoolean(parametersArray + BOOLEAN_HEADER);

    if (BOOLEAN_SIZE != booleanSize) {
        FATAL_PRINT("Check readBoolean() implementation for boolean 0x");
        FATAL_PRINT(BOOLEAN_ID, HEX);
        FATAL_PRINT(". It does not correspond to BOOLEAN_SIZE definition in boolean.h. ");
        FATAL_PRINT(booleanSize);
        FATAL_PRINT(" char(s) returned by readBoolean() for ")
        FATAL_PRINT(BOOLEAN_SIZE);
        FATAL_PRINTLN(" char(s) required for parameters according to BOOLEAN_SIZE.");
	}

	// First byte contains binary size
	parametersArray[0] = BOOLEAN_SIZE + 2; // binary size includes one byte for BOOLEAN_ID
    parametersArray[1] = BOOLEAN_ID;    // @todo Convert boolean id in two chars with str representation

    return booleanSize + BOOLEAN_HEADER;
}
