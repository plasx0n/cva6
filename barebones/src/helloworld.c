#include "uart.h"

static inline int template( int rs1 , int rs2){
    int rd; 
    asm volatile(" ld.sign %0,%1,%2" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2)); 
    return rd;
}

static inline float fmsub( float rs1 , float rs2, float rs3  ){
    float rd ; 
    asm volatile(" fmsub.s %0,%1,%2,%3" \
                            : "=f" (rd) \
                            : "f" (rs1), "f" (rs2), "f"(rs3)); 
    return rd;
}

static inline int ld_minmax( int rs1 , int rs2, int rs3  ){
    int rd ; 
    asm volatile(" ld3_minmax %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

int main()
{
    init_uart(50000000, 115200);
    print_uart("Hello World FROM RISCV BAREBONE\r\n");
    return 0;
}