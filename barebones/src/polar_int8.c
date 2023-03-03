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

                            
// PARAMETERS 
#define codw_N 1024
#define K codw_N/2
// ds le heap 
    int8_t froozen_bits[]={
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };
    int8_t U[]={
    1,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,0,0,1,0,0,1,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,1,1,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,1,
    };
    int8_t codw_int[]={
    4,6,6,-5,6,6,-4,-5,4,4,6,6,8,6,-8,6,-6,-8,-7,-5,6,5,8,5,7,6,6,-4,-5,-5,-4,-6,5,-5,5,5,-6,-6,-6,-3,-4,-6,5,-6,-4,6,-3,4,-4,6,4,6,7,6,-7,6,7,-5,4,5,-7,5,5,4,-6,-5,5,5,6,5,-5,7,4,-7,6,7,5,-6,4,-5,-7,-6,3,-5,-6,5,-7,-7,5,-6,6,5,5,5,5,-5,-6,-5,-6,-6,6,-5,-5,5,6,6,-5,-6,6,-4,5,-6,6,5,-6,-4,6,-7,6,5,6,5,6,8,-4,7,-6,5,-7,4,3,-5,7,-5,7,6,7,-5,6,-7,-6,-6,-6,-4,5,-5,5,6,-4,4,8,-5,-7,5,-6,6,-6,4,-6,5,-6,4,6,-5,8,-5,-6,7,5,5,6,-5,6,5,4,-4,5,-5,-6,5,5,5,6,-6,6,4,8,-5,-8,4,3,6,-6,-6,-6,6,-7,-7,-4,5,5,6,5,5,7,-5,-7,6,6,5,5,-4,8,-6,-6,-6,5,4,7,-6,8,-6,-6,-6,-5,6,-6,-4,4,5,-6,-3,4,5,5,-6,-5,7,6,-5,6,5,-6,6,-6,-5,5,-6,5,3,5,-6,5,4,7,-5,-4,6,-7,6,7,-6,-6,-6,-6,5,-6,-6,5,-4,6,-5,-5,-5,5,-4,7,-5,6,-7,-3,-4,5,-5,6,-8,5,4,-4,6,-6,6,5,-5,6,6,-5,7,7,-4,6,-6,-4,7,6,-6,-5,7,-4,-7,6,5,6,-5,5,6,6,5,-6,-5,7,-4,5,6,6,6,-6,7,-4,6,-5,5,-8,6,7,-6,-6,7,5,-5,7,3,-6,4,-7,-5,5,-7,-3,6,6,6,-5,-5,6,-6,-4,-6,-6,-6,4,5,6,7,-5,6,-6,5,5,6,-6,-5,-5,5,-5,4,-7,-5,5,-6,6,4,6,-7,6,-6,5,5,-6,-5,-7,-6,7,-7,-6,6,6,5,5,-6,6,6,-6,5,6,-4,4,4,5,8,6,-4,5,4,4,6,5,5,8,6,-5,8,-6,6,3,-6,-4,-4,-6,-5,4,-6,5,-5,-5,-6,-5,5,8,-5,-5,7,4,-4,6,-5,6,6,-6,5,5,5,4,-6,7,6,7,-6,-5,5,-6,6,-6,-6,7,6,6,-4,-5,7,-4,-6,-4,6,-5,-5,-5,5,-5,-4,4,-5,-5,-6,4,-6,6,5,6,-4,-5,-5,-4,6,-5,5,4,-4,6,7,-6,7,-6,5,-5,-5,5,-4,5,-6,4,6,-4,-5,-6,5,-6,-6,4,7,-5,-7,-6,-5,-8,-7,5,-4,7,5,5,6,-4,-6,-6,-5,-5,-6,-4,5,6,5,6,5,-7,6,-5,-6,8,4,6,4,6,6,-5,4,5,-5,5,-6,4,-6,-5,-5,-5,-4,5,-7,-5,6,-5,-5,5,-5,-6,-6,4,7,-6,-6,-3,-5,7,-5,-4,5,-7,-6,-6,5,-6,5,6,5,-7,4,6,-4,5,6,-5,6,-4,-6,-6,-5,-6,5,5,5,5,7,-7,6,6,-4,-6,-5,5,5,-5,6,-7,4,-6,-8,6,6,-5,6,-5,-6,-6,-5,-6,-6,7,-5,6,-5,4,-6,-6,6,-6,5,-5,-5,-4,5,-7,4,5,6,6,5,-4,7,-5,-7,6,-7,-9,4,4,-6,6,-7,7,-4,5,-5,7,-4,-5,6,-6,5,7,-6,-6,-7,-6,5,-6,-6,-6,6,-7,5,6,-4,-5,-6,-4,7,-7,-6,-6,5,6,-8,-7,-6,7,6,5,-6,6,8,6,-6,-6,-6,-5,-6,-7,5,5,-3,-4,-6,-7,6,-6,5,6,5,-6,-6,-6,8,-4,7,4,6,7,-6,5,6,-7,-6,5,5,-5,-5,-5,6,5,-6,-5,4,-5,-7,6,-6,7,5,-7,5,-5,-7,-6,6,-5,-6,-5,7,5,-5,6,-6,-5,5,5,5,7,-6,7,7,-4,6,-5,5,7,6,-6,6,-7,5,-5,5,5,6,-4,5,-7,4,-6,-8,6,-6,6,-6,-6,6,-7,-5,4,-7,-5,5,-6,7,6,-6,-6,6,5,-5,5,6,-7,-5,-6,6,-6,-6,-4,-5,6,7,-4,6,-7,-4,-6,-4,6,-4,6,-4,7,-6,6,-4,-7,5,4,-6,-7,6,-5,-6,5,-6,7,4,-5,6,6,-5,-6,-5,4,5,-6,5,4,3,6,6,-5,-5,-6,-7,7,-4,5,-5,-4,-5,4,6,4,-4,7,-6,5,5,-6,4,-7,-5,-3,6,-7,4,-5,-4,5,3,6,5,-5,4,5,-5,-5,-4,-6,7,-6,-6,7,-6,-6,6,-5,-5,-4,-5,-6,5,-4,-7,-7,-5,-5,-5,-4,-6,6,-5,5,-7,-6,6,8,4,6,6,-7,6,-6,7,7,5,5,-6,-5,6,5,-6,-4,5,-6,5,-6,-5,6,-5,-8,-6,-7,5,-4,-5,-5,5,6,-6,3,-4,6,6,-7,-6,-6,6,5,-6,5,7,6,-5,5,5,8,-5,4,5,-6,6,5,7,-5,4,-6,-4,-4,6,5,5,5,-6,5,-8,-6,6,-6,-5,7,-6,5,-5,5,8,-6,5,-6,4,-5,-7,
    };

    //--------------
    // min arrays n-sys 
    int8_t    LLR[2*codw_N]   = {0}; 
    int8_t     PS[codw_N]     = {0};
    int8_t     decode[codw_N] = {0};


