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

void displayVectorHex( int8_tx4 vector ){
	printf("V4[31:24] %x ",   vector>>24) ;
	printf("V3[23:16] %x ",  (vector<<8)>>24) ;
	printf("V2[15:8]  %x ",  (vector<<16)>>24) ;
	printf("V1[7:0]   %x \n",(vector<<24)>>24) ;
}


int main() {


    int8_t a, b, c, d ; 

    a = 10 ;
    b = 5 ; 
    c = 15 ; 
    d = 20 ; 

// 0x00000000140f050a

    int8_tx4 test_vec = a | b<<8 | c << 16 | d <<24 ; 
    int8_tx4 sat_vec =  125 | 124 << 8 | 123 << 16 | 122 << 24 ;
    int8_tx4 res_vec ;


    // displayVector(test_vec) ; 
     
      // callAddSat(res_vec,test_vec,test_vec) ; 
      // callAddSat(res_vec,sat_vec,sat_vec) ; 

    // test de addsat 
    printf("addsat\n"); 
    callAddSat(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    printf("subsat\n"); 
    callSubSat(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    printf("F\n"); 
    callFinstr(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    printf("R\n"); 
    callRinstr(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    // saturations 
    printf("test saturation\n\n"); 
    displayVector(sat_vec) ;
    
    printf("addsat\n"); 
    callAddSat(res_vec,sat_vec,sat_vec) ; 
    displayVector(res_vec) ; 

    printf("subsat\n"); 
    callSubSat(res_vec,sat_vec,sat_vec) ; 
    displayVector(res_vec) ; 


  return 0;
}