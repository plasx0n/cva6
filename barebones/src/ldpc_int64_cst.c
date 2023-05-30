/*
BUg

*/
#include <stdint.h>

#define CODE   ("LDPC")
#define ordo   ("Horizontal layered")
#define qtf    ("int64_t")
#define iter 	10
#define nb_VN 	34
#define nb_CN 	14

int64_t codw[]=  {1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
int64_t err_[] = {1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 

int64_t accuVn[]={3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 } ; 

// deg de chaque CN
int64_t deg_Cns[] = {8,8,10,10,8,8,10,10,4,4,6,6,6,6 }; 

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
	int64_t Resu[32]  ;

		for(int l=0;l<iter;l++)
		{
			// garder les ptrs en data type 
			int64_t* ptr_posVn = posVn ;
			int64_t* ptr_c2v   = c2v ;

			// parcours des CN
			for( int idex_Cn = 0 ; idex_Cn < nb_CN ; idex_Cn++)
			{

				int64_t min1    = INT8_MAX ;
				int64_t min2    = INT8_MAX ;
				int64_t sign    =   0 ;

				// parcours des VN liés au Cn courant
				// on conserve une data en int pour la comparaison et 
				// int64_t idex_vn baisse les perfos 
				// compilateur préfère les int pour la loop
				int degCn = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{
					int64_t vAccu ;
					int64_t min_temp ;
					int64_t a ;

					int64_t indice = ptr_posVn[ idex_Vn ];
					int64_t pVn  =	accuVn[ indice];
					int64_t msg  =	ptr_c2v [ idex_Vn ];
					
					callSubSat(vAccu,pVn,msg);				
					Resu[idex_Vn] =  vAccu; 

					// check min & signe ;
					// int64_t testacc =  
					// andi	s8,t3,255
					// sb	t3,0(a6)
					// srli	s8,s8,0x7

					sign  ^=  ( vAccu < 0); 
	
					// min casse la séquence car force slli & srai 
					callAbs(a,vAccu,0); 
					callMax(min_temp,min1,a) ; 
					callMin(min2, min2, min_temp )  ;   
					callMin(min1, a,min1) ; 

				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{
					int64_t nMessage ;
					int64_t eval ; 
					int64_t Rsign; ; 

					int64_t temp = Resu[idex_Vn] ; 

					// idem avec eval qui slli & srai 
					callEval(eval,min1,temp); 
					callRsign(Rsign,sign,temp) ;

					// generation du mask + min à sortir
					int64_t min_t = min1 & ~eval ; 
					int64_t min_u = min2 & eval ; 
					int64_t min_  = min_t | min_u ; 
 
					callNmess(nMessage,Rsign,min_ ) ;

					// maj c2v
					ptr_c2v[idex_Vn] = nMessage ;
	
					callAddSat(temp,temp, nMessage) ;

					int64_t    indice = ptr_posVn[ idex_Vn ];
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