// low level polar funcs


int16_t func_g(int8_t sa,int8_t la,int8_t lb)
{
    int8_t res ; 
    if ( sa==0 )
    {    
        callAddSat(res,la,lb);
    }
    else
    { 
        callSubSat(res,lb,la) ; 
    }
    return res ;
}


////////////////////////// 
// main func 

void node( int8_t* ptr_sum, int8_t *LLR , int N, int8_t *fz_bits,int8_t *decode)
{
    if( N == 1 )
    {
        
		callRinstr(*ptr_sum,*LLR, *fz_bits ); 
        if ( *fz_bits == 0 )
			*decode = *ptr_sum ;
		else
			*decode = 0;

        return;
    }
        // ON CALCULE LES F

        for( int x = 0 ; x < N/2; x += 1 )
        {
            callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;  
        }
 
        // ON CALCULE LA BRANCHE GAUCHE

        node( ptr_sum, (LLR+N), N/2, fz_bits,decode);

        // ON CALCULE LES G
        for( int x = 0;  x < N/2; x += 1 )
        {
            (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;
            printf("sa %d rs1 %d rs2 %d res %d\n" , ptr_sum[x] , LLR[ x ], (LLR+N/2)[ x ] , (LLR+N)[x] );

        }

        // ON CALCULE LA BRANCHE DROITE

        node( ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2, decode+N/2);
    
        // ON FAIT LES CALCUL DES H (XOR DES SP)

        for(int x = 0 ; x < N/2 ; x += 1 )
        {          
            ptr_sum[x] ^=ptr_sum[ x + (N/2) ];      
        }
}


int main(int argc, char **argv) {

for( int i = 0 ; i < codw_N ; ++i)
	LLR[i] =(int8_t) codw_int[i] ; 

    long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 


    // 4 cycles pour sortir les infos 
	cycle_start= cycles()-4;
	insn_start = insn()-4; 

    node(PS, LLR, codw_N, froozen_bits,decode  );

	cycle_stop= cycles()-4;
	insn_stop = insn()-4; 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 

	printf("cycles	: %d \n", cycle_tot) ; 
	printf("insn	: %d \n", insn_tot);
 

      // check resu ; 
    int j= 0; 
    int cpt = 0 ; 
    for( int i=0 ; i < codw_N ; i++)
    {
        if( froozen_bits[i]==0 && U[j++]!=decode[i]  )
            cpt++ ;              
    }

    printf(" %d",cpt) ; 

  return 0;
}