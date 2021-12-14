#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

// Comment to disable debug logs
// #define LEVEL_DEBUG

#ifdef LEVEL_DEBUG

#define DEBUG_PRINT(...) Serial.print("[DEBUG]"); Serial.print(__VA_ARGS__); 
#define DEBUG_PRINTLN(...) Serial.print("[DEBUG]"); Serial.println(__VA_ARGS__); 

#else

#define DEBUG_PRINT(...) 
#define DEBUG_PRINTLN(...) 

#endif

// For now, we assume that info,
// warning, error and fatal are always enabled

#define INFO_PRINT(...) Serial.print("[INFO]"); Serial.print(__VA_ARGS__); 
#define INFO_PRINTLN(...) Serial.print("[INFO]"); Serial.println(__VA_ARGS__); 

#define WARNING_PRINT(...) Serial.print("[WARNING]"); Serial.print(__VA_ARGS__); 
#define WARNING_PRINTLN(...) Serial.print("[WARNING]"); Serial.println(__VA_ARGS__); 

#define ERROR_PRINT(...) Serial.print("[ERROR]"); Serial.print(__VA_ARGS__); 
#define ERROR_PRINTLN(...) Serial.print("[ERROR]"); Serial.println(__VA_ARGS__); 

// ! FATAL_PRINT does not exit code. This allows to print values before calling FATAL_PRINTLN
#define FATAL_PRINT(...) Serial.print("[FATAL]"); Serial.print(__VA_ARGS__); 
#define FATAL_PRINTLN(...) Serial.print("[FATAL]"); Serial.println(__VA_ARGS__); Serial.println("[FATAL] Exit code"); Serial.flush(); exit(0)

void debugInit();

#endif // DEBUG_H