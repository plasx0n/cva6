/*
   SERV dependent à cause des instrus .. 
   voir pour refractor les vars temporaires 
   Ajouter eventuellement une autre instru dans le kernel .. 

*/


#include <stdint.h>

#include "ldpc_r3.h"


#define CODE   ("LDPC")
#define ordo   ("Horizontal layered")
#define qtf    ("int8_t")
#define nb_VN 	34
#define nb_CN 	14
#define iter 	10



// sort de la stack <= peux etre full et poser pb 

int8_t codw[]	={1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
int8_t err_[] 	={1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 

int8_t accuVn[] ={3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 } ; 

// deg de chaque CN
int8_t deg_Cns[] = {8,8,10,10,8,8,10,10,4,4,6,6,6,6  }; 

int8_t c2v [nb_CN * nb_VN ]= {0} ; 

int8_t posVn[]= {
    1, 3, 4, 6, 13, 19, 20, 22,
    0, 2, 5, 7, 12, 18, 21, 23,
    1, 6, 9, 11, 12, 14, 16, 18, 22, 24,
    0, 7, 8, 10, 13, 15, 17, 19, 23, 25,
    1, 2, 6, 8, 16, 21, 24, 26,
    0, 3, 7, 9, 17, 20, 25, 27,
    2, 4, 8, 10, 13, 14, 16, 18, 20, 26,
    3, 5, 9, 11, 12, 15, 17, 19, 21, 27,
    1, 2, 23, 28,
    0, 3, 22, 29,
    1, 3, 10, 15, 23, 30,
    0, 2, 11, 14, 22, 31,
    1, 10, 15, 18, 22, 32,
    0, 11, 14, 19, 23, 33,
} ; 


void process()
{
	// DOIT COMMENCER ICI AVEC AccVun déja remplit 
    
	// size 32 to compability 
	int8_t Resu[32]  ;

		for( int l=0; l<iter; l++)
		{
			// pour bouger dans le tableau d'indices
			int8_t* ptr_posVn = posVn ;
			int8_t* ptr_c2v   = c2v ;

			// parcours des CN
			for( int idex_Cn = 0 ; idex_Cn < nb_CN ; idex_Cn++)
			{

				// stocke les résu locaux des Vn pour traitement
				// degMax Cn -> 10

				
				int8_t min1    = 127 ;
				int8_t min2    = 127 ;
				int8_t sign    =  0 ;


				// parcours des VN liés au Cn courant
                int8_t degCN = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCN ; idex_Vn++)
				{

					// float Resu = nouveau - ancien
					// ancien :     SOv = LLR + S c2v ( eq 1.6 )  | v2c = SOv - c2v eq 1.7

					// de mem : 2 boucles l'une permet de maj les v2c pour chaque vn et de cac sign + xor

                    int8_t indice = ptr_posVn[ idex_Vn ];
					int8_t pVn  =	accuVn[ indice] 	;
					int8_t msg    =	ptr_c2v  [ idex_Vn ];
					
					int8_t vAccu ;
					callSubSat(vAccu,pVn,msg);				
					Resu[idex_Vn] =  vAccu; 

					// check min & signe ;
					// min avec vResu
					// sign  ^=  ( vAccu < 0); 
					
					int32_t SignVAcc ;
					callSign(SignVAcc,vAccu,0);
					sign^=SignVAcc ;  
				
					int8_t a = callAbs(vAccu,0); 
					min2 = minmax(min1,a,min2); 
					min1 = callMin( a,min1) ; 
					

				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn = 0 ; idex_Vn < degCN; idex_Vn++)
				{
					int8_t nMessage ;
					int8_t temp = Resu[idex_Vn] ; 

					// maj des messages c2v
					// avec les mins et les signe
					// mask pour supprimer les branches conds. 
					int8_t eval ;
					int8_t min_ = ld_min_sorting(min1,temp,min2);

					nMessage = ld_rsign_nmess(temp,sign,min_); 

					// maj c2v
					ptr_c2v[idex_Vn] = nMessage ;
					callAddSat(temp,temp, nMessage) ;

					// up accuVn ;
                    int8_t    indice = ptr_posVn[ idex_Vn ];
					accuVn[ indice ] = temp ;


				}
				ptr_posVn   += degCN;
				ptr_c2v     += degCN;

			}
		}

}
int main( ) 
{
	printf(" %s(%d,%d) %s:: %d ite :: %s \n",
	CODE,nb_VN,nb_VN-nb_CN,ordo ,iter,qtf) ; 


	printf("GENEREE : %s - %s\n", __DATE__, __TIME__);

	long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 
   	long time_start,time_stop , time_tot ;

	printf("|=======================|\n");
    printf("diff in :"); 
    for (int i=0 ; i<34; i++){
        if( i%32 == 0 ) printf("\n");
        int decb = err_[i] > 0;
        if( codw[i] != decb )
            printf("E") ;
        else  
            printf("-") ;
	}

	// 4 cycles pour sortir les infos 
	cycle_start= cycles()-4;
	insn_start = insn()-4; 
	
   	process() ; 

	cycle_stop= cycles()-4;
	insn_stop = insn()-4; 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 
	time_tot = time_stop - time_start ;

	printf("\n|=======================|\n");
	printf("cycles	: %d \n", cycle_tot) ; 
	printf("insn	: %d \n", insn_tot); 
	printf("|=======================|\n");

    printf("\n diff out :"); 
    for (int i=0 ; i<34; i++){
        if( i%32 == 0 ) printf("\n");
        int decb = accuVn[i] > 0;
        if( codw[i] != decb )
            printf("E") ;
        else  
            printf("-") ;
    }

	return 0; 

}
