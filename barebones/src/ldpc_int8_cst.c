#include <stdint.h>
#include "stdlib.h"

#define CODE   	("LDPC")
#define ALGO	("MPA - MIN-SUM")
#define ordo   	("Horizontal layered")

#define iter 	10
#define _8b 

#include "insn_2r.h"
#include "trame_34_20_BG2.h"

void process()
{
	// accu à conserver pour les iterations 
	int8_t Resu[32]  ;

		for(int l=0;l<iter;l++)
		{
			// garder les ptrs en data type 
			int8_t* ptr_posVn = posVn ;
			int8_t* ptr_c2v   = c2v ;

			// parcours des CN
			for( int idex_Cn = 0 ; idex_Cn < nb_CN ; idex_Cn++)
			{

				int8_t min1    = INT8_MAX ;
				int8_t min2    = INT8_MAX ;
				int8_t sign    =   0 ;

				// parcours des VN liés au Cn courant
				// on conserve une data en int pour la comparaison et 
				// int8_t idex_vn baisse les perfos 
				// compilateur préfère les int pour la loop
				int degCn = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{
					int8_t vAccu ;
					
					int8_t a ;

					int8_t indice = ptr_posVn[ idex_Vn ];
					int8_t pVn  =	accuVn[ indice];
					int8_t msg  =	ptr_c2v [ idex_Vn ];
					
					callSubSat(vAccu,pVn,msg);				

					Resu[idex_Vn] =  vAccu; 

					// check min & signe ;
					// int8_t testacc =  
					// andi	s8,t3,255
					// sb	t3,0(a6)
					// srli	s8,s8,0x7

					sign  ^=  ( vAccu < 0); 
	
					// min casse la séquence car force slli & srai 

					callAbs(a,vAccu,0); 

					int8_t min_temp ;
					callMax(min_temp,min1,a) ; 
					callMin(min2, min2, min_temp )  ;   
					callMin(min1, a,min1) ; 

				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{
					int8_t nMessage ;
					int8_t eval ; 
					int8_t Rsign; ; 

					int8_t temp = Resu[idex_Vn] ; 

					// idem avec eval qui slli & srai 
					callEval(eval,min1,temp); 
					callRsign(Rsign,sign,temp) ;

					// generation du mask + min à sortir
					int8_t min_t = min1 & ~eval ; 
					int8_t min_u = min2 & eval ; 
					int8_t min_  = min_t | min_u ; 
 
					callNmess(nMessage,Rsign,min_ ) ;

					// maj c2v
					ptr_c2v[idex_Vn] = nMessage ;

					callAddSat(temp,temp, nMessage) ;

					int8_t    indice = ptr_posVn[ idex_Vn ];
					accuVn[ indice ] = temp ;
				}
				
				ptr_posVn   += degCn;
				ptr_c2v     += degCn;
			}
		}
}

int main() {

	printf("|=======================|\n");
	printf("|%s(%d,%d)	\n",CODE, N, k );
	printf("|%s %s 		\n",ALGO, ordo ); 
	printf("|iter: %d , QTF: %s\n", iter, qtf ); 
	printf("|GENEREE : %s - %s\n", __DATE__, __TIME__);
	printf("|=======================|\n");

	long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 

    printf("|diff in :\n"); 
    for (int i=0 ; i<nb_VN; i++){
        // if( i%32 == 0 ) printf("\n");
        int decb = err_[i] > 0;
        if( codw[i] != decb )
            printf("E") ;
        else  
            printf("-") ;
	}
	printf("\n"); 

	// 4 cycles pour sortir les infos 
	cycle_start= cycles()-4;
	insn_start = insn()-4; 
	
   	process() ; 

	cycle_stop= cycles()-4;
	insn_stop = insn()-4; 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 

	printf("|=======================|\n");
	printf("|Bench\n"); 
	printf("|cycles	: %ld \n", cycle_tot) ; 
	printf("|insn	: %ld \n", insn_tot); 
	printf("|=======================|\n");

    printf("|diff out:\n"); 
    for (int i=0 ; i<nb_VN; i++){
        // if( i%32 == 0 ) printf("\n");
        int decb = accuVn[i] > 0;
        if( codw[i] != decb )
            printf("E") ;
        else  
            printf("-") ;
    }
	printf("\n"); 

	return 0; 

}