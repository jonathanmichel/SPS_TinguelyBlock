#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef motors_run_direction

boolean blockInit() {
	INFO_PRINTLN("motors_run_direction block init");
	return true;
}

/* Parameters
2 byte: [ppduuvvv][vvvvv---]
p = port [2 bits]
	00: A
	01: B
	10: C
	11: D
d = direction [1 bit]
	0: clockwise
	1: counterclockwise
u = unit [2 bits]
	00: rotations
	01: degrees
	10: seconds
	11: <not supported>
v = value [8 bits]
	0-255
*/
byte readParameters(byte* parametersArray) {
	byte port = MotorsPorts::A;
	byte direction = Direction::clockwise;
	byte unit = MotorsUnit::degrees;
	byte value = 135;

	port &= 0b11;
	direction &= 0b1;
	unit &= 0b11;

	byte b0 = (port << 6) + (direction << 5) + (unit << 3) + (value >> 5);
	byte b1 = (value << 3) & 0b11111000;

	parametersArray[0] = b0;
	parametersArray[1] = b1;

	INFO_PRINT("motors_run_direction port: ");
	INFO_PRINT(port);
	INFO_PRINT(", direction: ");
	INFO_PRINT(direction);
	INFO_PRINT(", unit: ");
	INFO_PRINT(unit);
	INFO_PRINT(", value:");
	INFO_PRINTLN(value);

	return 2; // parameters use 2 bytes
}
#endif