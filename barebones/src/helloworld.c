// #include "uart.h"
#include "stdlib.h"


int main()
{
    // init_uart(50000000, 115200);
    // print_uart("Hello World FROM RISCV BAREBONE\r\n");
    printf("test\n") ;

    long cycle1,cycles2  ; 
    long insn1, insn2 ;

    cycle1 = cycles() ; 
    insn1 = insn() ; 

    int dummy_var ; 
    for (int i = 0; i < 100; i++)
    {
        dummy_var++; 
    }
     
    cycles2 = cycles() - cycle1 ;  
    insn2   = insn() - insn1 ;  

    printf("cycles : %d \n",cycles2);
    printf("insn : %d \n",insn2);
    

    return 0;
}