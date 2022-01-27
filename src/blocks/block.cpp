#include "../includes/block.h"

#include "../includes/debug.h"

boolean blockInitGlobal() {
    if (BLOCK_SIZE > PARAMETERS_MAX_SIZE * 8) {
        FATAL_PRINT("BLOCK_SIZE (");
        FATAL_PRINT(BLOCK_SIZE);
        FATAL_PRINT(" chars) is bigger than PARAMETER_MAX_SIZE (");
        FATAL_PRINT(PARAMETERS_MAX_SIZE)
        FATAL_PRINTLN(" chars) used for array");
        return false;
    }
    return blockInit();
}

byte updateParameters(char* parametersArray) {
    byte parametersCharsUsed = readParameters(parametersArray);

    // Ensure that readParameters() did not write in unalllocated memory
    if(parametersCharsUsed > PARAMETERS_MAX_SIZE) {
        FATAL_PRINT("readParameters() used too much memory (");
        FATAL_PRINT(parametersCharsUsed);
        FATAL_PRINT(" chars) according to PARAMETER_MAX_SIZE (");
        FATAL_PRINT(PARAMETERS_MAX_SIZE)
        FATAL_PRINTLN(" chars) used for array definition"); 
    }

    // If block has a fixed size, check that readParameters() was correctly implemented
    if(BLOCK_SIZE != VARIABLE_SIZE) {
        if(BLOCK_SIZE != parametersCharsUsed) {
            FATAL_PRINT("Check readParameters() implementation for block 0x");
            FATAL_PRINT(BLOCK_ID);
            FATAL_PRINT(". It does not correspond to BLOCK_SIZE definition in block.h. ");
            FATAL_PRINT(parametersCharsUsed);
            FATAL_PRINT(" char(s) returned by readParameter() for ")
            FATAL_PRINT(BLOCK_SIZE);
            FATAL_PRINTLN(" char(s) required for parameters according to BLOCK_SIZE.");
        }
    }

    return parametersCharsUsed;
}

