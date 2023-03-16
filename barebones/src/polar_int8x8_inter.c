#include "stdint.h"
#include "./stdlib.h"

#define callRinstr(a,b,c) asm volatile("pl.r %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callFinstr(a,b,c) asm volatile("pl.f %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callSubSat(a,b,c) asm volatile("pl.subsat %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 
                                
#define callAddSat(a,b,c) asm volatile("pl.addsat %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callDecode(a,b,c) asm volatile("pl.decode %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callEval(a,b,c) asm volatile("pl.eval %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b),"r"(c)); 

                            
    #define codw_N 1024
    #define K codw_N/2
    int8_t froozen_bits[]={
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };

// double U int8x4
    int8_t U[]={
    1,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,0,0,1,0,0,1,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,1,1,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,1,
    1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0,1,0,0,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,0,0,0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,1,1,1,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,1,1,0,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,0,1,0,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,1,1,1,0,1,0,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

    1,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,0,0,1,0,0,1,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,1,1,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,1,
    1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0,1,0,0,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,0,0,0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,1,1,1,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,1,1,0,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,0,1,0,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,1,1,1,0,1,0,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    
    };


    int8_t codw_int[]={
    4,6,6,-5,6,6,-4,-5,4,4,6,6,8,6,-8,6,-6,-8,-7,-5,6,5,8,5,7,6,6,-4,-5,-5,-4,-6,5,-5,5,5,-6,-6,-6,-3,-4,-6,5,-6,-4,6,-3,4,-4,6,4,6,7,6,-7,6,7,-5,4,5,-7,5,5,4,-6,-5,5,5,6,5,-5,7,4,-7,6,7,5,-5,4,-5,-7,-6,3,-5,-6,5,-7,-7,5,-6,6,5,5,5,5,-5,-6,-5,-6,-6,6,-5,-5,5,6,6,-5,-6,6,-4,5,-6,6,5,-6,-4,6,-7,6,5,6,5,6,8,-4,7,-6,5,-7,4,3,-5,7,-5,7,6,7,-5,6,-7,-6,-6,-6,-4,5,-5,5,6,-4,4,8,-5,-7,5,-6,6,-6,4,-6,5,-6,4,6,-5,8,-5,-6,7,5,5,6,-5,6,5,4,-4,5,-5,-6,5,5,5,5,-6,6,4,8,-5,-8,4,3,6,-6,-6,-6,6,-7,-7,-4,5,5,6,5,5,7,-5,-7,6,6,5,5,-4,8,-6,-6,-6,5,4,7,-6,8,-6,-6,-6,-5,6,-6,-4,4,5,-5,-3,4,5,5,-5,-5,7,5,-5,5,5,-6,6,-6,-5,5,-6,5,3,5,-6,5,4,7,-5,-4,6,-7,6,7,-6,-6,-6,-6,5,-6,-6,5,-4,6,-5,-5,-5,5,-4,7,-5,6,-7,-3,-4,5,-5,6,-8,5,4,-4,6,-6,6,5,-5,6,6,-5,7,7,-4,6,-6,-4,7,6,-6,-5,7,-5,-7,6,5,6,-5,5,6,6,5,-6,-5,7,-4,5,5,6,6,-6,7,-4,6,-5,5,-8,6,7,-6,-6,7,5,-5,7,3,-6,4,-7,-5,5,-7,-3,6,6,6,-5,-5,6,-6,-4,-6,-6,-6,4,5,6,7,-5,6,-6,5,5,6,-6,-5,-5,5,-5,4,-7,-5,5,-6,6,4,6,-7,6,-6,5,5,-6,-5,-7,-6,7,-7,-6,6,6,5,5,-6,6,6,-6,5,6,-4,4,4,5,8,6,-4,5,4,4,6,5,5,8,6,-5,8,-6,6,3,-6,-4,-4,-6,-5,4,-6,5,-5,-5,-6,-5,5,8,-5,-5,7,4,-4,6,-5,6,6,-6,5,5,5,4,-6,7,6,7,-6,-5,5,-6,6,-6,-6,7,6,6,-4,-5,7,-4,-6,-4,5,-5,-5,-5,5,-5,-4,4,-5,-5,-5,4,-5,6,5,6,-4,-5,-5,-4,6,-5,5,4,-4,6,7,-6,7,-6,5,-5,-5,5,-4,5,-6,4,5,-4,-5,-5,5,-6,-6,4,7,-5,-7,-6,-5,-8,-7,5,-4,7,5,5,6,-4,-6,-6,-5,-5,-6,-4,5,6,5,6,5,-7,6,-5,-6,8,4,6,4,6,6,-5,4,5,-5,5,-6,4,-6,-5,-5,-5,-4,5,-7,-5,6,-5,-5,5,-5,-6,-6,4,7,-6,-6,-3,-5,7,-5,-4,5,-7,-6,-6,5,-6,5,6,5,-6,4,6,-4,5,6,-5,6,-4,-6,-6,-5,-6,5,5,5,5,7,-7,6,6,-4,-6,-5,5,5,-5,6,-6,4,-6,-8,6,6,-5,6,-5,-6,-6,-5,-6,-6,7,-5,6,-5,4,-6,-6,6,-6,5,-5,-5,-4,5,-7,4,5,6,6,5,-4,7,-5,-7,6,-7,-9,4,4,-5,6,-7,7,-4,5,-5,7,-4,-5,6,-6,5,7,-6,-6,-7,-6,5,-6,-6,-6,6,-7,5,6,-4,-5,-6,-4,7,-7,-6,-6,5,6,-8,-7,-6,8,6,5,-6,6,8,6,-6,-6,-6,-5,-6,-7,5,5,-3,-4,-6,-7,6,-6,5,5,5,-6,-6,-6,8,-4,7,4,6,7,-6,5,6,-7,-6,5,5,-5,-5,-5,6,5,-6,-5,4,-5,-7,6,-6,7,5,-7,5,-5,-7,-6,6,-5,-6,-5,7,5,-5,6,-6,-5,5,5,5,7,-6,7,7,-4,6,-5,5,7,6,-6,6,-7,5,-5,5,5,6,-4,5,-7,4,-6,-8,6,-6,6,-6,-6,6,-7,-5,4,-7,-5,5,-6,7,6,-6,-6,6,5,-5,5,6,-7,-5,-6,6,-6,-6,-4,-5,6,7,-4,6,-7,-4,-5,-4,6,-4,6,-4,7,-6,6,-4,-7,5,4,-6,-7,6,-5,-6,5,-6,7,4,-5,6,6,-5,-6,-5,4,5,-6,5,4,3,6,6,-5,-5,-6,-7,7,-4,5,-5,-4,-5,4,6,4,-4,7,-5,5,5,-6,4,-7,-5,-3,6,-7,4,-5,-4,5,3,6,5,-5,4,5,-5,-5,-4,-6,7,-6,-6,7,-6,-6,6,-5,-5,-4,-5,-6,5,-4,-7,-7,-5,-5,-5,-4,-5,6,-5,5,-7,-6,6,8,4,5,6,-7,6,-6,7,7,5,5,-6,-5,6,5,-6,-4,5,-6,5,-6,-5,6,-5,-8,-6,-7,5,-4,-5,-5,5,6,-6,3,-4,6,6,-7,-6,-6,6,5,-6,5,7,6,-5,5,5,8,-5,4,5,-6,6,5,7,-5,4,-6,-4,-5,6,5,5,5,-6,5,-8,-6,6,-6,-5,7,-6,5,-5,5,8,-6,5,-5,4,-5,-7,
    4,6,6,6,-5,6,-4,-5,-7,-7,-5,-5,-3,6,3,6,5,-8,-7,6,-5,5,-3,-6,-4,-5,6,7,6,-5,7,5,-6,6,-6,-6,-6,5,-6,8,-4,5,-6,-6,7,6,-3,4,-4,-5,4,6,7,-5,-7,-5,-4,-5,4,5,4,-6,-6,-7,5,-5,5,-6,6,5,-5,7,4,4,6,-4,5,6,4,-5,-7,-6,3,6,-6,5,-7,4,-6,-6,6,-6,-6,5,5,6,-6,-5,-6,-6,-5,-5,6,-6,-5,6,6,5,6,-4,5,-6,6,-6,5,7,-5,4,-5,-6,6,5,6,-3,7,7,5,-6,4,4,-8,6,-4,-5,7,-5,-4,6,6,4,-6,5,-6,7,-6,6,-6,-5,-4,4,-3,-5,4,-6,5,6,5,4,-6,-6,-6,-7,-5,-5,-3,6,-6,7,5,-6,6,-5,6,-6,4,-4,5,-5,-6,-6,5,-6,5,-6,-5,-7,8,-5,-8,4,-8,-5,5,-6,5,-5,-7,-7,-4,5,-6,-5,-6,5,7,-5,4,-5,-5,-6,-6,-4,-3,-6,-6,-6,-6,4,7,-6,-3,-6,-6,-6,-5,6,5,7,-7,5,-5,-3,4,5,-6,-5,6,-4,-6,6,-6,-6,5,6,5,-5,5,-6,-6,3,5,-6,-6,4,7,-5,7,6,-7,6,-4,-6,5,-6,-6,-6,5,-6,5,-4,-5,-5,-5,6,5,7,-4,-5,-5,4,8,7,-6,-5,-5,3,5,4,7,6,5,6,5,6,6,-5,6,7,-4,-4,-5,-6,7,-4,-5,5,-5,-4,-5,4,-5,5,6,6,-6,-5,-5,5,-6,-5,-4,7,-6,5,6,-5,5,7,-4,-5,-5,5,-8,6,-4,-6,-6,-4,5,6,7,3,5,-7,-7,6,-6,-7,-3,-5,6,6,-5,6,6,5,-4,5,5,5,-7,5,-5,-4,6,-5,5,-6,5,6,-6,-5,-5,-6,-5,4,-7,6,5,-6,-5,-7,6,-7,6,5,-6,5,-6,-5,-7,-6,-4,-7,-6,-5,6,5,-6,5,-5,-5,5,-6,-5,-4,4,4,-6,-3,6,-4,-6,4,-7,-5,5,-6,-3,6,6,-3,-6,6,-8,5,7,-4,-6,6,4,-6,-6,6,-5,-6,6,5,-3,6,6,-4,4,-4,-5,-5,-5,-5,5,5,-6,-6,4,5,7,6,7,-6,-5,5,5,-5,5,5,-4,-5,-5,7,6,-4,7,5,-4,5,-5,-5,-5,5,-5,-4,-7,-5,-5,-5,-7,6,-5,-6,-5,-4,-5,-5,7,-5,6,-6,-7,-4,6,7,-6,7,-6,5,6,-5,5,-4,5,-6,4,5,-4,-5,-5,-6,5,-6,4,7,6,4,5,6,3,-7,-6,-4,-4,5,5,-5,7,-6,5,6,6,5,-4,-6,-5,5,-5,-6,4,-5,6,5,8,-7,6,-7,6,-5,6,4,-6,-5,5,-6,4,5,-5,-5,-5,7,5,4,6,6,-5,-5,-6,6,5,5,-7,7,-6,5,-3,-5,7,-5,-4,-6,-7,5,-6,-6,-6,5,6,5,-6,-7,6,-4,5,-5,6,6,-4,5,5,-5,-6,-6,5,5,5,7,4,6,-5,7,5,-5,-6,-6,-5,6,-6,4,-6,3,-5,-5,6,-5,6,5,-6,-5,-6,5,-4,-5,-5,6,-7,-6,5,-5,5,5,-5,6,7,-6,-7,-7,5,-5,6,-6,7,-4,6,4,6,-7,2,4,-7,6,-5,-7,-4,-4,5,6,7,7,6,6,5,-6,7,-6,-6,4,-6,5,-6,5,-6,6,-7,5,6,7,-5,5,-4,7,4,5,-6,5,6,-8,4,5,-3,6,-6,5,6,8,6,-6,5,5,6,-6,-7,5,-6,8,7,5,4,6,5,5,5,5,5,-6,-6,8,7,7,4,6,7,-6,-6,-5,4,-6,5,5,-5,-5,6,6,-6,5,6,-7,6,4,-5,-6,-4,5,-7,5,6,-7,-6,6,6,-6,-5,7,-6,-5,6,-6,6,5,-6,5,7,5,-4,7,-4,6,6,5,7,-5,-6,-5,4,5,6,-6,-6,-5,7,5,4,-7,-6,-8,-5,-6,-5,-6,-6,-5,-7,6,-7,-7,6,5,5,7,-5,5,5,-5,5,6,5,-5,4,-5,-6,-5,5,5,7,-5,6,7,7,-5,4,-4,-5,7,-5,-4,6,7,7,-6,6,-4,4,5,4,5,-7,-5,-5,-6,-6,5,7,-7,6,6,6,6,-6,-5,4,-6,-6,-6,4,-8,-5,-5,6,-5,5,4,-4,7,-6,6,-4,-5,4,6,4,7,7,-5,5,-6,-6,4,4,6,-3,6,-7,-7,6,-4,5,3,6,5,6,4,5,6,-5,-4,5,-4,5,5,-4,5,5,6,-5,-5,7,6,-6,5,7,-7,4,6,-5,6,7,-5,-5,6,5,-7,5,-5,-3,4,5,-5,-7,6,5,-4,7,5,-6,-6,6,-5,-6,5,-4,5,5,5,5,6,-5,-5,3,5,-7,-6,-4,-5,-5,5,6,-6,-8,7,-5,-5,4,5,5,-5,-6,5,-6,-4,6,-5,5,5,8,-5,4,5,5,6,5,7,6,-7,5,7,6,6,5,5,-6,5,-6,3,5,6,-6,-5,7,-6,5,-5,-6,8,-6,5,-5,4,-5,-7,
    -7,6,-5,6,6,6,-4,6,4,-7,6,6,8,-5,-8,-5,5,-8,-7,6,-5,5,8,5,-4,-5,6,-4,-5,-5,7,-6,-6,-5,5,-6,-6,-6,5,-3,7,-6,5,5,-4,-5,-3,-7,-4,-5,4,-5,7,6,-7,6,7,-5,4,5,-7,5,-6,-7,-6,6,5,-6,6,5,-5,-4,-7,4,6,-4,5,6,-7,-5,4,5,3,6,5,-6,4,4,5,-6,6,5,-6,5,5,-5,-6,6,-6,5,6,6,6,5,-5,6,6,5,6,-4,-6,-6,-5,5,5,-4,6,-7,6,5,-5,-6,-5,-3,7,-4,-6,-6,4,4,3,-5,-4,6,7,-5,-4,-5,-5,-7,5,-6,5,-4,-6,6,-6,-5,-4,-7,8,6,4,-6,5,6,-6,4,5,-6,-6,4,6,-5,8,-5,5,-4,-6,5,-5,-5,-5,5,-7,-4,5,-5,5,5,-6,5,-6,5,6,4,-3,-5,-8,-7,-8,-5,-6,5,5,-5,4,4,7,5,-6,-5,-6,5,-4,6,-7,-5,-5,-6,-6,7,-3,-6,-6,5,-6,4,-4,-6,8,5,5,-6,-5,-5,-6,7,4,-6,6,8,4,5,5,6,-5,-4,-6,-5,-6,5,-6,6,5,6,5,5,-6,-8,-6,-6,-6,-7,-4,-5,7,6,4,-5,-4,-6,5,-6,5,-6,5,-6,-6,-4,-5,-5,-5,6,5,-4,-4,-5,6,-7,-3,7,-6,6,6,-8,5,-7,7,-5,-6,-5,5,-5,6,-5,-5,7,-4,-4,6,-6,-4,-4,-5,-6,-5,7,-5,-7,6,-6,6,-5,-6,-5,-5,5,-6,-5,-4,-4,-6,-6,-5,6,5,-4,-4,6,-5,5,-8,6,7,-6,5,7,5,-5,-4,3,-6,-7,-7,6,-6,4,-3,6,6,-5,-5,6,6,-6,-4,-6,-6,-6,-7,5,-5,-4,6,-5,-6,-6,5,6,-6,6,-5,5,-5,-7,-7,6,-6,-6,6,-7,-5,-7,6,-6,5,5,-6,6,-7,-6,7,-7,5,6,-5,-6,5,-6,6,-5,5,-6,-5,7,-7,-7,5,8,6,-4,5,4,4,-5,5,5,-3,-5,-5,-3,5,-5,3,5,-4,-4,5,6,-7,-6,-6,-5,-5,-6,6,-6,8,-5,-5,-4,-7,-4,-5,-5,-5,-5,5,5,5,5,4,-6,7,-5,7,5,6,-6,5,6,5,-6,7,-5,-5,-4,6,7,7,-6,7,5,6,-5,6,5,6,-4,4,6,6,-5,-7,6,-5,-6,-5,-4,-5,-5,-4,-5,-5,-6,4,-4,6,-4,-6,-4,-6,-6,-5,-5,-6,-4,-6,-6,-7,5,7,-5,6,-6,-6,-6,4,-4,-5,4,-6,-5,-8,4,5,7,-4,5,5,-5,7,-6,-6,-5,6,5,-4,5,6,5,-5,5,4,6,-5,5,8,4,-5,4,-5,6,-5,-7,5,6,5,5,4,5,-5,6,-5,-4,5,-7,-5,6,-5,-5,5,-5,5,5,4,-4,-6,5,-3,-5,7,6,7,-6,-7,5,-6,-6,5,5,-5,-6,-6,-7,-5,7,-6,-5,-5,6,-4,-6,5,-5,-6,5,5,-6,5,-4,-7,-5,-5,-4,5,-5,-6,-6,-5,6,5,4,5,-8,-5,6,-5,6,-5,-6,5,6,5,5,-4,6,6,6,-7,-6,-6,6,5,-6,-5,6,7,5,4,4,-6,6,-5,5,7,-4,6,4,6,4,-9,-7,-7,6,-5,-7,7,-4,-6,6,7,-4,-5,6,-6,5,-4,5,5,-7,5,5,5,-6,5,6,-7,5,-5,-4,6,-6,7,-4,-7,-6,5,5,6,3,4,5,8,-5,-6,5,-5,-3,-5,-6,5,5,6,-6,4,-6,5,8,7,5,4,-5,5,5,5,-6,5,-6,5,8,-4,-4,-7,6,7,5,5,-5,-7,5,-6,-6,-5,-5,-5,-5,5,5,6,4,6,-7,6,-6,-4,-6,-7,-6,6,4,5,6,6,5,6,7,-6,-5,-5,5,6,5,-6,5,-4,5,-4,7,7,6,6,5,7,-5,-6,6,4,5,-5,5,5,-5,7,-6,-7,4,-6,3,-5,5,6,5,-6,6,-7,6,4,-7,6,5,-6,7,6,5,5,6,5,-5,5,6,-7,6,-6,6,5,5,7,-5,6,7,7,6,4,7,6,-4,-5,7,6,-4,7,-6,6,-4,-7,5,-7,-6,-7,6,6,-6,5,5,7,-7,6,-5,6,-5,-6,6,4,-6,-6,5,4,3,6,6,6,-5,5,4,-4,7,5,6,-4,-5,4,-5,4,-4,7,6,5,-6,5,4,-7,6,8,6,-7,4,-5,-4,5,-8,6,5,-5,4,-6,-5,6,7,-6,7,-6,5,-4,5,5,-5,6,6,-4,-5,-6,5,-4,-7,-7,6,-5,-5,7,6,6,6,-6,4,-6,-5,8,4,-6,-5,4,6,5,7,7,5,-6,5,-5,6,5,5,7,5,5,5,5,6,-5,-5,-8,-6,-7,5,-4,6,-5,-6,-5,5,-8,-4,-5,6,-7,5,5,6,-6,-6,-6,7,-5,-5,-6,5,-3,-5,-7,5,-6,-5,-6,7,6,-7,5,7,6,6,5,5,5,5,5,3,-6,6,-6,6,7,5,5,6,5,8,5,5,6,4,6,-7,
    4,6,6,6,6,-5,-4,-5,-7,-7,-5,-5,8,6,-8,-5,5,3,4,6,-5,-6,-3,5,7,6,6,7,-5,6,7,-6,5,-5,-6,5,5,-6,5,8,-4,5,5,5,7,6,-3,-7,7,-5,4,6,7,-5,4,6,7,6,4,5,4,-6,-6,-7,-6,6,-6,5,6,-6,6,-4,-7,4,-5,-4,5,6,4,-5,-7,5,-8,-5,-6,-6,-7,4,5,-6,6,5,5,5,5,-5,-6,-5,-6,-6,6,6,6,5,-5,6,6,5,6,-4,-6,-6,6,-6,5,7,6,-7,6,5,6,-6,-5,-3,7,-4,-6,-6,-7,4,3,6,7,-5,7,6,-4,-5,-5,-7,5,-6,-6,-4,-6,-5,-6,-5,-4,-7,-3,6,4,5,5,6,5,4,5,-6,-6,-7,-5,6,8,6,5,7,-6,5,-5,-5,-5,5,-7,-4,-6,-5,5,5,5,5,5,5,6,4,-3,-5,-8,-7,-8,-5,5,5,-6,6,4,4,-4,5,-6,-5,5,5,-4,6,4,-5,-5,-6,5,7,8,-6,-6,5,5,4,-4,-6,-3,5,5,-6,-5,6,-6,-4,4,-6,6,8,4,5,5,6,-5,-4,-6,-5,5,5,5,6,5,6,5,5,-6,-8,-6,-6,-6,-7,-4,-5,-4,-5,-7,-5,-4,-6,5,-6,-6,5,-6,-6,5,7,6,-5,-5,-5,-6,7,7,6,6,-7,8,7,-6,6,6,3,5,-7,7,-5,-6,-5,5,6,-5,-5,-5,7,-4,-4,-5,5,-4,-4,-5,5,-5,-4,-5,4,-5,-6,6,-5,-6,-5,6,-6,-6,-5,-4,7,5,-6,6,-5,5,-4,-4,-5,-5,5,3,6,7,-6,5,7,-6,6,7,3,5,-7,-7,-5,-6,4,8,6,6,-5,-5,-5,-5,-6,-4,-6,-6,-6,4,-6,-5,-4,6,-5,-6,-6,-6,6,-6,-5,-5,5,-5,-7,4,-5,-6,-6,6,-7,-5,-7,6,-6,5,5,-6,6,4,-6,7,4,5,6,6,-6,5,-6,6,-5,5,-6,-5,7,4,-7,-6,8,6,-4,-6,4,4,-5,5,5,-3,-5,6,-3,-6,-5,3,5,-4,-4,5,6,-7,-6,-6,-5,-5,-6,-5,-6,-3,-5,-5,-4,-7,-4,-5,-5,-5,-5,-6,-6,-6,5,-7,-6,7,-5,-4,5,6,-6,-6,6,5,-6,7,-5,6,-4,-5,7,7,-6,-4,5,6,-5,-5,5,6,-4,-7,6,-5,-5,-7,6,-5,-6,-5,-4,-5,-5,-4,-5,-5,-6,-7,-4,-5,-4,-6,-4,-6,-6,-5,-5,-6,-4,-6,-6,-7,5,-4,-5,-5,-6,-6,5,4,7,6,4,5,6,-8,-7,5,7,-4,-6,-6,-5,7,5,5,-5,-5,-6,-4,-6,6,-6,-5,5,-7,6,6,-6,-3,4,-5,-7,6,-5,-5,-7,-6,-5,5,5,-7,5,-5,-5,-5,7,-6,-7,-5,-5,-5,-5,-6,6,5,5,4,-4,5,-6,-3,6,-4,6,7,-6,4,5,-6,-6,-6,5,6,-6,5,4,6,7,5,-5,-5,6,-4,-6,-6,-5,-6,5,5,5,5,7,-7,-5,-5,-4,5,-5,-6,-6,-5,6,5,4,-6,3,-5,-5,-5,6,-5,-6,-6,6,5,5,-4,6,6,6,4,-6,-6,-5,-6,5,-5,-5,7,5,4,4,-6,6,6,5,7,7,6,4,6,4,2,-7,-7,-5,-5,-7,-4,-4,-6,6,7,7,6,-5,-6,-6,-4,-6,5,-7,5,5,5,-6,5,6,4,5,-5,-4,-5,-6,-4,-4,-7,-6,5,5,6,3,4,5,-3,-5,5,-6,-5,-3,6,-6,5,5,-5,-6,4,-6,-6,8,7,5,-7,-5,-6,5,5,-6,-6,-6,5,8,7,-4,-7,6,7,-6,5,6,-7,5,-6,-6,-5,-5,-5,-5,5,5,6,4,-5,-7,-5,-6,-4,-6,-7,-6,6,4,5,6,6,5,6,7,5,6,6,5,6,5,-6,5,7,-6,7,7,-4,-5,-5,5,7,6,5,-5,-7,-6,-5,5,-6,-5,7,-6,-7,-7,-6,3,-5,5,6,5,-6,-5,4,6,4,-7,6,5,5,-4,6,5,5,-5,5,6,5,-5,4,6,-6,6,5,5,-4,6,6,7,7,-5,-7,7,-5,7,-5,7,6,7,7,-6,-5,-4,-7,5,-7,-6,4,-5,-5,-6,-6,5,7,4,6,-5,-5,-5,-6,6,4,5,5,5,4,3,6,6,-5,6,5,4,-4,7,5,6,7,-5,4,6,4,-4,7,6,-6,5,5,4,-7,6,8,6,-7,4,-5,-4,5,-8,-5,5,-5,-7,-6,-5,-5,7,-6,7,-6,5,-4,5,5,-5,-5,6,7,-5,-6,5,7,-7,-7,6,-5,-5,7,6,-5,6,5,4,-6,-5,8,4,-6,-5,4,6,5,7,7,5,5,5,6,6,5,5,7,5,5,5,5,6,6,6,3,-6,4,5,-4,6,6,-6,-5,5,3,-4,-5,6,-7,5,-6,6,5,-6,-6,7,6,-5,-6,5,8,-5,-7,5,5,-5,5,7,6,-7,5,7,6,6,5,5,5,5,5,3,5,6,5,6,7,5,5,6,5,8,5,5,6,4,6,-7,

    4,6,6,-5,6,6,-4,-5,4,4,6,6,8,6,-8,6,-6,-8,-7,-5,6,5,8,5,7,6,6,-4,-5,-5,-4,-6,5,-5,5,5,-6,-6,-6,-3,-4,-6,5,-6,-4,6,-3,4,-4,6,4,6,7,6,-7,6,7,-5,4,5,-7,5,5,4,-6,-5,5,5,6,5,-5,7,4,-7,6,7,5,-5,4,-5,-7,-6,3,-5,-6,5,-7,-7,5,-6,6,5,5,5,5,-5,-6,-5,-6,-6,6,-5,-5,5,6,6,-5,-6,6,-4,5,-6,6,5,-6,-4,6,-7,6,5,6,5,6,8,-4,7,-6,5,-7,4,3,-5,7,-5,7,6,7,-5,6,-7,-6,-6,-6,-4,5,-5,5,6,-4,4,8,-5,-7,5,-6,6,-6,4,-6,5,-6,4,6,-5,8,-5,-6,7,5,5,6,-5,6,5,4,-4,5,-5,-6,5,5,5,5,-6,6,4,8,-5,-8,4,3,6,-6,-6,-6,6,-7,-7,-4,5,5,6,5,5,7,-5,-7,6,6,5,5,-4,8,-6,-6,-6,5,4,7,-6,8,-6,-6,-6,-5,6,-6,-4,4,5,-5,-3,4,5,5,-5,-5,7,5,-5,5,5,-6,6,-6,-5,5,-6,5,3,5,-6,5,4,7,-5,-4,6,-7,6,7,-6,-6,-6,-6,5,-6,-6,5,-4,6,-5,-5,-5,5,-4,7,-5,6,-7,-3,-4,5,-5,6,-8,5,4,-4,6,-6,6,5,-5,6,6,-5,7,7,-4,6,-6,-4,7,6,-6,-5,7,-5,-7,6,5,6,-5,5,6,6,5,-6,-5,7,-4,5,5,6,6,-6,7,-4,6,-5,5,-8,6,7,-6,-6,7,5,-5,7,3,-6,4,-7,-5,5,-7,-3,6,6,6,-5,-5,6,-6,-4,-6,-6,-6,4,5,6,7,-5,6,-6,5,5,6,-6,-5,-5,5,-5,4,-7,-5,5,-6,6,4,6,-7,6,-6,5,5,-6,-5,-7,-6,7,-7,-6,6,6,5,5,-6,6,6,-6,5,6,-4,4,4,5,8,6,-4,5,4,4,6,5,5,8,6,-5,8,-6,6,3,-6,-4,-4,-6,-5,4,-6,5,-5,-5,-6,-5,5,8,-5,-5,7,4,-4,6,-5,6,6,-6,5,5,5,4,-6,7,6,7,-6,-5,5,-6,6,-6,-6,7,6,6,-4,-5,7,-4,-6,-4,5,-5,-5,-5,5,-5,-4,4,-5,-5,-5,4,-5,6,5,6,-4,-5,-5,-4,6,-5,5,4,-4,6,7,-6,7,-6,5,-5,-5,5,-4,5,-6,4,5,-4,-5,-5,5,-6,-6,4,7,-5,-7,-6,-5,-8,-7,5,-4,7,5,5,6,-4,-6,-6,-5,-5,-6,-4,5,6,5,6,5,-7,6,-5,-6,8,4,6,4,6,6,-5,4,5,-5,5,-6,4,-6,-5,-5,-5,-4,5,-7,-5,6,-5,-5,5,-5,-6,-6,4,7,-6,-6,-3,-5,7,-5,-4,5,-7,-6,-6,5,-6,5,6,5,-6,4,6,-4,5,6,-5,6,-4,-6,-6,-5,-6,5,5,5,5,7,-7,6,6,-4,-6,-5,5,5,-5,6,-6,4,-6,-8,6,6,-5,6,-5,-6,-6,-5,-6,-6,7,-5,6,-5,4,-6,-6,6,-6,5,-5,-5,-4,5,-7,4,5,6,6,5,-4,7,-5,-7,6,-7,-9,4,4,-5,6,-7,7,-4,5,-5,7,-4,-5,6,-6,5,7,-6,-6,-7,-6,5,-6,-6,-6,6,-7,5,6,-4,-5,-6,-4,7,-7,-6,-6,5,6,-8,-7,-6,8,6,5,-6,6,8,6,-6,-6,-6,-5,-6,-7,5,5,-3,-4,-6,-7,6,-6,5,5,5,-6,-6,-6,8,-4,7,4,6,7,-6,5,6,-7,-6,5,5,-5,-5,-5,6,5,-6,-5,4,-5,-7,6,-6,7,5,-7,5,-5,-7,-6,6,-5,-6,-5,7,5,-5,6,-6,-5,5,5,5,7,-6,7,7,-4,6,-5,5,7,6,-6,6,-7,5,-5,5,5,6,-4,5,-7,4,-6,-8,6,-6,6,-6,-6,6,-7,-5,4,-7,-5,5,-6,7,6,-6,-6,6,5,-5,5,6,-7,-5,-6,6,-6,-6,-4,-5,6,7,-4,6,-7,-4,-5,-4,6,-4,6,-4,7,-6,6,-4,-7,5,4,-6,-7,6,-5,-6,5,-6,7,4,-5,6,6,-5,-6,-5,4,5,-6,5,4,3,6,6,-5,-5,-6,-7,7,-4,5,-5,-4,-5,4,6,4,-4,7,-5,5,5,-6,4,-7,-5,-3,6,-7,4,-5,-4,5,3,6,5,-5,4,5,-5,-5,-4,-6,7,-6,-6,7,-6,-6,6,-5,-5,-4,-5,-6,5,-4,-7,-7,-5,-5,-5,-4,-5,6,-5,5,-7,-6,6,8,4,5,6,-7,6,-6,7,7,5,5,-6,-5,6,5,-6,-4,5,-6,5,-6,-5,6,-5,-8,-6,-7,5,-4,-5,-5,5,6,-6,3,-4,6,6,-7,-6,-6,6,5,-6,5,7,6,-5,5,5,8,-5,4,5,-6,6,5,7,-5,4,-6,-4,-5,6,5,5,5,-6,5,-8,-6,6,-6,-5,7,-6,5,-5,5,8,-6,5,-5,4,-5,-7,
    4,6,6,6,-5,6,-4,-5,-7,-7,-5,-5,-3,6,3,6,5,-8,-7,6,-5,5,-3,-6,-4,-5,6,7,6,-5,7,5,-6,6,-6,-6,-6,5,-6,8,-4,5,-6,-6,7,6,-3,4,-4,-5,4,6,7,-5,-7,-5,-4,-5,4,5,4,-6,-6,-7,5,-5,5,-6,6,5,-5,7,4,4,6,-4,5,6,4,-5,-7,-6,3,6,-6,5,-7,4,-6,-6,6,-6,-6,5,5,6,-6,-5,-6,-6,-5,-5,6,-6,-5,6,6,5,6,-4,5,-6,6,-6,5,7,-5,4,-5,-6,6,5,6,-3,7,7,5,-6,4,4,-8,6,-4,-5,7,-5,-4,6,6,4,-6,5,-6,7,-6,6,-6,-5,-4,4,-3,-5,4,-6,5,6,5,4,-6,-6,-6,-7,-5,-5,-3,6,-6,7,5,-6,6,-5,6,-6,4,-4,5,-5,-6,-6,5,-6,5,-6,-5,-7,8,-5,-8,4,-8,-5,5,-6,5,-5,-7,-7,-4,5,-6,-5,-6,5,7,-5,4,-5,-5,-6,-6,-4,-3,-6,-6,-6,-6,4,7,-6,-3,-6,-6,-6,-5,6,5,7,-7,5,-5,-3,4,5,-6,-5,6,-4,-6,6,-6,-6,5,6,5,-5,5,-6,-6,3,5,-6,-6,4,7,-5,7,6,-7,6,-4,-6,5,-6,-6,-6,5,-6,5,-4,-5,-5,-5,6,5,7,-4,-5,-5,4,8,7,-6,-5,-5,3,5,4,7,6,5,6,5,6,6,-5,6,7,-4,-4,-5,-6,7,-4,-5,5,-5,-4,-5,4,-5,5,6,6,-6,-5,-5,5,-6,-5,-4,7,-6,5,6,-5,5,7,-4,-5,-5,5,-8,6,-4,-6,-6,-4,5,6,7,3,5,-7,-7,6,-6,-7,-3,-5,6,6,-5,6,6,5,-4,5,5,5,-7,5,-5,-4,6,-5,5,-6,5,6,-6,-5,-5,-6,-5,4,-7,6,5,-6,-5,-7,6,-7,6,5,-6,5,-6,-5,-7,-6,-4,-7,-6,-5,6,5,-6,5,-5,-5,5,-6,-5,-4,4,4,-6,-3,6,-4,-6,4,-7,-5,5,-6,-3,6,6,-3,-6,6,-8,5,7,-4,-6,6,4,-6,-6,6,-5,-6,6,5,-3,6,6,-4,4,-4,-5,-5,-5,-5,5,5,-6,-6,4,5,7,6,7,-6,-5,5,5,-5,5,5,-4,-5,-5,7,6,-4,7,5,-4,5,-5,-5,-5,5,-5,-4,-7,-5,-5,-5,-7,6,-5,-6,-5,-4,-5,-5,7,-5,6,-6,-7,-4,6,7,-6,7,-6,5,6,-5,5,-4,5,-6,4,5,-4,-5,-5,-6,5,-6,4,7,6,4,5,6,3,-7,-6,-4,-4,5,5,-5,7,-6,5,6,6,5,-4,-6,-5,5,-5,-6,4,-5,6,5,8,-7,6,-7,6,-5,6,4,-6,-5,5,-6,4,5,-5,-5,-5,7,5,4,6,6,-5,-5,-6,6,5,5,-7,7,-6,5,-3,-5,7,-5,-4,-6,-7,5,-6,-6,-6,5,6,5,-6,-7,6,-4,5,-5,6,6,-4,5,5,-5,-6,-6,5,5,5,7,4,6,-5,7,5,-5,-6,-6,-5,6,-6,4,-6,3,-5,-5,6,-5,6,5,-6,-5,-6,5,-4,-5,-5,6,-7,-6,5,-5,5,5,-5,6,7,-6,-7,-7,5,-5,6,-6,7,-4,6,4,6,-7,2,4,-7,6,-5,-7,-4,-4,5,6,7,7,6,6,5,-6,7,-6,-6,4,-6,5,-6,5,-6,6,-7,5,6,7,-5,5,-4,7,4,5,-6,5,6,-8,4,5,-3,6,-6,5,6,8,6,-6,5,5,6,-6,-7,5,-6,8,7,5,4,6,5,5,5,5,5,-6,-6,8,7,7,4,6,7,-6,-6,-5,4,-6,5,5,-5,-5,6,6,-6,5,6,-7,6,4,-5,-6,-4,5,-7,5,6,-7,-6,6,6,-6,-5,7,-6,-5,6,-6,6,5,-6,5,7,5,-4,7,-4,6,6,5,7,-5,-6,-5,4,5,6,-6,-6,-5,7,5,4,-7,-6,-8,-5,-6,-5,-6,-6,-5,-7,6,-7,-7,6,5,5,7,-5,5,5,-5,5,6,5,-5,4,-5,-6,-5,5,5,7,-5,6,7,7,-5,4,-4,-5,7,-5,-4,6,7,7,-6,6,-4,4,5,4,5,-7,-5,-5,-6,-6,5,7,-7,6,6,6,6,-6,-5,4,-6,-6,-6,4,-8,-5,-5,6,-5,5,4,-4,7,-6,6,-4,-5,4,6,4,7,7,-5,5,-6,-6,4,4,6,-3,6,-7,-7,6,-4,5,3,6,5,6,4,5,6,-5,-4,5,-4,5,5,-4,5,5,6,-5,-5,7,6,-6,5,7,-7,4,6,-5,6,7,-5,-5,6,5,-7,5,-5,-3,4,5,-5,-7,6,5,-4,7,5,-6,-6,6,-5,-6,5,-4,5,5,5,5,6,-5,-5,3,5,-7,-6,-4,-5,-5,5,6,-6,-8,7,-5,-5,4,5,5,-5,-6,5,-6,-4,6,-5,5,5,8,-5,4,5,5,6,5,7,6,-7,5,7,6,6,5,5,-6,5,-6,3,5,6,-6,-5,7,-6,5,-5,-6,8,-6,5,-5,4,-5,-7,
    -7,6,-5,6,6,6,-4,6,4,-7,6,6,8,-5,-8,-5,5,-8,-7,6,-5,5,8,5,-4,-5,6,-4,-5,-5,7,-6,-6,-5,5,-6,-6,-6,5,-3,7,-6,5,5,-4,-5,-3,-7,-4,-5,4,-5,7,6,-7,6,7,-5,4,5,-7,5,-6,-7,-6,6,5,-6,6,5,-5,-4,-7,4,6,-4,5,6,-7,-5,4,5,3,6,5,-6,4,4,5,-6,6,5,-6,5,5,-5,-6,6,-6,5,6,6,6,5,-5,6,6,5,6,-4,-6,-6,-5,5,5,-4,6,-7,6,5,-5,-6,-5,-3,7,-4,-6,-6,4,4,3,-5,-4,6,7,-5,-4,-5,-5,-7,5,-6,5,-4,-6,6,-6,-5,-4,-7,8,6,4,-6,5,6,-6,4,5,-6,-6,4,6,-5,8,-5,5,-4,-6,5,-5,-5,-5,5,-7,-4,5,-5,5,5,-6,5,-6,5,6,4,-3,-5,-8,-7,-8,-5,-6,5,5,-5,4,4,7,5,-6,-5,-6,5,-4,6,-7,-5,-5,-6,-6,7,-3,-6,-6,5,-6,4,-4,-6,8,5,5,-6,-5,-5,-6,7,4,-6,6,8,4,5,5,6,-5,-4,-6,-5,-6,5,-6,6,5,6,5,5,-6,-8,-6,-6,-6,-7,-4,-5,7,6,4,-5,-4,-6,5,-6,5,-6,5,-6,-6,-4,-5,-5,-5,6,5,-4,-4,-5,6,-7,-3,7,-6,6,6,-8,5,-7,7,-5,-6,-5,5,-5,6,-5,-5,7,-4,-4,6,-6,-4,-4,-5,-6,-5,7,-5,-7,6,-6,6,-5,-6,-5,-5,5,-6,-5,-4,-4,-6,-6,-5,6,5,-4,-4,6,-5,5,-8,6,7,-6,5,7,5,-5,-4,3,-6,-7,-7,6,-6,4,-3,6,6,-5,-5,6,6,-6,-4,-6,-6,-6,-7,5,-5,-4,6,-5,-6,-6,5,6,-6,6,-5,5,-5,-7,-7,6,-6,-6,6,-7,-5,-7,6,-6,5,5,-6,6,-7,-6,7,-7,5,6,-5,-6,5,-6,6,-5,5,-6,-5,7,-7,-7,5,8,6,-4,5,4,4,-5,5,5,-3,-5,-5,-3,5,-5,3,5,-4,-4,5,6,-7,-6,-6,-5,-5,-6,6,-6,8,-5,-5,-4,-7,-4,-5,-5,-5,-5,5,5,5,5,4,-6,7,-5,7,5,6,-6,5,6,5,-6,7,-5,-5,-4,6,7,7,-6,7,5,6,-5,6,5,6,-4,4,6,6,-5,-7,6,-5,-6,-5,-4,-5,-5,-4,-5,-5,-6,4,-4,6,-4,-6,-4,-6,-6,-5,-5,-6,-4,-6,-6,-7,5,7,-5,6,-6,-6,-6,4,-4,-5,4,-6,-5,-8,4,5,7,-4,5,5,-5,7,-6,-6,-5,6,5,-4,5,6,5,-5,5,4,6,-5,5,8,4,-5,4,-5,6,-5,-7,5,6,5,5,4,5,-5,6,-5,-4,5,-7,-5,6,-5,-5,5,-5,5,5,4,-4,-6,5,-3,-5,7,6,7,-6,-7,5,-6,-6,5,5,-5,-6,-6,-7,-5,7,-6,-5,-5,6,-4,-6,5,-5,-6,5,5,-6,5,-4,-7,-5,-5,-4,5,-5,-6,-6,-5,6,5,4,5,-8,-5,6,-5,6,-5,-6,5,6,5,5,-4,6,6,6,-7,-6,-6,6,5,-6,-5,6,7,5,4,4,-6,6,-5,5,7,-4,6,4,6,4,-9,-7,-7,6,-5,-7,7,-4,-6,6,7,-4,-5,6,-6,5,-4,5,5,-7,5,5,5,-6,5,6,-7,5,-5,-4,6,-6,7,-4,-7,-6,5,5,6,3,4,5,8,-5,-6,5,-5,-3,-5,-6,5,5,6,-6,4,-6,5,8,7,5,4,-5,5,5,5,-6,5,-6,5,8,-4,-4,-7,6,7,5,5,-5,-7,5,-6,-6,-5,-5,-5,-5,5,5,6,4,6,-7,6,-6,-4,-6,-7,-6,6,4,5,6,6,5,6,7,-6,-5,-5,5,6,5,-6,5,-4,5,-4,7,7,6,6,5,7,-5,-6,6,4,5,-5,5,5,-5,7,-6,-7,4,-6,3,-5,5,6,5,-6,6,-7,6,4,-7,6,5,-6,7,6,5,5,6,5,-5,5,6,-7,6,-6,6,5,5,7,-5,6,7,7,6,4,7,6,-4,-5,7,6,-4,7,-6,6,-4,-7,5,-7,-6,-7,6,6,-6,5,5,7,-7,6,-5,6,-5,-6,6,4,-6,-6,5,4,3,6,6,6,-5,5,4,-4,7,5,6,-4,-5,4,-5,4,-4,7,6,5,-6,5,4,-7,6,8,6,-7,4,-5,-4,5,-8,6,5,-5,4,-6,-5,6,7,-6,7,-6,5,-4,5,5,-5,6,6,-4,-5,-6,5,-4,-7,-7,6,-5,-5,7,6,6,6,-6,4,-6,-5,8,4,-6,-5,4,6,5,7,7,5,-6,5,-5,6,5,5,7,5,5,5,5,6,-5,-5,-8,-6,-7,5,-4,6,-5,-6,-5,5,-8,-4,-5,6,-7,5,5,6,-6,-6,-6,7,-5,-5,-6,5,-3,-5,-7,5,-6,-5,-6,7,6,-7,5,7,6,6,5,5,5,5,5,3,-6,6,-6,6,7,5,5,6,5,8,5,5,6,4,6,-7,
    4,6,6,6,6,-5,-4,-5,-7,-7,-5,-5,8,6,-8,-5,5,3,4,6,-5,-6,-3,5,7,6,6,7,-5,6,7,-6,5,-5,-6,5,5,-6,5,8,-4,5,5,5,7,6,-3,-7,7,-5,4,6,7,-5,4,6,7,6,4,5,4,-6,-6,-7,-6,6,-6,5,6,-6,6,-4,-7,4,-5,-4,5,6,4,-5,-7,5,-8,-5,-6,-6,-7,4,5,-6,6,5,5,5,5,-5,-6,-5,-6,-6,6,6,6,5,-5,6,6,5,6,-4,-6,-6,6,-6,5,7,6,-7,6,5,6,-6,-5,-3,7,-4,-6,-6,-7,4,3,6,7,-5,7,6,-4,-5,-5,-7,5,-6,-6,-4,-6,-5,-6,-5,-4,-7,-3,6,4,5,5,6,5,4,5,-6,-6,-7,-5,6,8,6,5,7,-6,5,-5,-5,-5,5,-7,-4,-6,-5,5,5,5,5,5,5,6,4,-3,-5,-8,-7,-8,-5,5,5,-6,6,4,4,-4,5,-6,-5,5,5,-4,6,4,-5,-5,-6,5,7,8,-6,-6,5,5,4,-4,-6,-3,5,5,-6,-5,6,-6,-4,4,-6,6,8,4,5,5,6,-5,-4,-6,-5,5,5,5,6,5,6,5,5,-6,-8,-6,-6,-6,-7,-4,-5,-4,-5,-7,-5,-4,-6,5,-6,-6,5,-6,-6,5,7,6,-5,-5,-5,-6,7,7,6,6,-7,8,7,-6,6,6,3,5,-7,7,-5,-6,-5,5,6,-5,-5,-5,7,-4,-4,-5,5,-4,-4,-5,5,-5,-4,-5,4,-5,-6,6,-5,-6,-5,6,-6,-6,-5,-4,7,5,-6,6,-5,5,-4,-4,-5,-5,5,3,6,7,-6,5,7,-6,6,7,3,5,-7,-7,-5,-6,4,8,6,6,-5,-5,-5,-5,-6,-4,-6,-6,-6,4,-6,-5,-4,6,-5,-6,-6,-6,6,-6,-5,-5,5,-5,-7,4,-5,-6,-6,6,-7,-5,-7,6,-6,5,5,-6,6,4,-6,7,4,5,6,6,-6,5,-6,6,-5,5,-6,-5,7,4,-7,-6,8,6,-4,-6,4,4,-5,5,5,-3,-5,6,-3,-6,-5,3,5,-4,-4,5,6,-7,-6,-6,-5,-5,-6,-5,-6,-3,-5,-5,-4,-7,-4,-5,-5,-5,-5,-6,-6,-6,5,-7,-6,7,-5,-4,5,6,-6,-6,6,5,-6,7,-5,6,-4,-5,7,7,-6,-4,5,6,-5,-5,5,6,-4,-7,6,-5,-5,-7,6,-5,-6,-5,-4,-5,-5,-4,-5,-5,-6,-7,-4,-5,-4,-6,-4,-6,-6,-5,-5,-6,-4,-6,-6,-7,5,-4,-5,-5,-6,-6,5,4,7,6,4,5,6,-8,-7,5,7,-4,-6,-6,-5,7,5,5,-5,-5,-6,-4,-6,6,-6,-5,5,-7,6,6,-6,-3,4,-5,-7,6,-5,-5,-7,-6,-5,5,5,-7,5,-5,-5,-5,7,-6,-7,-5,-5,-5,-5,-6,6,5,5,4,-4,5,-6,-3,6,-4,6,7,-6,4,5,-6,-6,-6,5,6,-6,5,4,6,7,5,-5,-5,6,-4,-6,-6,-5,-6,5,5,5,5,7,-7,-5,-5,-4,5,-5,-6,-6,-5,6,5,4,-6,3,-5,-5,-5,6,-5,-6,-6,6,5,5,-4,6,6,6,4,-6,-6,-5,-6,5,-5,-5,7,5,4,4,-6,6,6,5,7,7,6,4,6,4,2,-7,-7,-5,-5,-7,-4,-4,-6,6,7,7,6,-5,-6,-6,-4,-6,5,-7,5,5,5,-6,5,6,4,5,-5,-4,-5,-6,-4,-4,-7,-6,5,5,6,3,4,5,-3,-5,5,-6,-5,-3,6,-6,5,5,-5,-6,4,-6,-6,8,7,5,-7,-5,-6,5,5,-6,-6,-6,5,8,7,-4,-7,6,7,-6,5,6,-7,5,-6,-6,-5,-5,-5,-5,5,5,6,4,-5,-7,-5,-6,-4,-6,-7,-6,6,4,5,6,6,5,6,7,5,6,6,5,6,5,-6,5,7,-6,7,7,-4,-5,-5,5,7,6,5,-5,-7,-6,-5,5,-6,-5,7,-6,-7,-7,-6,3,-5,5,6,5,-6,-5,4,6,4,-7,6,5,5,-4,6,5,5,-5,5,6,5,-5,4,6,-6,6,5,5,-4,6,6,7,7,-5,-7,7,-5,7,-5,7,6,7,7,-6,-5,-4,-7,5,-7,-6,4,-5,-5,-6,-6,5,7,4,6,-5,-5,-5,-6,6,4,5,5,5,4,3,6,6,-5,6,5,4,-4,7,5,6,7,-5,4,6,4,-4,7,6,-6,5,5,4,-7,6,8,6,-7,4,-5,-4,5,-8,-5,5,-5,-7,-6,-5,-5,7,-6,7,-6,5,-4,5,5,-5,-5,6,7,-5,-6,5,7,-7,-7,6,-5,-5,7,6,-5,6,5,4,-6,-5,8,4,-6,-5,4,6,5,7,7,5,5,5,6,6,5,5,7,5,5,5,5,6,6,6,3,-6,4,5,-4,6,6,-6,-5,5,3,-4,-5,6,-7,5,-6,6,5,-6,-6,7,6,-5,-6,5,8,-5,-7,5,5,-5,5,7,6,-7,5,7,6,6,5,5,5,5,5,3,5,6,5,6,7,5,5,6,5,8,5,5,6,4,6,-7,

    }; 

    int64_t data_out[K] ;
    int8_t codw_out[codw_N*4] ; 
    
    //--------------
    // min arrays n-sys 
    // to int32_t
    int64_t     LLR[4*codw_N]  = {0}; 
    int64_t     PS[codw_N]     = {0};
    int64_t     decode[codw_N] = {0};


