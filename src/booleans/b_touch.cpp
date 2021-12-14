#include "../includes/boolean.h"
#include "../includes/block.h"
#include "../includes/debug.h"

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