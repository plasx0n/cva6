/*
cleaned code 
min pose toujours pb avec le signe et oblige le gcc à passer
par slli / srai 

*/
// #define debug
#include <stdint.h>

#define CODE   ("LDPC")
#define ordo   ("Horizontal layered")
#define qtf    ("int8x4 SIMD:4")
#define iter 	10
#define nb_VN 	34
#define nb_CN 	14

#define int8_tx4 int32_t
#define int8_tx8 int64_t 

#ifdef debug
	void displayVector( int8_tx4 vector ){
		printf("V4[31:24] %d ",   vector>>24) ;
		printf("V3[23:16] %d ",  (vector<<8)>>24) ;
		printf("V2[15:8]  %d ",  (vector<<16)>>24) ;
		printf("V1[7:0]   %d \n",(vector<<24)>>24) ;
	}
	/**/
	void displayVectorHex_int8x4( int8_tx4 vector ){
		printf("V4[31:24] %x ",   vector>>24) ;
		printf("V3[23:16] %x ",  (vector<<8)>>24) ;
		printf("V2[15:8]  %x ",  (vector<<16)>>24) ;
		printf("V1[7:0]   %x \n",(vector<<24)>>24) ;
	}
#endif

#define callSign(rd,rs1,rs2) asm volatile("ld.sign %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
#define callAbs(rd,rs1,rs2) asm volatile("ld.abs %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
#define callMax(rd,rs1,rs2) asm volatile("ld.max %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
#define callMin(rd,rs1,rs2) asm volatile("ld.min %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
#define callNmess(rd,rs1,rs2) asm volatile("ld.nmess %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2));
#define callSubSat(rd,rs1,rs2) asm volatile("ld.subsat %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 						
#define callRsign(rd,rs1,rs2) asm volatile("ld.rsign %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
#define callEval(rd,rs1,rs2) asm volatile("ld.eval %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
#define callAddSat(rd,rs1,rs2) asm volatile("ld.addsat %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

// verification 

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
 

int32_t  accuVn[34] ; 

int8_t trames[nb_VN*4] = {
	3,5,-4,-4,0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4,
	-6,-4,5,-4,0,2,1,5,4,0,5,6,0,9,5,6,4,-7,-1,-4,-4,7,-7,6,1,-2,2,4,1,8,0,5,-9,5,
	3,5,5,5,-9,2,1,5,-5,-9,-4,-3,-9,9,5,6,-5,2,-1,-4,5,7,2,-3,1,7,-7,-5,1,8,9,-4,0,-4,
	3,5,-4,5,0,2,-8,5,-5,0,5,6,-9,0,5,6,-5,2,-1,5,-4,-2,-7,-3,1,-2,-7,4,1,-1,0,-4,0,-4 
	};

// deg de chaque CN
int32_t deg_Cns[] = 
{
    8,8,10,10,8,8,10,10,4,4,6,6,6,6  
}; 

int32_t c2v [nb_CN *nb_VN ]= {0} ; 

