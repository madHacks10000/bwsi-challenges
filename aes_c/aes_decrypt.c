#include "uart.h"
#include "bearssl.h"
#include <stdlib.h>
#include <string.h>
​
#define IV_LEN 0x10
#define KEY_LEN 0x10
#define KEY "thistheembseckey"
​
int main() {
    uart_init(UART2);
    int ret; 
​
    char * key = KEY;
    unsigned char iv[IV_LEN];
​
    for(int i = 0; i < IV_LEN; i++) {
        iv[i] = uart_read(UART2, BLOCKING, &ret);
    }
​
    unsigned short data_len = uart_read(UART2, BLOCKING, &ret) | (uart_read(UART2, BLOCKING, &ret) << 8) ;
    char * data = malloc(data_len);  
    for(int i = 0; i < data_len; i++) {
        data[i] = uart_read(UART2, BLOCKING, &ret);
    }
​
    const br_block_cbcdec_class * vd = &br_aes_big_cbcdec_vtable;
    br_aes_gen_cbcdec_keys v_dc;
    const br_block_cbcdec_class **dc;
​
    dc = &v_dc.vtable;
    vd->init(dc, key, KEY_LEN);
    vd->run(dc, iv, data, data_len);
​
    char * flag = strstr(data, "embsec{");
    int i = 0;
    while(flag[i] != '}') {
        uart_write(UART2, data[i]);
        i += 1;
    }
    uart_write(UART2, data[i]);
    uart_write(UART2, '\n');
​
    return 0;
}