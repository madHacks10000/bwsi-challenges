#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "uart.h"

uint8_t isAnagram (char* str_a, char* str_b) 
{
    int i;

    for(i=0; i<strlen(str_a); i++){
        char temp;
        temp = str_a[i];

        if(temp == ' '){
            continue;
        }
        int j;
        for(j=0; j<strlen(str_b); j++){
            char temp1;
            temp1 = str_b[j];
            if(temp == temp1){
                str_b[j] = ' ';
            }
        }
    }

    int k = 0;
    for(k=0; k<strlen(str_b); k++){
        if(str_b[k] == ' '){
            continue;
        }
        else {
            return 0;
        }
    } 
    return 1;
} 

int main () {
    uart_init(UART2);
    int ret;
    uint8_t numTests;
    char str_a[50];
    char str_b[50];
    uint8_t strPtr = 0;
    uint8_t testResult = 0;
    
    // Get ammount of tests
    numTests = uart_read(UART2, BLOCKING, &ret);

    // Begin main program loop
    for (int i = 0; i < numTests; i++) {
        char value = 0;
        uint8_t strPtr = 0;

        // Recieve first string
        while (value != 10) {
            value = uart_read(UART2, BLOCKING, &ret);
            str_a[strPtr++] = value;
        }
        str_a[(strPtr-1)] = '\0';  // Replaces newline with null terminator
        value = 0;
        strPtr = 0;

        // Recieve next string
        while (value != 10) {
            value = uart_read(UART2, BLOCKING, &ret);
            str_b[strPtr++] = value;
        }
        str_b[(strPtr-1)] = '\0';

        // Return result of test
        testResult = isAnagram(str_a, str_b);
        uart_write(UART2, (char) testResult);
    }

    return 0;
}
