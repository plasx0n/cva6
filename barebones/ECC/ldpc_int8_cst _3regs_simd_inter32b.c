/*
   SERV dependent à cause des instrus .. 
   voir pour refractor les vars temporaires 
   Ajouter eventuellement une autre instru dans le kernel .. 

*/

#include <stdlib.h>
#include <stdint.h>



#define CODE   ("LDPC")
#define ordo   ("Horizontal layered")
#define qtf    ("int8_tx4")
#define iter 	10
#define nb_VN 	34
#define nb_CN 	14



// deg de chaque CN
int8_t deg_Cns[] = 
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
 

int32_t accuVn[34] ; 

int8_t trames[] = {
3,5,-4,-4,0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4, 
-6,-4,5,-4,0,2,1,5,4,0,5,6,0,9,5,6,4,-7,-1,-4,-4,7,-7,6,1,-2,2,4,1,8,0,5,-9,5,
3,5,5,5,-9,2,1,5,-5,-9,-4,-3,-9,9,5,6,-5,2,-1,-4,5,7,2,-3,1,7,-7,-5,1,8,9,-4,0,-4,
3,5,-4,5,0,2,-8,5,-5,0,5,6,-9,0,5,6,-5,2,-1,5,-4,-2,-7,-3,1,-2,-7,4,1,-1,0,-4,0,-4,

3,5,-4,-4,0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4, 
-6,-4,5,-4,0,2,1,5,4,0,5,6,0,9,5,6,4,-7,-1,-4,-4,7,-7,6,1,-2,2,4,1,8,0,5,-9,5,
3,5,5,5,-9,2,1,5,-5,-9,-4,-3,-9,9,5,6,-5,2,-1,-4,5,7,2,-3,1,7,-7,-5,1,8,9,-4,0,-4,
3,5,-4,5,0,2,-8,5,-5,0,5,6,-9,0,5,6,-5,2,-1,5,-4,-2,-7,-3,1,-2,-7,4,1,-1,0,-4,0,-4,
} ;


#define callSign(rd,rs1,rs2) asm volatile("ld.sign %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 
								
// basiquement reviens au meme 
inline int32_t callAbs(int32_t rs1,int32_t rs2)
{
	int32_t rd ; 
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

inline int32_t callMin(int32_t rs1,int32_t rs2)
{
	int32_t rd ; 
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

inline int32_t Sign(int32_t rs1,int32_t rs2)
{
	int32_t rd ; 
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



static inline int32_t sign3( int32_t rs1 , int32_t rs2, int32_t rs3  ){
    int32_t rd ; 
    asm volatile(" ld3_sign3 %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

static inline int32_t minmax( int32_t rs1 , int32_t rs2, int32_t rs3  ){
    int32_t rd ; 
    asm volatile(" ld3_minmax %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

static inline int32_t ld_rsign_nmess( int32_t rs1 , int32_t rs2, int32_t rs3  ){
    int32_t rd ; 
    asm volatile(" ld3_rsign_nmess %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

static inline int ld_min_sorting( int32_t rs1 , int32_t rs2, int32_t rs3  ){
    int32_t rd ; 
    asm volatile(" ld3_min_sorting %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}


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
	// ordering is part of the decoder 
	reorder(accuVn,trames,34); 

	int32_t Resu[32]  ;

		for(int l=0;l<iter;l++)
		{
			int32_t* ptr_posVn = posVn ;
			int32_t* ptr_c2v   = c2v ;

			// parcours des CN
			for( int idex_Cn = 0 ; idex_Cn < nb_CN ; idex_Cn++)
			{

				int32_t min1    = (int32_t) 0x7F7F7F7F;
				int32_t min2    = (int32_t) 0x7F7F7F7F;
				int32_t sign    =   0 ;

				// parcours des VN liés au Cn courant
				int degCn = deg_Cns[idex_Cn];
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{

					int indice = ptr_posVn[ idex_Vn ];
					int32_t pVn  =	accuVn[ indice];
					int32_t msg  =	ptr_c2v [ idex_Vn ];

					int32_t vAccu ;
					callSubSat(vAccu,pVn,msg);				
					Resu[idex_Vn] =  vAccu; 

					int32_t SignVAcc ;
					callSign(SignVAcc,vAccu,0);
					sign^= SignVAcc; 
	
					int32_t a = callAbs(vAccu,0); 
					
					// int8_t min_temp ;
					// callMax(min_temp,min1,a) ; 
					// min2 = callMin( min2, min_temp )  ;   
					
					min2 = minmax(min2,min1,a); 
					min1 = callMin( a,min1) ; 

				}

				// parcours des VN liés au Cn courant
				for( int idex_Vn =0 ; idex_Vn < degCn ; idex_Vn++)
				{
					int32_t nMessage  ;
					int32_t temp = Resu[idex_Vn] ; 

					int32_t eval ; 

					// callEval(eval,min1,temp); 
					// int8_t min_t = min1 & ~eval ; 
					// int8_t min_u = min2 & eval ; 
					// int8_t min_  = min_t | min_u ; 
					int32_t min_ = ld_min_sorting(eval,min1,temp);


					int32_t Rsign ; 
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
	printf("%s(%d,%d) :: %s:: %d ite :: %s\n",CODE,nb_VN,nb_VN-nb_CN,ordo ,iter,qtf) ; 
	printf("GENEREE : %s - %s\n", __DATE__, __TIME__);

	long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 
   	long time_start,time_stop , time_tot ;

	// re-order operation 
	trameCheck(codw1,err_1) ; 
	trameCheck(codw2,err_2) ; 
	trameCheck(codw3,err_3) ; 
	trameCheck(codw4,err_4) ;
  	
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