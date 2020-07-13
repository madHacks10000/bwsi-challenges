#include "uart.h"

int main() {
    // Initialize serial
    uart_init(UART2);
    
    //read a big endian short
    
    i = 0;
    data = [];
    int ret;
    
    data = uart_read(UART2, BLOCKING, &ret);
    size = strlen(data)
    //break into frames called frame
        
        for ( int i = 0; i < 4; ++i )
    {
        value << 8 * i;  // shift everything over one byte
        value += a[ i ]; // add the next byte to the LSByte
    }
    
    while (frame != '\n'){
        for i in range(size) {
            i++;
            //read 1 byte
            //send chunk to flash
            data[i] = uart_read(UART2, BLOCKING, &ret);
        }
    }
    //memset(data, 0, counter)
    //clear the data array at some point
  // Send the full string back over serial
    //uart_write_str(UART2, flag);
    return 0;
}