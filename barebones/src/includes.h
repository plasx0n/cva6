/*
Core depedent 
    printf     
SIMD defines too 
could use abs () 
*/

// #define BASE_FUNC_32b
// #define EXT_FUNC_32b


// #define CUSTOM_BASE_FUNC_8b 
// à changer de nom 

// #include <stdio.h>
#include <stdint.h>

// HARD 
// rendement   0.500000 
// Eb_N0       1.400000 

#define codw_N 1024
#define K      512

/* table des noeuds */
char fb_table_tileN_origi[]={
4,4,4,2,4,2,4,4,0,4,0,4,4,4,0,4,4,4,3,4,4,4,0,4,0,4,0,4,4,4,2,4,2,4,4,4,2,4,4,4,1,4,4,4,2,4,2,4,4,4,4,3,4,3,1,4,4,4,4,3,4,3,1,1,4,4,4,4,2,4,2,4,2,4,4,4,2,4,2,4,4,4,4,3,4,3,1,4,4,4,4,0,4,4,4,3,4,4,4,3,4,3,1,4,4,4,4,1,1,1,4,4,4,4,4,2,4,4,4,3,4,4,4,1,1,4,4,4,3,1,1,1,4,4,4,4,3,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
};
char* fb_table_tileN = fb_table_tileN_origi ; 

