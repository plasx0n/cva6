#include "uart.h"

static inline int template( int rs1 , int rs2){
    int rd; 
    asm volatile(" add %0,%1,%2" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2)); 
    return rd;
}

int main()
{
    init_uart(50000000, 115200);
    print_uart("Hello World FROM RISCV BAREBONE\r\n");
    
    print_uart("After initialisation\r\n");
    int test=0 ; 
    test= template(1,2); 
    print_uart_byte(test);
    print_uart("After addition\r\n");

    return 0;
}