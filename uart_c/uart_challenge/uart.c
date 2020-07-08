
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
    
    //1st: disable warten bit in CTL register (bit 0 furthest back one, page 453)
    // #define UART2_CTL_R
    //set warten bit to 0
    //turn bit on use or oporator, use & to turn it off
    //UART_CTL_R |= 0x40000E030 not needed, value already points to that spot in memory
    UART2_CTL_R &= ~(0x00000001); //correct
    
    //2nd: write integer portion of the BRD register
    // #define UART2_IBRD_R
    //we want 0x0a bit
    //IBRD is address of the register but we want the bit
    UART2_IBRD_R |= 0x0a;
    //#define UART_IBRD_DIVINT_MASK   //0x0000FFFF  // Integer baud-rate divisor
        
    //3rd: write fractional portion of the BRD register
    // #define UART2_FBRD_R
    //know it is FBRD from the paragraph
    //we want 0x36 bit
    UART2_FBRD_R |= 0x36; //cant just set equal because some bits are reserved, or prevents what you dont want change from being changed
    
    //4th:write desired serial parameters to CRH register
    // #define UART2_LCRH_R
    UART2_LCRH_R |= 0x00000060; //8 bit usuing or will not let the 0 bits be effective
        
    //5th: enable UART warten bit
    //set warten bit to 1
    UART2_CTL_R |= UART_LCRH_WLEN_8;
    //0x00000001
    
}

uint8_t uart_read(uint8_t uart, int blocking, int *read)
{
  // Implement me!!
    //page 444 read
    
    //while (FLASH_FMC_R & FLASH_FMC_WRITE); // Wait until write bit is 1
    //read is UARTRSR 
    // UART2_LCRH_R |= UART_LCRH_FEN; // 0000.0010
    if (blocking){
        while (UART2_FR_R & UART_FR_RXFE); // 0x00000010
        *read = 1;
        return UART2_DR_R & UART_DR_DATA_M; // 0x000000FF
    } else {
        if (UART2_FR_R & UART_FR_RXFF) { // 0x00000040
            *read = 1;
            return UART2_DR_R & UART_DR_DATA_M; // 0x000000FF
        } else {
            *read = 0;
            return 0;
        }
    }
}

void uart_write(uint8_t uart, uint32_t data)
{
  // Implement me!!
    //write is UARTECR
    while (UART2_FR_R & UART_FR_BUSY); // 0x00000008
    UART2_DR_R = (data & UART_DR_DATA_M); // 0x000000FF
    
}

void uart_write_str(uint8_t uart, char *str) {
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
    