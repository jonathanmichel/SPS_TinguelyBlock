#include "../includes/boolean.h"
#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef b_touch

/* Parameters
1 char : [p]
p = ports [1 char]
	'1': Port 1
	'2': Port 2
	'3': Port 3
	'4': Port 4
*/
byte readBoolean(char* parametersArray) {
	char port = SensorsPorts_symbol[SensorsPorts::INPUT_2];

	INFO_PRINT("b_touch port: ");
	INFO_PRINTLN(port);

	parametersArray[0] = port;

	return 1; // parameters use 1 char
}

#endif // b_touch