#ifndef BLOCK_H
#define BLOCK_H

#include "Arduino.h"

/*/ Chose here which block is described
#define c_end
#define motors_run_direction
#define motors_start_speed
#define motors_stop
#define set_status_light
#define wait_seconds
#define wait_touch
#define wait_until
#define h_on_start
#define c_forever
#define c_repeat
#define c_repeat_until
#define c_if
#define c_else
#define set_trap_door
#define start_crawler
//*/

#define set_trap_door

#define PARAMETERS_MAX_SIZE 16 	// bytes

// @todo Remove, no more required but still used in code for deprecated blocks
enum MotorsPorts { A = 0, B, C, D };
enum SensorsPorts { INPUT_1 = 0, INPUT_2, INPUT_3, INPUT_4 };
enum Direction { clockwise = 0, counterclockwise };
enum State { pressed = 0, released };
enum Operator { equal = 0, greater, less };
enum MotorsUnit { rotations = 0, degrees, seconds };
enum DistanceUnit { cm = 0, inches };
enum Sign { positive = 0, negative };

boolean blockInitGlobal();
byte updateParameters(char* parametersArray);

// Each of the above functions have to be implemented 
// in block specific code
boolean blockInit();
byte readParameters(char* parametersArray);

// To define a new block:
// BLOCK_ID : 2 chars representing the block id value in hexadecimal
// BLOCK_SIZE : number of chars required to send parameters, 
//				use VARIABLE_SIZE to indicate variable length 
//				(for binary arguments like boolean)
// BLOCK_TYPE : block type (c, stack, hat, end)

#define VARIABLE_SIZE -1

#ifdef c_end
	#define BLOCK_ID "00"
	#define BLOCK_SIZE 0
	#define BLOCK_TYPE "c"
#endif // c_end

#ifdef motors_run_direction
	#define BLOCK_ID "0D"
	#define BLOCK_SIZE 6
	#define BLOCK_TYPE "stack"
#endif // motors_run_direction

#ifdef motors_start_speed
	#define BLOCK_ID "0E"
	#define BLOCK_SIZE 5
	#define BLOCK_TYPE "stack"
#endif // motors_start_speed

#ifdef motors_stop
	#define BLOCK_ID "0F"
	#define BLOCK_SIZE 1
	#define BLOCK_TYPE "stack"
#endif // motors_stop

#ifdef set_status_light
	#define BLOCK_ID "16"
	#define BLOCK_SIZE 1
	#define BLOCK_TYPE "stack"
#endif // set_status_light

#ifdef wait_seconds
	#define BLOCK_ID "1F"
	#define BLOCK_SIZE 2
	#define BLOCK_TYPE "stack"
#endif // wait_seconds

#ifdef wait_touch
	#define BLOCK_ID "20"
	#define BLOCK_SIZE 2
	#define BLOCK_TYPE "stack"
#endif // wait_touch

#ifdef wait_until
	#define BLOCK_ID "21"
	#define BLOCK_SIZE VARIABLE_SIZE
	#define BLOCK_TYPE "stack"
#endif // wait_until

#ifdef h_on_start
	#define BLOCK_ID "2E"
	#define BLOCK_SIZE 0
	#define BLOCK_TYPE "hat"
#endif // h_on_start

#ifdef c_forever
	#define BLOCK_ID "38"
	#define BLOCK_SIZE 0
	#define BLOCK_TYPE "c"
#endif // c_forever

#ifdef c_if
	#define BLOCK_ID "39"
	#define BLOCK_SIZE VARIABLE_SIZE
	#define BLOCK_TYPE "c"
#endif // c_if

#ifdef c_repeat
	#define BLOCK_ID "3B"
	#define BLOCK_SIZE 2
	#define BLOCK_TYPE "c"
#endif // c_repeat

#ifdef c_repeat_until
	#define BLOCK_ID "3C"
	#define BLOCK_SIZE VARIABLE_SIZE
	#define BLOCK_TYPE "c"
#endif // c_repeat_until

#ifdef set_trap_door
	#define BLOCK_ID "64"
	#define BLOCK_SIZE 1
	#define BLOCK_TYPE "stack"
#endif // c_else

#ifdef start_crawler
	#define BLOCK_ID "65"
	#define BLOCK_SIZE 1
	#define BLOCK_TYPE "stack"
#endif // c_else


#ifdef c_else
	#define BLOCK_ID "7F"
	#define BLOCK_SIZE 0
	#define BLOCK_TYPE "c"
#endif // c_else

#endif