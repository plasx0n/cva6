#include "stdint.h"
#include "./stdlib.h"

#define callRinstr(a,b,c) asm volatile("pl.r %0,%1,%2" \
	                            : "+r" (a) \
	                            : "r" (b), "r" (c)); 

#define callFinstr(a,b,c) asm volatile("pl.f %0,%1,%2" \
	                            : "+r" (a) \
	                            : "r" (b), "r" (c)); 

#define callSubSat(a,b,c) asm volatile("pl.subsat %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 
                                
#define callAddSat(a,b,c) asm volatile("pl.addsat %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 


#define int8_tx4 int32_t


void displayVector( int8_tx4 vector ){
	printf("V4[31:24] %d ",   vector>>24) ;
	printf("V3[23:16] %d ",  (vector<<8)>>24) ;
	printf("V2[15:8]  %d ",  (vector<<16)>>24) ;
	printf("V1[7:0]   %d \n",(vector<<24)>>24) ;
}

int main() {


    int8_t a, b, c, d ; 

    a = 10 ;
    b = 5 ; 
    c = 15 ; 
    d = 20 ; 

// 0x00000000140f050a

    int8_tx4 test_vec = a | b<<8 | c << 16 | d <<24 ; 
    displayVector(test_vec) ; 
    int8_tx4 res_vec ; 

    // test de addsat 
    callAddSat(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    callSubSat(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    callFinstr(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    callRinstr(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 




  return 0;
}