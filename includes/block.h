#ifndef BLOCK_H
#define BLOCK_H

#include "Arduino.h"

/*/ Chose here wich block is described
#define c_end
#define motors_run_direction
#define motors_start_speed
#define motors_stop
#define set_status_light
#define wait_seconds
#define wait_touch
#define h_on_start
#define c_forever
#define c_else
//*/

#define h_on_start

#define PARAMETERS_MAX_SIZE 15 	// bits

boolean blockInitGlobal();

// Each of the above functions have to be implemented 
// in block specific code
boolean blockInit();
byte updateParameters(char* parametersArray);

#ifdef c_end
	#define BLOCK_ID 0x0
	#define BLOCK_SIZE 0
	#define BLOCK_TYPE "c"
#endif // c_end

#ifdef motors_run_direction
	#define BLOCK_ID 0xD
	#define BLOCK_SIZE 13
	#define BLOCK_TYPE "stack"
#endif // motors_run_direction

#ifdef motors_start_speed
	#define BLOCK_ID 0xE
	#define BLOCK_SIZE 10
	#define BLOCK_TYPE "stack"
#endif // motors_start_speed

#ifdef motors_stop
	#define BLOCK_ID 0xF
	#define BLOCK_SIZE 2
	#define BLOCK_TYPE "stack"
#endif // motors_stop

#ifdef set_status_light
	#define BLOCK_ID 0x16
	#define BLOCK_SIZE 3
	#define BLOCK_TYPE "stack"
#endif // set_status_light

#ifdef wait_seconds
	#define BLOCK_ID 0x1F
	#define BLOCK_SIZE 8
	#define BLOCK_TYPE "stack"
#endif // wait_seconds

#ifdef wait_touch
	#define BLOCK_ID 0x20
	#define BLOCK_SIZE 3
	#define BLOCK_TYPE "stack"
#endif // wait_touch

#ifdef h_on_start
	#define BLOCK_ID 0x2E
	#define BLOCK_SIZE 0
	#define BLOCK_TYPE "hat"
#endif // h_on_start

#ifdef c_forever
	#define BLOCK_ID 0x38
	#define BLOCK_SIZE 0
	#define BLOCK_TYPE "cap"
#endif // c_forever

#ifdef c_else
	#define BLOCK_ID 0x7F
	#define BLOCK_SIZE 0
	#define BLOCK_TYPE "c"
#endif // c_else

#endif