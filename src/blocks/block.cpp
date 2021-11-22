#include "../includes/block.h"

#include "../includes/debug.h"

boolean blockInitGlobal() {
    if (BLOCK_SIZE > PARAMETERS_MAX_SIZE) {
        FATAL_PRINTLN("BLOCK_SIZE is bigger than PARAMETER_MAX_SIZE used for array");
        return false;
    }
    return blockInit();
}
