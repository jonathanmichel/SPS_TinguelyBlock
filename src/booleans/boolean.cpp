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

byte updateBoolean(byte* parametersArray) {
    byte booleanSize = readBoolean(parametersArray + BOOLEAN_HEADER);

    byte booleanBytesRequired = 0;
    if(BOOLEAN_SIZE > 0) {
        booleanBytesRequired = (unsigned int)((BOOLEAN_SIZE - 1)/8) + 1;
    }

    if (booleanBytesRequired != booleanSize) {
        FATAL_PRINT("Check readBoolean() implementation for boolean 0x");
        FATAL_PRINT(BOOLEAN_ID, HEX);
        FATAL_PRINT(". It does not correspond to BOOLEAN_SIZE definition in boolean.h. ");
        FATAL_PRINT(booleanSize);
        FATAL_PRINT(" byte(s) returned by readBoolean() for ")
        FATAL_PRINT(BOOLEAN_SIZE);
        FATAL_PRINTLN(" bit(s) required for parameters according to BOOLEAN_SIZE.");
	}

	// First byte contains binary size
	parametersArray[0] = booleanBytesRequired + 1; // binary size includes one byte for BOOLEAN_ID
    parametersArray[1] = BOOLEAN_ID;

    return booleanSize + BOOLEAN_HEADER;
}