int8_t froozen_bits[]={
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
int8_t U[]={
 1,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,0,0,1,0,0,1,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,1,1,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,1,
};
int8_t codw[]={
 0,9,-4,-1,11,0,1,-2,-12,-12,-2,7,7,7,-17,7,-8,-5,-12,-3,-4,-7,5,-10,0,-4,7,14,-4,9,11,-8,5,-2,3,5,3,-7,1,21,0,-7,-6,4,1,-2,5,-12,14,9,-1,10,0,-1,0,8,0,-2,-11,4,-11,-10,-8,-2,-7,10,2,-10,7,-9,-3,2,-14,-12,8,15,2,6,-14,7,-13,-9,-16,7,-6,4,0,0,3,-6,-1,3,-8,5,-8,10,5,0,2,-7,8,6,0,2,-4,11,-2,-7,-3,4,2,2,-5,-6,-10,14,-3,-11,-4,-8,-4,4,7,6,1,14,-10,-9,-1,0,-5,9,1,-3,2,10,1,9,7,-3,-8,-10,5,13,3,7,-8,-3,0,-1,17,-2,0,1,-6,8,-10,-12,-8,2,2,-12,8,6,9,-2,5,3,-6,5,6,7,-2,2,-12,13,-7,-5,-10,5,4,1,5,-9,-1,0,5,6,-18,-12,-18,11,5,-9,4,-4,-12,-11,1,3,-9,6,2,1,14,-5,-13,-3,8,-10,0,11,17,-8,4,-6,-6,-11,13,-8,6,-10,-9,-9,-4,-2,-7,11,-1,1,-5,6,-1,-9,1,6,10,13,-6,7,5,-7,3,0,4,8,-9,4,-6,-17,-8,-11,-9,-11,14,-5,14,6,-14,-2,15,3,-10,-7,-6,5,-6,2,-8,3,-3,-2,7,-1,-10,0,11,9,6,-16,5,2,2,-2,-4,-18,5,-13,12,10,-9,-4,2,7,9,-5,-3,0,14,0,7,3,12,12,6,-6,10,2,11,-13,10,-10,8,0,-6,10,-4,4,4,-3,0,0,-6,5,11,-3,-10,13,0,-5,-3,-7,-8,8,2,1,-6,1,4,8,0,-7,-11,0,-1,-3,-10,0,18,10,-4,10,9,7,11,-10,3,-7,-8,-6,-11,4,-4,1,-5,10,-6,-6,3,11,5,-3,8,-8,-2,-12,-2,0,5,3,-3,-15,7,-12,-5,4,3,3,5,6,-15,-7,0,0,-11,-3,10,0,-7,-6,-3,-1,2,-9,-5,4,-12,-1,5,20,-1,11,-7,-12,0,7,-9,2,19,-3,-2,9,2,10,-4,5,12,0,-9,-3,-4,-6,-6,9,-2,-8,-5,-8,17,10,-3,0,-14,16,-1,-1,10,-1,5,3,2,4,0,2,0,-1,3,4,10,-9,4,-4,-9,-10,2,-1,-4,13,-1,12,2,-6,1,5,7,-2,-5,5,-4,2,-2,-3,9,-5,-2,6,8,3,10,0,9,8,2,7,8,4,-13,0,-2,0,2,4,1,3,8,-2,5,16,-7,2,-11,5,4,7,-5,3,5,3,-13,0,11,-14,-8,0,-5,0,-6,11,12,-8,1,-3,11,2,5,-2,9,-7,0,-10,8,-8,8,-10,-3,10,10,-11,5,-2,8,-13,-5,8,-3,0,-8,-4,1,5,-3,-6,-2,7,-1,13,1,-12,-3,-4,10,9,1,0,4,5,-12,11,-7,-7,17,7,11,8,3,5,-12,-7,5,-7,5,-6,-5,-7,0,0,10,0,-6,-3,8,9,12,-7,-9,-3,-7,5,-6,5,-9,11,-3,8,-5,15,1,9,3,3,-3,0,-11,-2,-6,-7,-2,7,-4,7,-4,2,-11,9,4,-8,1,8,10,6,-15,3,0,-4,3,4,-1,11,12,5,-13,-14,-9,11,-1,-7,12,0,9,-3,10,-15,-24,0,-12,-5,6,-12,0,11,-7,-3,12,4,-4,-3,-9,-6,0,1,0,-14,-10,-7,-10,-9,-7,-4,0,-8,-3,0,7,1,0,3,0,-10,1,-10,9,-18,-2,2,16,-5,3,3,11,18,-5,5,-8,-6,-5,1,-14,-8,4,18,0,-6,0,9,-8,3,5,2,-10,-8,4,4,14,12,-1,-2,12,-6,5,10,-12,-8,-9,5,6,-5,-2,-5,4,-6,6,-16,-4,-14,6,-9,13,1,-12,-8,7,0,5,-4,-2,-8,6,0,-8,-3,-1,1,6,-6,-7,2,11,-7,14,16,2,10,-3,3,0,7,-6,-1,-11,4,10,2,2,-4,0,-7,-13,0,-10,-7,7,1,7,-10,-10,-5,-12,9,-15,-15,11,-7,-9,2,8,-8,5,8,-6,8,2,-5,-2,11,2,-3,-10,2,3,8,-4,0,0,7,-1,15,6,12,6,12,-3,1,0,-10,-3,12,0,2,-12,-9,-1,9,9,3,-7,5,14,-1,6,8,-2,-5,2,-3,-12,4,5,-8,-12,-18,7,-1,8,0,2,-4,12,0,-9,-1,11,-1,0,10,-4,2,1,6,4,-8,-7,-1,0,-1,5,7,-11,-1,-4,12,1,-6,11,-8,-1,-2,1,9,8,2,-7,14,0,-11,1,-8,-10,7,10,-3,14,6,-11,-7,0,-14,0,-4,7,6,2,6,9,7,-6,-4,4,-3,17,-11,-6,11,0,-5,-7,2,12,4,3,-9,10,-2,-8,-9,11,2,4,5,4,6,-2,9,-16,2,-3,4,13,-3,8,-8,-4,-6,-17,0,-5,6,-15,5,-6,-2,-6,-7,-11,13,6,-3,-11,-10,18,10,-1,-8,4,-1,-8,0,6,0,3,13,0,-3,0,1,-6,-9,-9,-5,-10,6,4,-2,0,-10,-9,9,0,4,-6,-10,-5,-12,10,-13,
};



/* TEST FUNCS */ 
/*call les instrus customs 8b*/
// #ifdef CUSTOM_BASE_FUNC_8b

#define callRinstr(a,b,c) asm volatile("pl.r %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callFinstr(a,b,c) asm volatile("pl.f %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callSubSat(a,b,c) asm volatile("pl.subsat %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 
                                
#define callAddbSat(a,b,c) asm volatile("pl.addsat %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 


/* Basic Functions SC Float and 32 bits */ 
#ifdef BASE_FUNC_32b

    #include <math.h>

    float func_f(float la,float lb)
    {
        float min1 , min2 ; 
        int sign = 0 ; 

        min1 = abs(la) ; 
        min2 = abs(lb) ;

        if(min1>min2) min1=min2 ; 
        sign = (la < 0) ^ (lb < 0) ; 

        return (sign == 0 )? min1 : -min1 ; 

    }

    int func_r(float la,int  froozen)
    {
        if(froozen)
        {
            return 0 ;    
        }
        else 
        {
            return (la < 0) ; 
        }
    }

    float func_g(int sa,float la,float lb)
    {
        return ( (1-2*sa)*la+lb ) ; 
    }

    int func_h(int sa,int sb)
    {
        return sa^sb; 
    }

#endif 

/* Extended Functions SC Float and 32 bits */ 
#ifdef EXT_FUNC_32b

    void node_8(int* ptr_sum, float *LLR , int N, char *fz_bits)
    { 
        if( N == 1 )
        {     
            *ptr_sum = func_r(*LLR, *fz_bits ); 
            return;
        }

        for( int x = 0 ; x < N/2; x += 1 )
            (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
    
        // ON CALCULE LA BRANCHE GAUCHE
        node_8(ptr_sum, (LLR+N), N/2, fz_bits);

        // ON CALCULE LES G
        for( int x = 0;  x < N/2; x += 1 )
        {
            (LLR+N)[ x ] = func_g( ptr_sum[x] ,LLR[ x ], (LLR+N/2)[ x ]) ; 
        }

        // ON CALCULE LA BRANCHE DROITE
        node_8(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
        
        // ON FAIT LES CALCUL DES H (XOR DES SP)
        for(int x = 0 ; x < N/2 ; x += 1 )
        {          
            ptr_sum[x] = func_h( ptr_sum[x], ptr_sum[ x + (N/2) ]); 
        }
    }

    void node(int* ptr_sum, float *LLR , int N, char *fz_bits)
    {
        // ON CALCULE LA BRANCHE GAUCHE
        // get the node status 
        char enab1 = *fb_table_tileN++  ; 

        if(enab1==0) // r0 
        {
            // update res with G 
            for( int x = 0;  x < N/2; x += 1 )
            {
                (LLR+N)[ x ] = func_g( ptr_sum[x] ,LLR[ x ], (LLR+N/2)[ x ]) ; 
            }

        }else if (enab1==1) // r1 
        {
            // ON CALCULE LES F
            for( int x = 0 ; x < N/2; x += 1 )
            {
                (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                // possible opti de boucle 
                ptr_sum[x] = func_r((LLR+N)[x], 0 ); 
            }

            // update Res with G 
            for( int x = 0;  x < N/2; x += 1 )
            {
                (LLR+N)[ x ] = func_g( ptr_sum[x] ,LLR[ x ], (LLR+N/2)[ x ]) ; 
            }

        }else if (enab1==2) // REP
        {
            // Somme des LLR 
            // x > 0 ? PS => 0 
            // x < 0 ? PS => 1 

            // ON CALCULE LES F
            float tot = 0 ; 
            for( int x = 0 ; x < N/2; x += 1 )
            {
                
                (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                tot += (LLR+N)[x] ;
            }

            if(tot < 0 )
            {
                for( int x = 0 ; x < N/2; x += 1 )
                    ptr_sum[x] = 1 ; 
            } 

            // update Res with G for next node 
            for( int x = 0;  x < N/2; x += 1 )
            {
                (LLR+N)[ x ] = func_g( ptr_sum[x] ,LLR[ x ], (LLR+N/2)[ x ]) ; 
            }


        } else if (enab1==3 ) // SPC 
        {

            int sign=0;
            float mina = 1000 , minb=1000 ; 
            int idx_min= 0 ; 
            for( int x = 0 ; x < N/2; x += 1 )
            {
                
                (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                // possible opti de boucle 
                // force r1 
                ptr_sum[x] = func_r((LLR+N)[x], 0 ); 
                // parité on the fly 
                sign ^= ptr_sum[x] ; 

                float a = fabs((LLR+N)[ x ]) ; 

                if(a < mina)
                {
                    minb = mina;
                    mina = a;
                    idx_min = x ; 
                }else if(a < minb) // min1 < a < min2
                    minb = a  ;
            }
                
            // printf("sign %d min %f  idx %d " ,sign,  mina,idx_min); 
            ptr_sum[idx_min]^=sign ;

            // update Res with G for next node 
            for( int x = 0;  x < N/2; x += 1 )
            {
                (LLR+N)[ x ] = func_g( ptr_sum[x] ,LLR[ x ], (LLR+N/2)[ x ]) ; 
            }


        } else // opération normale 
        {   
            if((N/2)==8){                          
                                    
                // ON CALCULE LES F
                for( int x = 0 ; x < N/2; x += 1 )
                {
                    (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                }

                // Recursif Node_8 
                node_8( ptr_sum, (LLR+N), N/2, fz_bits) ; 

                // ON CALCULE LES G
                for( int x = 0;  x < N/2; x += 1 )
                {
                    (LLR+N)[ x ] = func_g( ptr_sum[x] ,LLR[ x ], (LLR+N/2)[ x ]) ; 
                }
            }
            else{
                // ON CALCULE LES F
                for( int x = 0 ; x < N/2; x += 1 )
                {

                    (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                }
                
                node( ptr_sum, (LLR+N), N/2, fz_bits);
                    
                // ON CALCULE LES G
                for( int x = 0;  x < N/2; x += 1 )
                {
                    (LLR+N)[ x ] = func_g( ptr_sum[x] ,LLR[ x ], (LLR+N/2)[ x ]) ; 
                }
            }
            
        }
            

        // ON CALCULE LA BRANCHE DROITE
        // get the node status 
        char enab2 = *fb_table_tileN++  ; 
        
        if(enab2==0) // r0 
        {
            //gestion de ptr ... 

        }else if (enab2==1) // r1 
        {
            // copy leaf calc to PS  
            for( int x = 0 ; x < N/2; x += 1 )
            {
                // +N puisque ne saute pas dans un nouveau node 
                // force r0 
                (ptr_sum+N/2)[x] = func_r( (LLR+N)[x], 0 );
            }

        }else if (enab2==2) // REP
        {
            // Somme LLRS et PS update 
            float tot = 0 ; 
            for (int x = 0; x < N/2; x++)
                tot += (LLR+N)[x] ; 

            if(tot <= 0 )
            {
                for( int x = 0 ; x < N/2; x += 1 )
                    (ptr_sum+N/2)[x] = 1 ; 
            } 
        }
        else if (enab2==3) // SPC
        {
            // printf("\n SPC droit \n "); 
            // parité + sign 
            int sign=0 ; 
            float mina = 1000 , minb=1000 ; 
            int idx_min= 0 ; 
            for( int x = 0 ; x < N/2; x += 1 )
            {
                // +N puisque ne saute pas dans un nouveau node 
                // force R1 (ne tiens pas compte des bits gelés )
                (ptr_sum+N/2)[x] = func_r( (LLR+N)[x], 0 );
                sign ^= (ptr_sum+N/2)[x] ; 
                float a = fabs((LLR+N)[ x ]) ; 
                
                if(a < mina)
                {
                    minb = mina;
                    mina = a;
                    idx_min = x ; 
                }else if(a < minb) // min1 < a < min2
                    minb = a  ;
            }
                
            // printf("sign %d min %f  idx %d " ,sign,  mina,idx_min);
            ptr_sum[idx_min]^=sign ;
        }
            
        else // opération normale 
        {
            if( (N/2)==8 ){
                node_8(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
            }else{
                node(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
            }
        }  

        // ON FAIT LES CALCUL DES H (XOR DES SP)
        for(int x = 0 ; x < N/2 ; x += 1 )
        {          
            ptr_sum[x] = func_h( ptr_sum[x], ptr_sum[ x + (N/2) ]);    
        }
    }

    // calcule unqiuement le premier f ,  g  et le dernier Xor(h)
    void node_top(int* ptr_sum, float *LLR , int N, char *fz_bits)
    {

        // if (*fb_table_tileN != 4) {
        //     printf("(EE) TOP LEVEL TILE IS FROZEN !\n");
        //     exit(0);
        // }

        fb_table_tileN+=1 ; 

        // une fois F pr la branche gauche 
        for( int x = 0 ; x < N/2; x += 1 )
        {
            (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ;
        }

        // tt la branche gauche 
        const int not_frozen_value = 4;
        if (*fb_table_tileN++ != not_frozen_value) {
            printf("(EE) Un truc impossible vient de se produire (1:%d)\n", *(fb_table_tileN-1));
            exit( 0 );
        } else {
            node( ptr_sum, (LLR+N), N/2, fz_bits);
        }

        // une fois G pour la branche droite   
        for( int x = 0;  x < N/2; x += 1 )
        {
            // PS sont dispo
            (LLR+N)[ x ] = func_g( ptr_sum[x] ,LLR[ x ], (LLR+N/2)[ x ]) ; 
        }

        // tt la branche droite 
        if (*fb_table_tileN++ != not_frozen_value) {
            printf("(EE) Un truc impossible vient de se produire (1:%d)\n", *(fb_table_tileN-1));
            exit( 0 );
        } else {
            node( ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
        }

        // ON FAIT LES CALCUL DES H (XOR DES SP)
        for(int x = 0 ; x < N/2 ; x += 1 )
        {          
            // xor
            ptr_sum[x] = func_h( ptr_sum[x], ptr_sum[ x + (N/2) ]); 
        }

    }
#endif 

/* Basic Functions 8 and 16 bits RV */ 
#ifdef BASE_FUNC_8b

        int8_t func_f(int8_t la,int8_t lb)
        {
            int8_t min1 , min2 ; 
            int8_t sign = 0 ; 

            min1 = abs(la) ; 
            min2 = abs(lb) ;
            
            if(min1>min2) min1=min2 ; 
            sign = (la < 0) ^ (lb < 0) ; 

            return (sign == 0 )? min1 : -min1 ; 
        }
        

        int8_t func_r(int8_t la,char froozen)
        {
            if(froozen)
            {
                return 0 ;   
            }
            else 
            {
                return (la < 0) ; 
            }
        }

        int8_t sat( int16_t val)
        {
            // evaluation uniquement sur G en 16 bits 

            if( val >= 127 )
                return 127 ; 
            else if( val <= -127)
                return -127 ; 
            else 
                return val ;
        }
        #ifndef CUSTOM_BASE_FUNC_8b
        int16_t func_g(int8_t sa,int8_t la,int8_t lb)
        {
            if ( sa==0 )
            {
                return la+lb ; 
            }
            else
            { 
                return lb-la ; 
            }
        }
        #endif

   
    /* custom fonction G , doublon volontaire pour tests */ 
    #ifdef CUSTOM_BASE_FUNC_8b
    int8_t func_g(int8_t sa,int16_t la,int16_t lb)
    {
        int8_t res ; 
        /* 
            int16_t aprime = sa ? -la : la ; 
            callAddbSat(res,lb,aprime); 
        */
        // provide better cycle count ( less insn)
        if ( sa==0 )
        {    
            callAddbSat(res,la,lb);
        }
        else
        { 
            callSubSat(res,lb,la) ; 
        }
        return res ;
    }
    #endif
#endif

/* Extended Functions 8 and 16 bits RV */ 
#ifdef EXT_FUNC_8b

    void node_8(int8_t* ptr_sum, int8_t *LLR , int N, char *fz_bits)
    { 
        if( N == 1 )
        {     
            #ifdef CUSTOM_BASE_FUNC_8b
                callRinstr(*ptr_sum,*LLR, *fz_bits);
            #else 
                *ptr_sum = func_r(*LLR, *fz_bits ); 
            #endif 

            return;
        }

        for( int x = 0 ; x < N/2; x += 1 )
        {
            #ifdef CUSTOM_BASE_FUNC_8b
                callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
            #else 
                (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ;
            #endif 
        }

            
        // ON CALCULE LA BRANCHE GAUCHE
        node_8(ptr_sum, (LLR+N), N/2, fz_bits);

        // ON CALCULE LES G
        for( int x = 0;  x < N/2; x += 1 )
        {
            #ifdef CUSTOM_BASE_FUNC_8b
                (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;
                // printf( "Res %d  ( %d, %d , %d ) \n", (LLR+N)[ x ],  ptr_sum[x], (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]  ) ;

            #else 
                int16_t temp = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ; 
                (LLR+N)[ x ] =sat( temp)  ;  
            #endif 
        }

        // ON CALCULE LA BRANCHE DROITE
        node_8(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
        
        // ON FAIT LES CALCUL DES H (XOR DES SP)
        for(int x = 0 ; x < N/2 ; x += 1 )
        {          
            ptr_sum[x] ^=ptr_sum[ x + (N/2) ]; 
        }
    }


    void node(int8_t* ptr_sum, int8_t *LLR , int N, char *fz_bits)
    {
        // ON CALCULE LA BRANCHE GAUCHE
        // get the node status 
        char enab1 = *fb_table_tileN++  ; 

        if(enab1==0) // r0 
        {
            // update res with G 
            for( int x = 0;  x < N/2; x += 1 )
            {
                #ifdef CUSTOM_BASE_FUNC_8b
                (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;
            
                #else 
                int16_t temp = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ; 
                (LLR+N)[ x ] =sat( temp)  ;  
                #endif 
            }

        }else 
        if (enab1==1) // r1 
        {
            // ON CALCULE LES F
            for( int x = 0 ; x < N/2; x += 1 )
            {
                #ifdef CUSTOM_BASE_FUNC_8b
                    // opti avec pointeur sur (LLR+N)[ x ] ?? 
                    callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
                    callRinstr(ptr_sum[x],(LLR+N)[x], 0);

                #else 
                    (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                    ptr_sum[x] = func_r((LLR+N)[x], 0 ); 
                #endif 
            }

            // update Res with G 
            for( int x = 0;  x < N/2; x += 1 )
            {
                #ifdef CUSTOM_BASE_FUNC_8b
                    (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;
                
                #else 
                    int16_t temp = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ; 
                    (LLR+N)[ x ] =sat( temp)  ;  
                #endif 
            }

        }else 
        if (enab1==2) // REP
        {
            // Somme des LLR 
            // x > 0 ? PS => 0 
            // x < 0 ? PS => 1 

            // ON CALCULE LES F
            int tot = 0 ; 
            for( int x = 0 ; x < N/2; x += 1 )
            {
                #ifdef CUSTOM_BASE_FUNC_8b
                callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
                #else
                (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                #endif 
                tot += (LLR+N)[x] ;
            }

            if(tot < 0 )
            {
                for( int x = 0 ; x < N/2; x += 1 )
                    ptr_sum[x] = 1 ; 
            } 

            // update Res with G for next node 
            for( int x = 0;  x < N/2; x += 1 )
            {
                #ifdef CUSTOM_BASE_FUNC_8b
                (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;
                
                #else 
                int16_t temp = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ; 
                (LLR+N)[ x ] =sat( temp)  ;  
                #endif 
            }


        } else 
        if (enab1==3 ) // SPC 
        {

            int8_t sign=0;
            int mina = 100  ;
            int8_t idx_min= 0 ; 
            for( int x = 0 ; x < N/2; x += 1 )
            {
                #ifdef CUSTOM_BASE_FUNC_8b
                callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
                callRinstr(ptr_sum[x],(LLR+N)[x], 0);
                #else 
                (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                ptr_sum[x] = func_r((LLR+N)[x], 0 ); 
                #endif 
                
                sign ^= ptr_sum[x] ; 

                int a = abs((LLR+N)[ x ]) ; 

                if(a < mina)
                {
                    mina = a;
                    idx_min = x ; 
                }
            }
                
            // printf("sign %d min %f  idx %d " ,sign,  mina,idx_min); 
            ptr_sum[idx_min]^=sign ;

            // update Res with G for next node 
            for( int x = 0;  x < N/2; x += 1 )
            {
                #ifdef CUSTOM_BASE_FUNC_8b
                (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;
                
                #else 
                int16_t temp = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ; 
                (LLR+N)[ x ] =sat( temp)  ;  
                #endif 
            }


        } 
        else // opération normale 
        {   
            // if ici permet de mieux dérouler le code afterwards ( reduc insn reduc cycles ) ? 
            if((N/2)==8){                          
                                    
                // ON CALCULE LES F
                for( int x = 0 ; x < N/2; x += 1 )
                {
                    #ifdef CUSTOM_BASE_FUNC_8b
                    callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
                    #else
                    (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                    #endif
                }

                // Recursif Node_8 
                node_8( ptr_sum, (LLR+N), N/2, fz_bits) ; 

                // ON CALCULE LES G
                for( int x = 0;  x < N/2; x += 1 )
                {
                    #ifdef CUSTOM_BASE_FUNC_8b
                    (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;
                    
                    #else 
                    int16_t temp = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ; 
                    (LLR+N)[ x ] =sat( temp)  ;  
                    #endif 
                }
            }
            else{
                // ON CALCULE LES F
                for( int x = 0 ; x < N/2; x += 1 )
                {
                    #ifdef CUSTOM_BASE_FUNC_8b
                    callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
                    #else
                    (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
                    #endif
                }
                
                node( ptr_sum, (LLR+N), N/2, fz_bits);
                    
                // ON CALCULE LES G
                for( int x = 0;  x < N/2; x += 1 )
                {
                    #ifdef CUSTOM_BASE_FUNC_8b
                    (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;
                    
                    #else 
                    int16_t temp = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ; 
                    (LLR+N)[ x ] =sat( temp)  ;  
                    #endif 
                }
            }
            
        }
            

        // ON CALCULE LA BRANCHE DROITE
        // get the node status 
        char enab2 = *fb_table_tileN++  ; 
        
        if(enab2==0) // r0 
        {
            //gestion de ptr ... 

        }else 
        if (enab2==1) // r1 
        {
            // copy leaf calc to PS  
            for( int x = 0 ; x < N/2; x += 1 )
            {
                #ifdef CUSTOM_BASE_FUNC_8b
                callRinstr((ptr_sum+N/2)[x],(LLR+N)[x], 0);
                #else 
                // +N puisque ne saute pas dans un nouveau node 
                // force r1 
                (ptr_sum+N/2)[x] = func_r( (LLR+N)[x], 0 );
                #endif
            }

        }else 
        if (enab2==2) // REP
        {
            // Somme LLRS et PS update 
            int tot = 0 ; 
            for (int x = 0; x < N/2; x++)
                tot += (LLR+N)[x] ; 

            if(tot <= 0 )
            {
                for( int x = 0 ; x < N/2; x += 1 )
                    (ptr_sum+N/2)[x] = 1 ; 
            } 
        }else 
        if (enab2==3) // SPC
        {
            // printf("\n SPC droit \n "); 
            // parité + sign 
            int8_t sign=0 ; 
            int mina = 100  ; 
            int8_t idx_min= 0 ; 
            for( int x = 0 ; x < N/2; x += 1 )
            {

                #ifdef CUSTOM_BASE_FUNC_8b
                callRinstr((ptr_sum+N/2)[x],(LLR+N)[x], 0);
                #else 
                // +N puisque ne saute pas dans un nouveau node 
                // force R1 (ne tiens pas compte des bits gelés )
                (ptr_sum+N/2)[x] = func_r( (LLR+N)[x], 0 );
                #endif 
                
                sign ^= (ptr_sum+N/2)[x] ; 
                int a = abs((LLR+N)[ x ]) ; 
                
                if(a < mina)
                {	
                    mina = a;
                    idx_min = x ; 
                }
            }
                
            // printf("sign %d min %f  idx %d " ,sign,  mina,idx_min);
            ptr_sum[idx_min]^=sign ;
        }       
        else // opération normale 
        {
            if( (N/2)==8 ){
                node_8(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
            }else{
                node(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
            }
        }  

        // ON FAIT LES CALCUL DES H (XOR DES SP)
        for(int x = 0 ; x < N/2 ; x += 1 )
        {          
            ptr_sum[x] ^=ptr_sum[ x + (N/2) ];    
        }
    }

    // calcule unqiuement le premier f ,  g  et le dernier Xor(h)
    void node_top(int8_t* ptr_sum, int8_t *LLR , int N, char *fz_bits)
    {

        // if (*fb_table_tileN != 4) {
        //     printf("(EE) TOP LEVEL TILE IS FROZEN !\n");
        //     exit(0);
        // }

        fb_table_tileN+=1 ; 

        // une fois F pr la branche gauche 
        for( int x = 0 ; x < N/2; x += 1 )
        {
            #ifdef CUSTOM_BASE_FUNC_8b
                callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
            #else
                (LLR+N)[ x ] = func_f( LLR[ x ], (LLR+N/2)[ x ]) ; 
            #endif
        }

        // tt la branche gauche 
        const int not_frozen_value = 4;
        if (*fb_table_tileN++ != not_frozen_value) {
            printf("(EE) Un truc impossible vient de se produire (1:%d)\n", *(fb_table_tileN-1));
            
        } else {
            node( ptr_sum, (LLR+N), N/2, fz_bits);
        }

        // une fois G pour la branche droite   
        for( int x = 0;  x < N/2; x += 1 )
        {
            #ifdef CUSTOM_BASE_FUNC_8b
            (LLR+N)[ x ] = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ;

            #else 
            int16_t temp = func_g( ptr_sum[x] , (int16_t) LLR[ x ], (int16_t) (LLR+N/2)[ x ]) ; 
            (LLR+N)[ x ] =sat( temp)  ;  
            #endif 
        }

        // tt la branche droite 
        if (*fb_table_tileN++ != not_frozen_value) {
            printf("(EE) Un truc impossible vient de se produire (1:%d)\n", *(fb_table_tileN-1));
            
        } else {
            node( ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
        }

        // ON FAIT LES CALCUL DES H (XOR DES SP)
        for(int x = 0 ; x < N/2 ; x += 1 )
        {          
            // xor
            ptr_sum[x] ^=ptr_sum[ x + (N/2) ]; 
        }

    }

#endif 