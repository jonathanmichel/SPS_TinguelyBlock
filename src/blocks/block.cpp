#include "../includes/block.h"

boolean blockInitGlobal() {
    if (BLOCK_SIZE > PARAMETERS_MAX_SIZE) {
        Serial.println("BLOCK_SIZE is bigger than PARAMETER_MAX_SIZE used for array");
        return false;
    }
    return blockInit();
}
