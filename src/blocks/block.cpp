#include "../includes/block.h"

#include "../includes/debug.h"

boolean blockInitGlobal() {
    if (BLOCK_SIZE > PARAMETERS_MAX_SIZE) {
        FATAL_PRINTLN("BLOCK_SIZE is bigger than PARAMETER_MAX_SIZE used for array");
        return false;
    }
    return blockInit();
}

byte updateParameters(byte* parametersArray) {
    byte parameterSize = readParameters(parametersArray);

    byte parametersBytesRequired = 0;
    if(BLOCK_SIZE > 0) {
        parametersBytesRequired = (unsigned int)((BLOCK_SIZE - 1)/8) + 1;
    }

    if(parametersBytesRequired != parameterSize) {
        FATAL_PRINT("Check readParameters() implementation for block 0x");
        FATAL_PRINT(BLOCK_ID, HEX);
        FATAL_PRINT(". It does not correspond to BLOCK_SIZE definition in block.h. ");
        FATAL_PRINT(parameterSize);
        FATAL_PRINT(" byte(s) returned by readParameter() for ")
        FATAL_PRINT(BLOCK_SIZE);
        FATAL_PRINTLN(" bit(s) required for parameters according to BLOCK_SIZE.");
    }

    return parameterSize;
}

