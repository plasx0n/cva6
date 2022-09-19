#include "uart.h"

int main()
{
    init_uart(50000000, 115200);
    print_uart("Hello World FROM RISCV BAREBONE\r\n");
    
    float test  = 1.2f;

    print_uart("After initialisation\r\n");

    test  += 3.1f;

    print_uart("After addition\r\n");

    return 0;
}