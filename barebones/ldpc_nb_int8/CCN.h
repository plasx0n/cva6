
#include "GF.h"
#include "hlayered.h"
#include "constantes.h"
#include <stdlib.h>


/*
Fonctions ECN s

process uniquement les ECNS à partir des messages entrants 
message entrant ==> copiés depuis le decodeur 

*/
#define SAT_VALUE 127

struct CCN_struct
{
	/* data */
   	// inchangées 
	int degree ;
    int nECNs  ;
    int size ; 

	// equivalent dual tab ? ==> 4 messages entrants composés de 4 symboles en GF  
   	unsigned char** ecns; //ptr de tableau  : ecns est déja en ptr puisque tab (ptr -> ptr tab -> var uchar )
   	unsigned char** _msgs;

	// unsigned char* ecns[nECNs] ;
	// unsigned char* _msgs[degree] ;
}CCN;


// ECN min_sum GF64 DegCN_4 
void process_ecn(int gf, const unsigned char a[], const unsigned char b[], unsigned char r[])
{
	// printf("MinSumNatFixedAvx2<%d>::process( )\n", gf);
   	//	assert( false );
	for(unsigned int j=0; j<gf; j++)
	{
		r[j] = a[0] + b[j];
	}
	for(unsigned int i=1; i<gf; i++)
	{
		for(unsigned int j=0; j<gf; j++)
		{
			const unsigned int p    = i ^ j;
		
			#ifdef CST
			unsigned int sumS ; 
			callAdd32uSat64(sumS,(unsigned int)a[i],(unsigned int)b[j]) ; 
			callMin(r[p] , sumS,r[p]) ; 
			#else
			const unsigned int sum  = (unsigned int)a[i] + (unsigned int)b[j];
			const unsigned int sumS = sum > 63 ? 63 : sum;
			r[p] = (sumS < r[p]) ? sumS : r[p];
			#endif 
		}
	}
}

// saturation => func ok avec le simulateur 
void process_sat(int gf , unsigned char dest [] , const unsigned char src[] )
{
   	for( int i = 0; i < gf ; i++ ){
		#ifdef CST
		callSat8u(dest[i],src[i],SAT_VALUE) ; 
		#else 
    	dest[i]  = (src[i] >= SAT_VALUE) ? SAT_VALUE : src[i]; 
		#endif
	}
}

void CN_SPA_float_AVX2_process(int _dc_) {
	// FORWARD PROCESSING
    process_ecn(_GF_,  CCN._msgs[0],  CCN._msgs[1], CCN.ecns[0]);
	for(int q = 0; q <= (_dc_-4); q += 1){
		process_ecn( _GF_ ,CCN._msgs[q+2], CCN.ecns[q], CCN.ecns[q+1]);
	}

	// BACKWARD PROCESSING
   	process_ecn(_GF_,CCN._msgs[_dc_-2], CCN._msgs[_dc_-1], CCN.ecns[_dc_-2]);
	for(int q = 1; q <= (_dc_-3); q += 1){
		process_ecn(_GF_,CCN._msgs[_dc_-2-q], CCN.ecns[_dc_-3+q], CCN.ecns[_dc_-2+q]);
	}

	// MERGE PROCESSING
    process_ecn(_GF_, CCN._msgs[ 0], CCN.ecns[2*_dc_-6], CCN.ecns[2*_dc_-4]);
	for(int q = 1; q <= (_dc_-4); q += 1){
		process_ecn(_GF_,CCN.ecns[q-1], CCN.ecns[2*_dc_-6-q], CCN.ecns[2*_dc_-4+q]);
	}
	process_ecn(_GF_,CCN._msgs[_dc_-1], CCN.ecns[_dc_-4], CCN.ecns[3*_dc_-7]);

	// RECOPIE DES RESULTATS
	for(int q = 1; q <= (_dc_-1); q += 1){
		process_sat(_GF_, CCN._msgs[q-1], CCN.ecns[2*_dc_-6+q]);
	}
	process_sat(_GF_,CCN._msgs[_dc_-1], CCN.ecns[_dc_-3]);
}

void init_ecn()
{

	// inchangées 
	CCN.degree 	= _DEG_CN_;
	CCN.nECNs  	= 3 * (CCN.degree - 2);
   	CCN.size 	= 64 ; 

   	// alloc dynamique du tableau de pointeurs > tab de data ?  
	// type :: T** 
	// _msgs = new unsigned char* [degree]; 
 	CCN._msgs = (unsigned char**) malloc( CCN.degree * sizeof(unsigned char*)) ;
	
	for(int d=0; d<CCN.degree; d+=1){
		// creation mémoire à la main dans le heap, tableau après tableau 
		// aligned load:: intrinsec 
      	// intel d'apres stackoverflow
      	// _msgs[d] = (T*) _mm_malloc( size, sizeof(__m256i) ); 
		CCN._msgs[d] = (unsigned char*) malloc(CCN.size * sizeof(unsigned char)) ;
    }
	// ecns = new unsigned char* [nECNs];
   	CCN.ecns = (unsigned char**) malloc( CCN.nECNs * sizeof(unsigned char*)) ;

	for(int d=0; d<CCN.nECNs; d+=1){
		CCN.ecns[d] = (unsigned char*) malloc(CCN.size * sizeof(unsigned char)) ;
	}
}