/*
apparament inline sans static devant doit etre
inclus dans le headern liée çà GCC et 
le linkage 


viré les inlines 
*/



#include "constantes.h"
#include "GF.h"
#include "hlayered.h"
#include <stdlib.h>

/*** prototypes **/ 
// n-simd inclus 

void hard_decision           (int GF, char DEST[],            unsigned char vars[]);
void symb_decision           (int GF, unsigned char  DEST[],  unsigned char vars[]);
int  syndrom                 (int GF, unsigned char decide[]);   
void zero                    (int SIZE, unsigned char dest[]);

void message                 (int GF, unsigned char dst[GF],  unsigned char src1[GF],    unsigned char src2[GF]);
void update                  (int GF, unsigned char dst[GF],  unsigned char src1[GF]);
void to_gf                   (int GF, unsigned char a[]);
void to_natural              (int GF, unsigned char a[]);
void divide                  (int GF, unsigned char a[],      const int alpha);
void multiply                (int GF, unsigned char a[], const int alpha);
void copy                    (int GF, unsigned char dst[], unsigned char src[]);
void normalize               (int GF, unsigned char a[], unsigned char value);
unsigned char find_min_pos   (int GF, unsigned char a[]);
unsigned char find_min       (int GF, unsigned char a[]);

// unsigned char min( unsigned char a , unsigned char b ); 



/****func declarations ***/ 


void hard_decision(int GF, char DEST[], unsigned char vars[])
{
    for (int n = 0; n < _NSYMBOL_; n++)
    {
        int symbol = find_min_pos(GF, vars + GF * n);
        for (int g=0; g<_LOG2GF_; g++){
            int value = GF_BINGF[symbol][g];
            DEST[_LOG2GF_ * n + g] = value;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void symb_decision(int GF, unsigned char DEST[ ], unsigned char vars[ ])
{
    for (int n = 0; n < _NSYMBOL_; n++){
        DEST[n] = find_min_pos(GF, vars + GF * n);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int syndrom (int GF, unsigned char decide[] )
{
    int synd = 0;
    const int* pNodes = LINK_NODES;
    const int* pAlpha = ALPHA;

    for (int k=0; k<_DEG_COMPUTATIONS_; k++){
        for (int l=0; l<_DEG_CN_; l++){
            const int alpha  = pAlpha[l];
            const int vn_pos = pNodes[l];
            const int symbol = decide[ vn_pos ];
            const int value  = GF_MUL[ alpha ][ symbol ];
            synd             = GF_ADD[ synd  ][ value  ];
        }
        if (synd != 0){
            break;
        }
        pNodes += _DEG_CN_;
        pAlpha += _DEG_CN_;
    }
    return (synd);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void zero(int SIZE, unsigned char dest[])
{
	for(int i=0; i<SIZE; i++){
		dest[i] = 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void message(int GF, unsigned char dst[GF], unsigned char src1[GF], unsigned char src2[GF])
{
	for(int i=0; i<GF; i++){
		const int msg = src1[i] - src2[i];
		src1[i] = msg;
		dst [i] = msg;
	}
}

/*
maxN, maxM => figées à 63dasn uchar , 64 dans le NB_int_avx 
*/
 void update(int GF, unsigned char dst[GF],  unsigned char src1[GF] )
{
	for(int i=0; i<GF; i++){
      #ifdef CST
      callAdd32sSat64(dst[i], dst[i], src1[i]);
      #else 
    	const int tmp = dst[i] + src1[i];
		dst [i] = tmp > 64 ? 64 : tmp;
      #endif
   }
}
/*
*/
 void to_gf(int GF, unsigned char a[])
{
	unsigned char tmp[GF];
   for(int i=0; i<GF; i++){
      tmp[ GF_N2S[i] ] = a[ i ];
   }
   copy(GF,a, tmp);
}
/*
*/
 void to_natural(int GF, unsigned char a[])
{
	unsigned char tmp[GF];
   for(int i=0; i<GF; i++){
      tmp[ GF_S2N[i] ] = a[ i ];
   }
   copy(GF,a, tmp);
}
/*
*/
 void divide(int GF, unsigned char a[], const int alpha)
{
   unsigned char tmp[GF];
   for(int i=0; i<GF; i++){
      const int symbol = i;
      const int dest   = GF_DIV[symbol][alpha];
      tmp[ dest ] = a[ i ];
   }
   copy(GF,a, tmp);
}

/*
*/
 void multiply(int GF, unsigned char a[], const int alpha)
{
	unsigned char tmp[GF];
   for(int i=0; i<GF; i++)
   {
   	const int symbol = i;
   	const int dest   = GF_MUL[symbol][alpha];
      tmp[ dest ] = a[ i ];
   }
   copy(GF,a, tmp);
}
/*
*/
 void copy(int GF, unsigned char dst[], unsigned char src[])
{
   for(int i=0; i<GF; i++){
	   dst [i] = src[i];
   }
}
/*
*/
 void normalize(int GF, unsigned char a[], unsigned char value)
{
   for(int i=0; i<GF; i++)
   {  
      #ifdef CST
      callSub32sSat64(a[i],a[i],value) ; 
      #else 
      const int diff = a[i] - value;
      a[i] = diff > 64 ? 64 : diff;
      #endif 
   }
}
/*
*/
 unsigned char find_min_pos(int GF, unsigned char a[])
{
	int pos = 0;
	int min = a[0];
	for(int i=1; i<_GF_; i++)
	{
	   if( min > a[i] )
	   {
	       min = a[i];
	       pos = i;
	   }
	}
   return pos ; 
}

/*
definir une fonction pour min 
*/
#ifndef CST
unsigned char min( unsigned char a , unsigned char b )
{
   return (a>b) ? b : a ; 
}
#endif 


unsigned char find_min(int GF, unsigned char a[])
{
   unsigned char min_ = a[0];
   for(int i=1; i<GF; i++)
   {
      #ifdef CST
      callMin(min_,min_,a[i]) ; 
      #else 
      min_ = min(min_, a[i]); 
      #endif 
   }  
   return min_;
}