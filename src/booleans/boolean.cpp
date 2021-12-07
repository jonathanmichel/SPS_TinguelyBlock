#include "../includes/boolean.h"
#include "../includes/block.h"
#include "../includes/debug.h"

// Boolean binary is formatted as followed
// [ssssssss][bbbbbbbb][pppppppp][...]
// s: boolean size in bytes [8 bits]
// b: boolean id [8 bits]
// p: boolean parameters [x byte(s)]
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

#ifdef b_touch

/* Parameters
1 byte: [pp------]
p = ports [2 bits]
	00: 1
	01: 2
	10: 3
	11: 4
*/
byte readBoolean(byte* parametersArray) {
	byte port = SensorsPorts::INPUT_2;

	port &= 0b11;

	parametersArray[0] = (port << 6);

	INFO_PRINT("b_touch port: ");
	INFO_PRINTLN(port);

	return 1; // parameters use 1 byte
}

#endif // b_touch

#ifdef b_distance

/* Parameters
2 bytes: [ppoovvvv][vvvvu---]
p = ports [2 bits]
	00: 1
	01: 2
	10: 3
	11: 4
o = operator [2 bits]
    00: equal
    01: greater
    10: less
    11: <not supported>
v = value [8 bits]
u = unit [1 bit]
    0: cm
    1: inches
*/
byte readBoolean(byte* parametersArray) {
	byte port = SensorsPorts::INPUT_4;
    byte oper = Operator::less;
    byte value = 75;
    byte unit = DistanceUnit::inches;

	byte b0 = (port << 6) + (oper << 4) + (value >> 4);
    byte b1 = (value << 4) + (unit << 3);

    parametersArray[0] = b0;
    parametersArray[1] = b1;

	INFO_PRINT("b_distance port: ");
	INFO_PRINT(port);
    INFO_PRINT(", operator: ");
    INFO_PRINT(oper);
    INFO_PRINT(", value: ");
    INFO_PRINT(value);
    INFO_PRINT(", unit: ");
    INFO_PRINTLN(unit);

    return 2; // parameters use 2 bytes
}

#endif // b_distance