/*
   SERV dependent à cause des instrus .. 
   voir pour refractor les vars temporaires 
   Ajouter eventuellement une autre instru dans le kernel .. 

*/


#include <stdint.h>

#include "ldpc_r3_int8x8.h"

#define CODE   ("LDPC")
#define ordo   ("Horizontal layered")
#define qtf    ("int64_t SIMD:8 ")
#define nb_VN 	34
#define nb_CN 	14
#define iter 	10



int8_t 	codw1[]=  {1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0};  
int8_t 	err_1[] = {1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
		   
//    3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 

// parviens pas à corriger 
int8_t codw2[]  ={0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,1,1,0,1,0,1,0,1} ;
int8_t err_2[] = {0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,1,1,0,1,0,1,0,1};
			

// []={-6,-4,5,-4,0,2,1,5,4,0,5,6,0,9,5,6,4,-7,-1,-4,-4,7,-7,6,1,-2,2,4,1,8,0,5,-9,5, } ;
				  
int8_t codw3[]  ={1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,1,0} ;
int8_t err_3[] = {1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,1,0};
			      
// []={3,5,5,5,-9,2,1,5,-5,-9,-4,-3,-9,9,5,6,-5,2,-1,-4,5,7,2,-3,1,7,-7,-5,1,8,9,-4,0,-4, } ; 

// parviens pas à corriger
int8_t codw4[]  ={1,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0} ;
int8_t err_4[] = {1,1,0,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0}; 

// []={3,5,-4,5,0,2,-8,5,-5,0,5,6,-9,0,5,6,-5,2,-1,5,-4,-2,-7,-3,1,-2,-7,4,1,-1,0,-4,0,-4, 

int8_t 	codw5[]=  {1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0};  
int8_t 	err_5[] = {1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
		   
//    3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 

// parviens pas à corriger 
int8_t codw6[]  ={0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,1,1,0,1,0,1,0,1} ;
int8_t err_6[] = {0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,1,1,0,1,0,1,0,1};
			

// []={-6,-4,5,-4,0,2,1,5,4,0,5,6,0,9,5,6,4,-7,-1,-4,-4,7,-7,6,1,-2,2,4,1,8,0,5,-9,5, } ;
				  
int8_t codw7[]  ={1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,1,0} ;
int8_t err_7[] = {1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,1,0};
			      
// []={3,5,5,5,-9,2,1,5,-5,-9,-4,-3,-9,9,5,6,-5,2,-1,-4,5,7,2,-3,1,7,-7,-5,1,8,9,-4,0,-4, } ; 

// parviens pas à corriger
int8_t codw8[]  ={1,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0} ;
int8_t err_8[] = {1,1,0,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0}; 

// []={3,5,-4,5,0,2,-8,5,-5,0,5,6,-9,0,5,6,-5,2,-1,5,-4,-2,-7,-3,1,-2,-7,4,1,-1,0,-4,0,-4, 
 

int64_t  accuVn[34] ; 

int8_t trames[] = {
//t1 to t4  
3,5,-4,-4,0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4, 
-6,-4,5,-4,0,2,1,5,4,0,5,6,0,9,5,6,4,-7,-1,-4,-4,7,-7,6,1,-2,2,4,1,8,0,5,-9,5,
3,5,5,5,-9,2,1,5,-5,-9,-4,-3,-9,9,5,6,-5,2,-1,-4,5,7,2,-3,1,7,-7,-5,1,8,9,-4,0,-4,
3,5,-4,5,0,2,-8,5,-5,0,5,6,-9,0,5,6,-5,2,-1,5,-4,-2,-7,-3,1,-2,-7,4,1,-1,0,-4,0,-4,
// copy 
3,5,-4,-4,0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4, 
-6,-4,5,-4,0,2,1,5,4,0,5,6,0,9,5,6,4,-7,-1,-4,-4,7,-7,6,1,-2,2,4,1,8,0,5,-9,5,
3,5,5,5,-9,2,1,5,-5,-9,-4,-3,-9,9,5,6,-5,2,-1,-4,5,7,2,-3,1,7,-7,-5,1,8,9,-4,0,-4,
3,5,-4,5,0,2,-8,5,-5,0,5,6,-9,0,5,6,-5,2,-1,5,-4,-2,-7,-3,1,-2,-7,4,1,-1,0,-4,0,-4,

} ;

// deg de chaque CN
int64_t deg_Cns[] = 
{
    8,8,10,10,8,8,10,10,4,4,6,6,6,6  
}; 

int64_t c2v [nb_CN *nb_VN ]= {0} ; 

int64_t posVn[]= {
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


// feed trames * 4 array of int8_t 
void reorder(int64_t* dest, const int8_t* src, int N) // a = sign, b = value
{
    int8_t* ptr = (int8_t*) dest;
    for (int8_t i=0; i<N; i++)
    {
        for (int64_t z = 0; z < 8; z+= 1)
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

void trameCheck(int8_t * codw ,int8_t * err_ ){
	printf("Diff in : \n") ;
	for (int i=0 ; i<34; i++){
      	int decb = err_[i] > 0;
      	if( codw[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	}
	printf("\n") ; 
}

void postTrameCheck(int8_t * trame, int8_t * codw, int N ){

	printf("Diff post: \n") ;
	for (int i=N ; i<N+34; i++){
      	int decb = trame[i] > 0;
      	if( codw[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	}
	printf("\n") ; 
}

void displayVector( int32_t vector ){
	printf("V4[31:24] %d ",   vector>>24) ;
	printf("V3[23:16] %d ",  (vector<<8)>>24) ;
	printf("V2[15:8]  %d ",  (vector<<16)>>24) ;
	printf("V1[7:0]   %d \n",(vector<<24)>>24) ;
}

// #define debug

void process()
{
	// DOIT COMMENCER ICI AVEC AccVun déja remplit 

	// size 32 to compability 
	int64_t Resu[32]  ;

		for( int l=0; l<iter; l++)
		{
			#ifdef debug
				printf("ITER nb %d\n",iter);
			#endif
			// pour bouger dans le tableau d'indices
			int64_t* ptr_posVn = posVn ;
			int64_t* ptr_c2v   = c2v ;

			// parcours des CN
			for( int idex_Cn = 0 ; idex_Cn < nb_CN ; idex_Cn++)
			{
				#ifdef debug
					printf("idex_cn %d\n",idex_Cn);
				#endif
				// stocke les résu locaux des Vn pour traitement
				// degMax Cn -> 10

				
				int64_t min1    = (int64_t) 0X7F7F7F7F7F7F7F7F ;
				int64_t min2    = (int64_t) 0X7F7F7F7F7F7F7F7F ;
				int64_t sign    =  0 ;


				// parcours des VN liés au Cn courant
                int64_t degCN = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCN ; idex_Vn++)
				{
					#ifdef debug
						printf("idex_Vn %d\n",idex_Vn);
					#endif
					// float Resu = nouveau - ancien
					// ancien :     SOv = LLR + S c2v ( eq 1.6 )  | v2c = SOv - c2v eq 1.7

					// de mem : 2 boucles l'une permet de maj les v2c pour chaque vn et de cac sign + xor

                    int64_t indice 	= ptr_posVn[ idex_Vn ];
					int64_t pVn  	= accuVn[ indice] 	;
					int64_t msg    	= ptr_c2v  [ idex_Vn ];
					
					int64_t vAccu ;
					callSubSat(vAccu,pVn,msg);				
					Resu[idex_Vn] =  vAccu; 

					#ifdef debug
						printf("vAccu : \n") ; 
						displayVector(vAccu) ; 
					#endif

					// check min & signe ;
					// min avec vResu
					int64_t SignVAcc ;
					callSign(SignVAcc,vAccu,0);
					sign^=SignVAcc ; 

					#ifdef debug
						printf("sign : \n") ; 
						displayVector(sign) ; 
					#endif
				
					int64_t a = callAbs(vAccu,0); 

					#ifdef debug
						printf("a : \n") ; 
						displayVector(a) ; 
					#endif

					min2 = minmax(min1,a,min2); 
					callMin(min1, a,min1) ; 

					#ifdef debug
						printf("min1 : \n") ; 
						displayVector(min1) ; 

						printf("min2 : \n") ; 
						displayVector(min2) ; 
					#endif

				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn = 0 ; idex_Vn < degCN; idex_Vn++)
				{
					#ifdef debug
						printf("idex_Vn %d\n",idex_Vn);
					#endif

					int64_t nMessage ;
					int64_t temp = Resu[idex_Vn] ; 

					// maj des messages c2v
					// avec les mins et les signe
					// mask pour supprimer les branches conds. 
					int64_t min_ = ld_min_sorting(min1,temp,min2);
					
					#ifdef debug
						printf("min1 : \n") ; 
						displayVector(min1) ; 

						printf("temp : \n") ; 
						displayVector(temp) ; 

						printf("min2 : \n") ; 
						displayVector(min2) ; 

						printf("min_ : \n") ; 
						displayVector(min_) ; 
					#endif
					
					nMessage 	 = ld_rsign_nmess(temp,sign,min_); 

					#ifdef debug
						printf("nMessage : \n") ; 
						displayVector(nMessage) ; 
					#endif

					// maj c2v
					ptr_c2v[idex_Vn] = nMessage ;
					callAddSat(temp,temp, nMessage) ;

					#ifdef debug
						printf("temp : \n") ; 
						displayVector(temp) ; 
					#endif
					// up accuVn ;
                    int32_t    indice = ptr_posVn[ idex_Vn ];
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
	// re-order operation 
	trameCheck(codw1,err_1) ; 
	trameCheck(codw2,err_2) ; 
	trameCheck(codw3,err_3) ; 
	trameCheck(codw4,err_4) ;
	printf("|=======================|\n");

	// 4 cycles pour sortir les infos 
	cycle_start= cycles()-4;
	insn_start = insn()-4; 
	 
	// this is ok 
	reorder(accuVn,trames,34);
   	process() ; 
	ireorder(trames,accuVn,34) ;

	cycle_stop= cycles()-4;
	insn_stop = insn()-4; 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 
	time_tot = time_stop - time_start ;

	printf("\n|=======================|\n");
	printf("cycles	: %d \n", cycle_tot) ; 
	printf("insn	: %d \n", insn_tot); 
	printf("|=======================|\n");

	postTrameCheck(trames,codw1,0) ;

	printf("Diff post: \n") ;
	for (int i=0 ; i<34; i++){
      	int decb = trames[34+i] > 0;
		  printf("trame %d codw2 %d ",trames[34+i], codw2[i] ); 
      	if( codw2[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	printf("\n"); 
	}
	printf("\n") ; 

	printf("Diff post: \n") ;
	for (int i=0 ; i<34; i++){
      	int decb = trames[68+i] > 0;
      	if( codw3[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	}
	printf("\n") ; 

	printf("Diff post: \n") ;
	for (int i=0 ; i<34; i++){
      	int decb = trames[(34*3)+i] > 0;
      	if( codw4[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	}
	printf("\n") ; 

	printf("|=======================|\n");

		printf("Diff post: \n") ;
	for (int i=0 ; i<34; i++){
      	int decb = trames[(34*4)+i] > 0;
      	if( codw5[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	}
	printf("\n") ;

			printf("Diff post: \n") ;
	for (int i=0 ; i<34; i++){
      	int decb = trames[(34*5)+i] > 0;
      	if( codw6[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	}
	printf("\n") ;


		printf("Diff post: \n") ;
	for (int i=0 ; i<34; i++){
      	int decb = trames[(34*6)+i] > 0;
      	if( codw7[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	}
	printf("\n") ;


		printf("Diff post: \n") ;
	for (int i=0 ; i<34; i++){
      	int decb = trames[(34*7)+i] > 0;
      	if( codw8[i] != decb )
        	printf("E") ;
      	else  
        	printf("-") ;
	}
	printf("\n") ;


}
