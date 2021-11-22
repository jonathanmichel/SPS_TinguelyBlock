#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

// Comment to disable debug logs
// #define LEVEL_DEBUG

#ifdef LEVEL_DEBUG

#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__); 
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__); 

#else

#define DEBUG_PRINT(...) 
#define DEBUG_PRINTLN(...) 

#endif

// For now, we assume that info,
// warning, error and fatal are always enabled

#define INFO_PRINT(...) Serial.print(__VA_ARGS__); 
#define INFO_PRINTLN(...) Serial.println(__VA_ARGS__); 

#define WARNING_PRINT(...) Serial.print(__VA_ARGS__); 
#define WARNING_PRINTLN(...) Serial.println(__VA_ARGS__); 

#define ERROR_PRINT(...) Serial.print(__VA_ARGS__); 
#define ERROR_PRINTLN(...) Serial.println(__VA_ARGS__); 

#define FATAL_PRINT(...) Serial.print(__VA_ARGS__); Serial.flush(); exit(0);
#define FATAL_PRINTLN(...) Serial.println(__VA_ARGS__); Serial.flush(); exit(0)

void debugInit();

#endif // DEBUG_H