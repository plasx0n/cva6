
// #include "simple_system_common.h"

#define test_gf16
// #define CST

#define callAdd32sSat64(rd,rs1,rs2) asm volatile("ldn.add32s_sat64 %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
#define callSub32sSat64(rd,rs1,rs2) asm volatile("ldn.sub32s_sat64 %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
                               
#define callMin(rd,rs1,rs2) asm volatile("ldn.min %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

#define callAdd32uSat64(rd,rs1,rs2) asm volatile("ldn.add32u_sat64 %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 


#define callSat8u(rd,rs1,rs2) asm volatile("ldn.sat8u %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

#include "nsimd.h"
#include "hlayered.h"
#include "CCN.h"
#include "trame.h"

unsigned char msgs[_MESSAGE_ * _GF_];   
unsigned char vars[_NSYMBOL_ * _GF_];	

int m_saturation=63 ; //selon simu 

char t_decoded_bits [ _NBIT_ + 32];

void decode(int nIters)
{
	unsigned char* SRC = t1_proba_symbol_fixed;

	copy(_GF_ * _NSYMBOL_, vars, SRC);

	unsigned char symbol[_NSYMBOL_];
	char* DEST = t_decoded_bits;

	// INITIALISATION DES MESSAGES
	zero( _MESSAGE_*_GF_, msgs );

   	int iter;
	
	for (iter = 0; iter < nIters; iter+=1)
	{
		// printf( "ite : %d",iter); 
		const int* pNodes      = LINK_NODES;
		unsigned char* pMsgRd  = msgs;
		unsigned char* pMsgWr  = msgs;

   		for (int cn = 0; cn < _DEG_COMPUTATIONS_; cn+=1) /* Loop for the M Check nodes */
			{
				int dCN = CHECK_DEGREE[ cn ];
				for (int d=0; d<_DEG_CN_; d++) //maj Vn to Cn , message apres messages 
				{

					const int vn_start = _GF_ * pNodes[d];
					message( _GF_, CCN._msgs[d] , vars + vn_start, pMsgRd);
					const unsigned char min = find_min(_GF_, CCN._msgs[d]	);
					normalize( _GF_,	CCN._msgs[d],min);

              	 	multiply( _GF_ ,CCN._msgs[d]		 , ALPHA[_DEG_CN_ * cn + d]);
					to_natural(_GF_ ,	CCN._msgs[d]		 );

    
               pMsgRd += _GF_;
					
				}
            	// ON CALCULE LES VALEURS INTERNES DU NOEUD CN
				CN_SPA_float_AVX2_process(dCN) ; 

				// ON MET A JOUR LES	 VALEURS DES NOEUDS VNs
				for (int d=0; d<_DEG_CN_; d++)
				{
					const int vn_start = _GF_ * pNodes[d];
        
					to_gf ( _GF_ ,	CCN._msgs[d]		 );
					divide( _GF_ ,	CCN._msgs[d]		, ALPHA[_DEG_CN_ * cn + d]);
					update( _GF_, vars + vn_start, 		CCN._msgs[d]		 ); // MAX VALUE INSERTED
					copy  ( _GF_, pMsgWr, 					CCN._msgs[d]		 );

					pMsgWr  += _GF_;
				}
				pNodes += _DEG_CN_;

			}
         
         if( 1 )
			{
				symb_decision( _GF_ ,symbol, vars);
				int s = syndrom( _GF_, symbol);
				if( s == 0 ){
					// _t->decoded( true );
					iter += 1; // ON COMPTE LA DERNIERE ITERATION
					break;
				}
			}
		}

		hard_decision(_GF_,DEST, vars);

}


int main( ) 
{
	init_ecn(); 
	decode(2);

	// for (int i=0; i< _NBIT_ ; i++) {
    // 	(t1_coded_bits[i] != t_decoded_bits[i]) ? puts("E") : puts("-");  
    // }

	return 0 ; 
}




