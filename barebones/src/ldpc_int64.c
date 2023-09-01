

#include <stdint.h>
#include "stdlib.h"

#define CODE   	("LDPC")
#define ALGO	("MPA - MIN-SUM")
#define ordo   	("Horizontal layered")

#define iter 	10
#define _64b

#include "trame_34_20_BG2.h"

#define EN_SAT


void process()
{
	// DOIT COMMENCER ICI AVEC AccVun déja remplit 
    
	// size 32 to compability 
	int64_t Resu[32]  ;

		for( int l=0; l<iter; l++)
		{
			// pour bouger dans le tableau d'indices
			int64_t* ptr_posVn = posVn ;
			int64_t* ptr_c2v   = c2v ;

			// parcours des CN
			for( int idex_Cn = 0 ; idex_Cn < nb_CN ; idex_Cn++)
			{

				// stocke les résu locaux des Vn pour traitement
				// degMax Cn -> 10

				
				int64_t min1    = INT8_MAX ;
				int64_t min2    = INT8_MAX ;
				int64_t sign    =  0 ;


				// parcours des VN liés au Cn courant
                int64_t degCN = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCN ; idex_Vn++)
				{

					// float Resu = nouveau - ancien
					// ancien :     SOv = LLR + S c2v ( eq 1.6 )  | v2c = SOv - c2v eq 1.7

					// de mem : 2 boucles l'une permet de maj les v2c pour chaque vn et de cac sign + xor

                    int64_t indice = ptr_posVn[ idex_Vn ];
					int64_t pVn  =	accuVn[ indice] 	;
					int64_t msg    =	ptr_c2v  [ idex_Vn ];
					
					#ifdef EN_SAT
					// instr 
					int64_t vAcc = pVn - msg ; 
					vAcc = vAcc > 127 	? 127  : vAcc ; 
					vAcc = vAcc < -127 	? -127 : vAcc ;
					int64_t vAccu = vAcc ; 
					
					#else 
					int vAccu = pVn - msg ; 

					#endif

					// OK 
					// int64_t vAccu = call_sub_sat_instr(pVn,msg);					
					
					Resu[idex_Vn] =  vAccu;

					// check min & signe ;
					// min avec vResu
					sign  ^=  ( vAccu < 0);  
			
					// pas mieux et fct pas 
					// sign = call_sign_instr(vAccu,sign); 
					
					int64_t a =  vAccu >= 0 ? vAccu : -vAccu ;
					// pas de gain , mm pire avec le call de cette facon  
					// int64_t a = call_abs_instr(vAccu,0); 	
					//  a = insn_abs( b )

					// ici aussi r4 peux etre un bon compromis 
					// pas d'améliorations avec les instrus customs 
	
					if(a < min1)
					{
						min2 = min1;
						min1 = a;
					}else if(a < min2) // min1 < a < min2
						min2 = a  ;
					

				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn = 0 ; idex_Vn < degCN; idex_Vn++)
				{
					int64_t nMessage ;
					int64_t temp = Resu[idex_Vn] ; 

					// maj des messages c2v

					// avec les mins et les signe
					// mask pour supprimer les branches conds. 
					int64_t eval = ( min1!=temp)? 0x00 : 0xff ; 
					
					int64_t min_t = min1 & ~eval ; 
					int64_t min_u = min2 & eval ; 
					int64_t min_  = min_t | min_u ; 

					int64_t Rsign 	= sign ^ ( temp >= 0 ) ; 
					nMessage = (Rsign) ? min_ : -min_; 

					// maj c2v
					ptr_c2v[idex_Vn] = nMessage ;
					
					// saturation 8 bits signes
					#ifdef EN_SAT

					int64_t res = (temp + nMessage) ; 
					int64_t post_res =  ( res > 127 ) ? 127 : ( res < -127 )? -127 : res  ;

					// up accuVn ;
                    int64_t    indice = ptr_posVn[ idex_Vn ];
					accuVn[ indice ] = post_res ;

					#else 

					int32_t res = (temp + nMessage) ; 
                    int    indice = ptr_posVn[ idex_Vn ];
					accuVn[ indice ] = res ;

					#endif

				}
				ptr_posVn   += degCN;
				ptr_c2v     += degCN;

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

	perfs_init();
	
   	process() ; 

	perfs_end(); 
	display_perf(); 


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