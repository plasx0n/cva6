/*
   SERV dependent à cause des instrus .. 
   voir pour refractor les vars temporaires 
   Ajouter eventuellement une autre instru dans le kernel .. 

*/

#include <stdlib.h>
#include <stdint.h>

#define CODE   ("LDPC")
#define ordo   ("Horizontal layered")
#define qtf    ("int8")
#define iter 	10
#define nb_VN 	34
#define nb_CN 	14



int8_t 	codw[]=  {1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
int8_t 	err_[] = {1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 

int8_t  	accuVn[nb_VN]={3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 } ; 

// deg de chaque CN
int8_t deg_Cns[] = 
{
    8,8,10,10,8,8,10,10,4,4,6,6,6,6  
}; 

int8_t c2v [nb_CN *nb_VN ]= {0} ; 

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

// basiquement reviens au meme 
inline int8_t callAbs(int8_t rs1,int8_t rs2)
{
	int8_t rd ; 
	asm volatile("ld.abs %0,%1,%2" \
	            	: "=r" (rd) \
	            	: "r" (rs1), "r" (rs2));
	return rd ;
}

#define callMax(rd,rs1,rs2) asm volatile("ld.max %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

// #define callMin(rd,rs1,rs2) asm volatile("ld.min %0,%1,%2" \
	                            // : "=r" (rd) \
	                            // : "r" (rs1), "r" (rs2)); 

inline int8_t callMin(int8_t rs1,int8_t rs2)
{
	int8_t rd ; 
	asm volatile("ld.min %0,%1,%2" \
	            	: "=r" (rd) \
	            	: "r" (rs1), "r" (rs2));
	return rd ;
}


#define callNmess(rd,rs1,rs2) asm volatile("ld.nmess %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2));

#define callSubSat(rd,rs1,rs2) asm volatile("ld.subsat %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
								
#define callRsign(rd,rs1,rs2) asm volatile("ld.rsign %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

inline int8_t Sign(int8_t rs1,int8_t rs2)
{
	int8_t rd ; 
	asm volatile("ld.sign %0,%1,%2" \
	                : "=r" (rd) \
	                : "r" (rs1), "r" (rs2));
	return rd ; 
}

#define callEval(rd,rs1,rs2) asm volatile("ld.eval %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 


#define callAddSat(rd,rs1,rs2) asm volatile("ld.invminand %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 


static inline int sign3( int rs1 , int rs2, int rs3  ){
    int rd ; 
    asm volatile(" ld3_sign3 %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

static inline int minmax( int rs1 , int rs2, int rs3  ){
    int rd ; 
    asm volatile(" ld3_minmax %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

static inline int ld_rsign_nmess( int rs1 , int rs2, int rs3  ){
    int rd ; 
    asm volatile(" ld3_rsign_nmess %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

static inline int ld_min_sorting( int rs1 , int rs2, int rs3  ){
    int rd ; 
    asm volatile(" ld3_min_sorting %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}


void process()
{
	// DOIT COMMENCER ICI AVEC AccVun déja remplit 
    
    // HL /////////////////////////////////

	int8_t Resu[32]  ;

		for(int l=0;l<iter;l++)
		{
			int8_t* ptr_posVn = posVn ;
			int8_t* ptr_c2v   = c2v ;

			// parcours des CN
			for( int idex_Cn = 0 ; idex_Cn < nb_CN ; idex_Cn++)
			{

				int8_t min1    = 127 ;
				int8_t min2    = 127 ;
				int8_t sign    =   0 ;

				// parcours des VN liés au Cn courant
				int degCn = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{

					int indice = ptr_posVn[ idex_Vn ];
					int8_t pVn  =	accuVn[ indice];
					int8_t msg  =	ptr_c2v [ idex_Vn ];

					int8_t vAccu ;
					callSubSat(vAccu,pVn,msg);				
					Resu[idex_Vn] =  vAccu; 

					// check min & signe ;
					// int8_t testacc =  
					sign  ^=  ( vAccu < 0); 
	
					int8_t a = callAbs(vAccu,0); 
					
					// int8_t min_temp ;
					// callMax(min_temp,min1,a) ; 
					// min2 = callMin( min2, min_temp )  ;   
					
					min2 = minmax(min2,min1,a); 
					min1 = callMin( a,min1) ; 

				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{
					int8_t nMessage  ;
					int8_t temp = Resu[idex_Vn] ; 

					int8_t eval ; 

					// callEval(eval,min1,temp); 
					// int8_t min_t = min1 & ~eval ; 
					// int8_t min_u = min2 & eval ; 
					// int8_t min_  = min_t | min_u ; 
					int8_t min_ = ld_min_sorting(eval,min1,temp);


					int8_t Rsign ; 
					// callRsign(Rsign,sign,temp) ; 
					// callNmess(nMessage,Rsign,min_ ) ;
					nMessage = ld_rsign_nmess(min_,sign,temp); 

					// maj c2v
					ptr_c2v[idex_Vn] = nMessage ;
	
					callAddSat(temp,temp, nMessage) ;
					// callSubSat(temp,temp, -nMessage) ;


					int    indice = ptr_posVn[ idex_Vn ];
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