#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef motors_start_speed

boolean blockInit() {
	INFO_PRINTLN("motors_start_speed block init");
	return true;
}

/* Parameters
2 byte: [ppdsssss][ss------]
p = port [2 bits]
	00: A
	01: B
	10: C
	11: D
d = direction [1 bit]
	0: clockwise
	1: counterclockwise
s = speed [7 bits]
	0-100
*/
byte readParameters(byte* parametersArray) {
	byte port = MotorsPorts::C;
	byte direction = Direction::counterclockwise;
	byte speed = 69;

	port &= 0b11;
	direction &= 0b1;

	byte b0 = (port << 6) + (direction << 5) + (speed >> 3);
	byte b1 = (speed << 6) & 0b11000000;

	parametersArray[0] = b0;
	parametersArray[1] = b1;

	INFO_PRINT("motors_start_speed port: ");
	INFO_PRINT(port);
	INFO_PRINT(", direction: ");
	INFO_PRINT(direction);
	INFO_PRINT(", speed:");
	INFO_PRINTLN(speed);
	
	return 2; // parameters use 2 bytes
}

#endif