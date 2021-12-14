#include "../includes/block.h"

#include "../includes/debug.h"

boolean blockInitGlobal() {
    if (BLOCK_SIZE > PARAMETERS_MAX_SIZE * 8) {
        FATAL_PRINT("BLOCK_SIZE (");
        FATAL_PRINT(BLOCK_SIZE);
        FATAL_PRINT(" bits) is bigger than PARAMETER_MAX_SIZE (");
        FATAL_PRINT(PARAMETERS_MAX_SIZE)
        FATAL_PRINTLN(" bytes) used for array");
        return false;
    }
    return blockInit();
}

byte updateParameters(byte* parametersArray) {
    byte parametersBytesUsed = readParameters(parametersArray);

    // Ensure that readParameters() did not write in unalllocated memory
    if(parametersBytesUsed > PARAMETERS_MAX_SIZE) {
        FATAL_PRINT("readParameters() used too much bytes (");
        FATAL_PRINT(parametersBytesUsed);
        FATAL_PRINT(" bytes) accodring to PARAMETER_MAX_SIZE (");
        FATAL_PRINT(PARAMETERS_MAX_SIZE)
        FATAL_PRINTLN(" bytes) used for array definition"); 
    }

    // If block has a fixed size, check that readParameters() was correctly implemented
    if(BLOCK_SIZE != VARIABLE_SIZE) {
        // Calculate bytes required depending on parameters bits length
        byte parametersBytesRequired = 0;
        if(BLOCK_SIZE > 0) {
            parametersBytesRequired = (unsigned int)((BLOCK_SIZE - 1)/8) + 1;
        }
        if(parametersBytesRequired != parametersBytesUsed) {
            FATAL_PRINT("Check readParameters() implementation for block 0x");
            FATAL_PRINT(BLOCK_ID, HEX);
            FATAL_PRINT(". It does not correspond to BLOCK_SIZE definition in block.h. ");
            FATAL_PRINT(parametersBytesUsed);
            FATAL_PRINT(" byte(s) returned by readParameter() for ")
            FATAL_PRINT(BLOCK_SIZE);
            FATAL_PRINTLN(" bit(s) required for parameters according to BLOCK_SIZE.");
        }
    }

    return parametersBytesUsed;
}

