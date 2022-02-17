#include "../includes/boolean.h"
#include "../includes/block.h"
#include "../includes/debug.h"

#ifdef b_distance

/* Parameters
// @ todo - Deprecated implementation, format parameters to match protocol
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
s = sign [1 bit]
    0: positiv
    1: negativ
v = value [8 bits]
u = unit [1 bit]
    0: cm
    1: inches
*/
byte readBoolean(char* parametersArray) {
	FATAL_PRINTLN("Deprecated implementation, please update it !");
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