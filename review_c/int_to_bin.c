#include <stdio.h>
#include <stdint.h>
#include "uart.h"

void intToBin (uint8_t target, char* buffer) {
    /* Your code goes here */
    int i;
    //target is the integer value, like 5, 5 is stored as binary automatically
    //target = 1101_0011
    //target >> 1 
    //target = 0110_1001
    //leftmost bit: 0000_0001
    //target >>7
    for (i = 0; i <= 7; i++)
    {
        uint8_t temp;
        char write;
        temp = target >> (7-i);
        temp = temp & 0x1; //0000_001b clear all the other things in target
        
        if (temp == 1){
            write = '1';
        } else {
            write = '0';
        }
        buffer[i] = write;
    }
    buffer[8] = '\0';
    
} 

int main () {
    uart_init(UART2);
    uint8_t value;
    int ret;
    char binaryStr[9];

    // Begin main program loop
    while (value != 10) {
        value = uart_read(UART2, BLOCKING, &ret);
        intToBin(value, binaryStr);
        uart_write_str(UART2, binaryStr);
    }

    return 0;
}
