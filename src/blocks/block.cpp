#include "../includes/block.h"
#include "../includes/com.h"

void sendId() {
    int i = 0;
    char id[BLOCK_ID_SIZE] = BLOCK_ID_BIN;
    for (i = 0; i < BLOCK_ID_SIZE; i++) {
        sendByte(id[i]);
    }
}