void reorder(int64_t* dest, const int8_t* src, int N) // a = sign, b = value
{
    int8_t* ptr = (int8_t*) dest;
    for (int32_t i=0; i<N; i++)
    {
        for (int32_t z = 0; z < 8; z+= 1)
        {
            ptr[(8*i) + z] = src[z * N + i];
        }
    }
}

void ireorder(int8_t* dest, int64_t* src, int N) // a = sign, b = value
{
    int8_t* ptr = (int8_t*) src;
    for (int32_t i = 0; i < N; i += 1)
    {
        for (int32_t j = 0; j < 8; j += 1)
        {
            dest[j * N + i] = ptr[8 * i + j];
        }
    }
}


int64_t func_g(int64_t sa,int64_t la,int64_t lb)
{
    // solutionée par l'utilisation du masquage mais demande de faire les 2 calculs .. 
    // modèle LDPC 

    int64_t eval ;   
    callEval(eval,sa,0) ;  

    int64_t v1=0;
    int64_t v2,vf ; 
    callSubSat(v2,lb,la) ; 

    v1 = v1 & ~eval ;
    v2 = v2 & eval ; 
    vf = v1 | v2 ; 

    return vf ; 
}


////////////////////////// 
// main func 
void node( int64_t* ptr_sum, int64_t *LLR , int N, int8_t *fz_bits,int64_t *decode)
{
    if( N == 1 )
    {

    
		callRinstr( *ptr_sum , *LLR , *fz_bits ); 
        callDecode(*decode,*ptr_sum,*fz_bits) ; 

        return;
    }
        // ON CALCULE LES F

        for( int x = 0 ; x < N/2; x += 1 )
        {    
            callFinstr( (LLR+N)[ x ] , LLR[ x ] , (LLR+N/2)[ x ] )  ; 
        }
 
        // ON CALCULE LA BRANCHE GAUCHE

        node( ptr_sum, (LLR+N), N/2, fz_bits,decode);

        // ON CALCULE LES G
        for( int x = 0;  x < N/2; x += 1 )
        {
            (LLR+N)[ x ] = func_g( ptr_sum[x] , LLR[ x ], (LLR+N/2)[ x ]) ; 
        }

        // ON CALCULE LA BRANCHE DROITE

        node( ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2, decode+N/2);
    
        // ON FAIT LES CALCUL DES H (XOR DES SP)

        for(int x = 0 ; x < N/2 ; x += 1 )
        {          
            ptr_sum[x] ^=ptr_sum[ x + (N/2) ];      
        }
}


