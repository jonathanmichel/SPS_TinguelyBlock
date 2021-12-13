#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <Arduino.h>

/*/ Chose here wich boolean has to be used in conditional blocks
#define b_touch
#define b_distance
//*/

#define b_distance

#ifdef b_touch
	#define BOOLEAN_ID 0x43
	#define BOOLEAN_SIZE 2
#endif // b_touch

#ifdef b_distance
	#define BOOLEAN_ID 0x41
	#define BOOLEAN_SIZE 14
#endif // b_distance


byte updateBoolean(byte* parametersArray);

// For each boolean block, the above functin has to  
// be implemented
byte readBoolean(byte* parametersArray);

#endif // BOOLEAN_H