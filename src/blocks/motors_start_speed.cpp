#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef motors_start_speed

boolean blockInit() {
	INFO_PRINTLN("motors_start_speed block init");
	return true;
}

/* Parameters
2 byte: [ppdvvvvv][vvv-----]
p = port [2 bits]
	00: A
	01: B
	10: C
	11: D
d = direction [1 bit]
	0: clockwise
	1: counterclockwise
v = value [8 bits]
	0-255
*/
byte readParameters(byte* parametersArray) {
	byte port = MotorsPorts::C;
	byte direction = Direction::counterclockwise;
	byte value = 69;

	port &= 0b11;
	direction &= 0b1;

	byte b0 = (port << 6) + (direction << 5) + (value >> 3);
	byte b1 = (value << 5) & 0b11100000;

	parametersArray[0] = b0;
	parametersArray[1] = b1;

	INFO_PRINT("motors_start_speed port: ");
	INFO_PRINT(port);
	INFO_PRINT(", direction: ");
	INFO_PRINT(direction);
	INFO_PRINT(", value:");
	INFO_PRINTLN(value);
	
	return 2; // parameters use 2 bytes
}

#endif