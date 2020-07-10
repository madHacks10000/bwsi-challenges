
// Hardware Imports
#include "inc/hw_memmap.h" // Peripheral Base Addresses
#include "inc/lm3s6965.h" // Peripheral Bit Masks and Registers

// Component Header
#include "uart.h"

// UART Channels - You can use these names, but don't uncomment them!
// #define UART0 0
// #define UART1 1
// #define UART2 2

// Reading modes - You can use these names, but don't uncomment them!
// #define NONBLOCKING 0
// #define BLOCKING 1

void uart_init(uint8_t uart)
{
  // Implement me!!
    //page 451 is helpful
    //1st: disable warten bit in CTL register (set bit to 0, furthest back one, page 453)
    //2nd: write integer portion of the BRD register
    //3rd: write fractional portion of the BRD register
    //4th:write desired serial parameters to CRH register
    //5th: enable UART warten bit
    // #define UART2_CTL_R
    // #define UART2_IBRD_R
    // #define UART2_FBRD_R
    // #define UART2_LCRH_R
    
    UART2_CTL_R &= ~(0x00000001); //disables UART by setting the last bit to 0, inverts 
    
    //IBRD is address of the register but we want the bit
    UART2_IBRD_R &= ~(UART_IBRD_DIVINT_M); //setting first half of the baud, flipping all the bits, the integer part
    UART2_IBRD_R |= 0x0a; //adding the bits we want which is 0x0a
        
    UART2_FBRD_R &= ~(UART_FBRD_DIVFRAC_M); //set fractional baudrate part
    UART2_FBRD_R |= 0x36; //sets second half of the baud rate to 0x36 (directions)
    //cant just set equal because some bits are reserved, or prevents what you dont want change from being changed
    
    UART2_LCRH_R &= ~(UART_LCRH_WLEN_M); //set 8 bit word
    UART2_LCRH_R |= UART_LCRH_WLEN_8; //same as UART2_LCRH_R |= 0x00000060;
    
     //8 bit using or will not let the 0 bits be effective
        
    UART2_CTL_R |= UART_LCRH_WLEN_8; 
    UART2_CTL_R |= UART_CTL_UARTEN; //turn UART back on
    
}

uint8_t uart_read(uint8_t uart, int blocking, int *read)
{
  // Implement me!!
    //page 444 read
    //if blocking=1 then we do a blocking read, 1 is true so we do if (blocking)
    if (blocking){
        while (UART2_FR_R & UART_FR_RXFE); //wait for byte (FIFO is empty)
        *read = 1; //use a pointer, if we just did the var, the var in the memory wouldn't be updated, sets actual value to 1
        return UART2_DR_R & UART_DR_DATA_M; //return data that is in the register (the RX value)
    } else {
        if (UART2_FR_R & UART_FR_RXFF) { //checks if data is available
            *read = 1;
            return UART2_DR_R & UART_DR_DATA_M; //return RX value
        } else {
            *read = 0;
            return 0;
        }
    }
}

void uart_write(uint8_t uart, uint32_t data)
{
  // Implement me!!
    while (UART2_FR_R & UART_FR_BUSY); // wait for UART ready
    UART2_DR_R = (data & UART_DR_DATA_M); //DR is the UART data register, clears the data field and writes in new data
    //UART2_DR_R = (UART2_DR_R & ~(UART_DR_DATA_M)) | (data & 0xFF);
    
}

void uart_write_str(uint8_t uart, char *str) {
    //below: increment the memory address, get value at the memory address and check it, null terminator is where the value is 0 and 0 is false so the loop is terminated
  while (*str) { // Loop until null terminator
    uart_write(uart, (uint32_t)*str++);
  }
}

inline void nl(uint8_t uart) {
  uart_write(uart, '\n');
}

void uart_write_hex(uint8_t uart, uint32_t data) {
  uint32_t nibble;

  for (int shift = 28; shift >= 0; shift -=4) {
    nibble = (data >> shift) & 0xF;
    if (nibble > 9) {
      nibble += 0x37;
    } else {
      nibble += 0x30;
    }
    uart_write(uart, nibble);
  }
}


void UART0_IRQHandler(void)
{
}
    