int main() {


    long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 


    // 4 cycles pour sortir les infos 
	cycle_start= cycles()-4;
	insn_start = insn()-4; 

    reorder(LLR,codw_int,codw_N) ;
    node(PS,LLR, codw_N, froozen_bits,decode  );
    // exctract data bits from decode vector with fz_bits idxs 
    // PART OF THE DECODER 

    int j = 0 ; 
    for (int i = 0; i < codw_N; i++)
    {
        if(!froozen_bits[i])
        {
            data_out[j]=decode[i] ;
            j++ ;  
        }             
    }
    ireorder(codw_out,data_out,K) ; 

	cycle_stop= cycles()-4;
	insn_stop = insn()-4; 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 

	printf("cycles	: %d \n", cycle_tot) ; 
	printf("insn	: %d \n", insn_tot);
 

      // check resu ; 
for (int i = 0; i < codw_N*2; i++)
    {
        if(codw_out[i]!= U[i] )
            printf("E") ; 
        else 
            printf("-") ; 
         
    }
    
    printf("\n") ; 



    j= 0; 
    int cpt = 0 ; 
    for( int i=0 ; i < codw_N ; i++)
    {
        if( froozen_bits[i]==0 && U[j++]!=(decode[i]<<24)>>24  )
        {
            cpt++ ;
            printf(" %d ",i) ; 
        }
                          
    }

    printf("cpt : %d\n",cpt); 
    printf("\n") ;

    j= 0; 
    cpt = 0 ; 
    for( int i=0 ; i < codw_N ; i++)
    {
        if( froozen_bits[i]==0 && U[K+j++]!=(decode[i]<<16)>>24  )
        {
            cpt++ ;
            printf(" %d ",i) ; 
        }
                          
    }
    printf("cpt : %d\n",cpt); 
    printf("\n") ;


    j= 0; 
    cpt = 0 ; 
    for( int i=0 ; i < codw_N ; i++)
    {
        if( froozen_bits[i]==0 && U[(2*K)+j++]!=(decode[i]<<8)>>24  )
        {
            cpt++ ;
            printf(" %d ",i) ; 
        }
                          
    }
    printf("cpt : %d\n",cpt); 
    printf("\n") ;


    j= 0; 
    cpt = 0 ; 
    for( int i=0 ; i < codw_N ; i++)
    {
        if( froozen_bits[i]==0 && U[(3*K)+j++]!=(decode[i])>>24  )
        {
            cpt++ ;
            printf(" %d ",i) ; 
        }
                          
    }
    printf("cpt : %d\n",cpt); 
    printf("\n") ; 

  return 0;
}
