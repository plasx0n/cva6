/*
BUg

*/
#include <stdint.h>

#define debug 

#define CODE   ("LDPC")
#define ordo   ("Horizontal layered")
#define qtf    ("int32_t")
#define iter 	10
#define nb_VN 	34
#define nb_CN 	14

int32_t codw[]=  {1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
int32_t err_[] = {1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 

int32_t accuVn[]={3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 } ; 

// deg de chaque CN
int32_t deg_Cns[] = {8,8,10,10,8,8,10,10,4,4,6,6,6,6 }; 

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


				int32_t min1    = INT8_MAX ;
				int32_t min2    = INT8_MAX ;
				int32_t sign    =   0 ;

				// parcours des VN liés au Cn courant
				// on conserve une data en int pour la comparaison et 
				// int32_t idex_vn baisse les perfos 
				// compilateur préfère les int pour la loop
				int degCn = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{
					#ifdef debug 
						printf("		VN%d\n",idex_Vn);
					#endif


					int32_t vAccu ;
					int32_t min_temp ;
					int32_t a ;

					int32_t indice = ptr_posVn[ idex_Vn ];
					int32_t pVn  =	accuVn[ indice];
					int32_t msg  =	ptr_c2v [ idex_Vn ];
					
					callSubSat(vAccu,pVn,msg);	
					
					#ifdef debug 
						printf("			indice  %d \n",indice);
						printf("			subsat \n");
						printf("			pVn  	%d \n", pVn);
						printf("			msg  	%d \n", msg);
						printf("			vAccu  	%d \n", vAccu);
						// printf("			sign %d \n", sign); 
					#endif

								
					Resu[idex_Vn] =  vAccu; 

					// check min & signe ;
					// int32_t testacc =  
					// andi	s8,t3,255
					// sb	t3,0(a6)
					// srli	s8,s8,0x7

					sign  ^=  ( vAccu < 0); 
					
					#ifdef debug 
						printf("			sign \n"); 
						printf("			vAccu  	%d \n", vAccu);
						printf("			sign 	%d \n", sign); 
					#endif 


					// min casse la séquence car force slli & srai 
					callAbs(a,vAccu,0); 
					callMax(min_temp,min1,a) ; 
					callMin(min2, min2, min_temp )  ;   
					callMin(min1, a,min1) ; 

					#ifdef debug 
						printf("			a 	 %d\n", a ); 
						printf("			min1 %d\n", min1 ); 
						printf("			min2 %d\n", min2 ); 
					#endif 


				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{

					#ifdef debug 
						printf("		VN%d\n",idex_Vn);
					#endif

					int32_t nMessage ;
					int32_t eval ; 
					int32_t Rsign; ; 

					int32_t temp = Resu[idex_Vn] ; 

					// idem avec eval qui slli & srai 
					callEval(eval,min1,temp); 
					#ifdef debug 
						printf("			eval \n"); 
						printf("			min1  %d \n", min1); 
						printf("			temp  %d \n", temp);
						printf("			eval  %d \n", eval);
					#endif 


					callRsign(Rsign,sign,temp) ;

					#ifdef debug 
						printf("			Rsign \n"); 
						printf("			sign  %d \n", sign); 
						printf("			temp  %d \n", temp);
						printf("			Rsign %d \n", Rsign); 
					#endif 

					// generation du mask + min à sortir
					int32_t min_t = min1 & ~eval ; 
					int32_t min_u = min2 & eval ; 
					int32_t min_  = min_t | min_u ; 
 
					callNmess(nMessage,Rsign,min_ ) ;

					#ifdef debug 
						printf("			Nmess \n"); 
						printf("			min_  	 %d \n", min_); 
						printf("			Rsign  	 %d \n", Rsign);
						printf("			Nmessage %d \n", nMessage); 
					#endif 


					// maj c2v
					ptr_c2v[idex_Vn] = nMessage ;
	
					callAddSat(temp,temp, nMessage) ;

					#ifdef debug 
						printf("			callAddSat \n"); 
						printf("			min_  	 	%d \n", min_); 
						printf("			res temp  	%d \n", temp);
					#endif 


					int32_t    indice = ptr_posVn[ idex_Vn ];
					accuVn[ indice ] = temp ;
				}
				
				ptr_posVn   += degCn;
				ptr_c2v     += degCn;
			}
		}

}

int main( ) 
{
	printf("%s(%d,%d) :: %s:: %d ite :: %s \n",CODE,nb_VN,nb_VN-nb_CN,ordo ,iter,qtf) ; 
	// generic test 

	printf("GENEREE : %s - %s\n", __DATE__, __TIME__);

	long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 
   	long time_start,time_stop , time_tot ;

    printf("\n"); 
    printf("\n diff in :"); 
    for (int i=0 ; i<nb_VN; i++){
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

	printf("cycles	: %d \n", cycle_tot) ; 
	printf("insn	: %d \n", insn_tot);

    printf("\n"); 
    printf("\n diff out :"); 
    for (int i=0 ; i<nb_VN; i++){
        if( i%32 == 0 ) printf("\n");
        int decb = accuVn[i] > 0;
        if( codw[i] != decb )
            printf("E") ;
        else  
            printf("-") ;
    }

	return 0 ; 

}