int32_t posVn[]= {
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

void reorder(int32_t* dest, const int8_t* src, int N) // a = sign, b = value
{
    int8_t* ptr = (int8_t*) dest;
    for (int8_t i=0; i<N; i++)
    {
        for (int32_t z = 0; z < 4; z+= 1)
        {
            ptr[(4*i) + z] = src[z * N + i];  
        }
    }
}

void ireorder(int8_t* dest, int32_t* src, int N) // a = sign, b = value
{
    int8_t* ptr = (int8_t*) src;
    for (int32_t i = 0; i < N; i += 1)
    {
        for (int32_t j = 0; j < 4; j += 1)
        {
            dest[j * N + i] = ptr[4 * i + j];
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


void process()
{
	// accu à conserver pour les iterations 
	int32_t Resu[32]  ;

		for(int l=0;l<iter;l++)
		{
		#ifdef debug 
			printf("iter %d\n", l);
		#endif
			// garder les ptrs en data type 
			int32_t* ptr_posVn = posVn ;
			int32_t* ptr_c2v   = c2v ;

			// parcours des CN
			for( int idex_Cn = 0 ; idex_Cn < nb_CN ; idex_Cn++)
			{

			#ifdef debug 
				printf("	CN %d\n", idex_Cn); 
			#endif

				int32_t min1    = 	0x7E7E7E7E ;
				int32_t min2    = 	0x7E7E7E7E ;
				int32_t sign    =   0 ;

				// parcours des VN liés au Cn courant
				// on conserve une data en int pour la comparaison et 
				// int8_t idex_vn baisse les perfos 
				// compilateur préfère les int pour la loop
				int degCn = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{

					#ifdef debug 
						printf("		VN %d\n",idex_Vn);
					#endif
					int32_t vAccu ;
					int32_t min_temp ;
					int32_t a ;

					int32_t indice = ptr_posVn[ idex_Vn ];
					int32_t pVn  =	accuVn[ indice];
					int32_t msg  =	ptr_c2v [ idex_Vn ];
					
					callSubSat(vAccu,pVn,msg);				
					Resu[idex_Vn] =  vAccu; 

					#ifdef debug 
						printf("			subsat \n"); 
						printf("			pVN ");
						displayVector(pVn) ; 
						printf("			msg "); 
						displayVector(msg) ; 
						printf("			vAccu "); 
						displayVector(vAccu) ;


					#endif 




					// doit etre compatible avec 32b 
					int32_t SignVAcc ;
					callSign(SignVAcc,vAccu,0);
					sign^= SignVAcc; 

					#ifdef debug 
						printf("			sign \n"); 
						printf("			vAccu "); 
						displayVector(vAccu) ; 
						printf("			SignVAcc ");
						displayVector(SignVAcc) ; 
						printf("			sign "); 
						displayVector(sign) ; 
					#endif 


					// min casse la séquence car force slli & srai 
					callAbs(a,vAccu,0); 
					callMax(min_temp,min1,a) ; 
					callMin(min2, min2, min_temp )  ;   
					callMin(min1, a,min1) ; 
					#ifdef debug 
						printf("			a	" ); 
						displayVector(a) ;
						printf("			min1 " ); 
						displayVector(min1) ;
						printf("			min2 " ); 
						displayVector(min2) ;
					#endif 
				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{
					#ifdef debug 
						printf("		VN %d\n",idex_Vn);
					#endif
					int32_t nMessage ;
					int32_t eval ; 
					int32_t Rsign;

					int32_t temp = Resu[idex_Vn] ; 

					// idem avec eval qui slli & srai 
					callEval(eval,min1,temp); 
					callRsign(Rsign,sign,temp) ;

					#ifdef debug 
						printf("			Rsign \n"); 
						printf("			sign "); 
						displayVector(sign) ; 
						printf("		+++	temp ");
						displayVector(temp) ; 
						printf("			Rsign "); 
						displayVector(Rsign) ; 
					#endif 

					// generation du mask + min à sortir
					int32_t min_t = min1 & ~eval ; 
					int32_t min_u = min2 & eval ; 
					int32_t min_  = min_t | min_u ; 
 
					
					callNmess(nMessage,Rsign,min_ ) ;
					#ifdef debug 
						printf("			Nmess  \n"); 
						printf("			min_ 	 ");
						displayVector(min_);  
						printf("			Rsign  	 ");
						displayVector(Rsign);  
						printf("			Nmessage "); 
						displayVector(nMessage);  

					#endif 

					// maj c2v
					ptr_c2v[idex_Vn] = nMessage ;
	
					callAddSat(temp,temp, nMessage) ;
					#ifdef debug 
						printf("			callAddSat "); 
						printf("			nMessage   "); 
						displayVector(nMessage);
						printf("			res temp   ");
						displayVector(temp) ; 
					#endif 

					int32_t  indice = ptr_posVn[ idex_Vn ];
					accuVn[ indice ] = temp ;
				}
				
				ptr_posVn   += degCn;
				ptr_c2v     += degCn;
			}

			#ifdef debug 
				for (int i = 0; i < nb_VN; i++)
					displayVector(accuVn[i]) ; 
			#endif
		}

}


int main( ) 
{
	printf("%s(%d,%d) :: %s:: %d ite :: %s\n",CODE,nb_VN,nb_VN-nb_CN,ordo ,iter,qtf) ; 
	printf("GENEREE : %s - %s\n", __DATE__, __TIME__);

	// re-order operation 
	trameCheck(codw1,err_1) ; 
	trameCheck(codw2,err_2) ; 
	trameCheck(codw3,err_3) ; 
	trameCheck(codw4,err_4) ;


	long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 
   	long time_start,time_stop , time_tot ;

	// 4 cycles pour sortir les infos 
	cycle_start= cycles()-4;
	insn_start = insn()-4; 
	
	// ordering is part of the decoder 
	reorder(accuVn,trames,34); 

#ifdef debug 
	for (int i = 0; i < nb_VN; i++)
		displayVector(accuVn[i]) ; 
#endif
	

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

	return 0; 

}
