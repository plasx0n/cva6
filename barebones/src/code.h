

#include <stdio.h>
#include <stdint.h>
// Trame 
#include "trames/n3_repspc_k512_inter.h"

// SIMD INTER ONLY 

#define callRinstr(a,b,c) asm volatile("pl.r %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callFinstr(a,b,c) asm volatile("pl.f %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callSubSat(a,b,c) asm volatile("pl.subsat %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c));
#define callAddSat(a,b,c) asm volatile("pl.addsat %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callEval(a,b,c) asm volatile("pl.eval %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b),"r"(c)); 

#define callVADDREP1(a,b,c) asm volatile("pl.rep_addlow %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callVADDREP2(a,b,c) asm volatile("pl.rep_addhi %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callVREPSUM(a,b,c) asm volatile("pl.rep_addsign %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callVSPCMIN(a,b,c) asm volatile("pl.spc_amin %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c)); 

#define callVSPCCOMP(a,b,c) asm volatile("pl.spc_acmp %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c));        

#define callVSPCUPDATE1(a,b,c) asm volatile("pl.spc_idup %0,%1,%2" \
	                            : "=r" (a) \
	                            : "r" (b), "r" (c));     

#define callVSPCUPDATE2(a,b,c) asm volatile("pl.spc_max %0,%1,%2" \
                                : "=r" (a) \
                                : "r" (b),"r"(c)); 

static inline int32_t func_g3( int32_t rs1 , int32_t  rs2, int32_t  rs3  ){
		int32_t rd ; 
		asm volatile(" pl3.g %0,%1,%2,%3" \
								: "=r" (rd) \
								: "r" (rs1), "r" (rs2), "r"(rs3)); 
		return rd;
	}


void reorder(int32_t* dest, const int8_t* src, int N) // N: SIMD level 
{
    int8_t* ptr = (int8_t*) dest;
    for (int32_t i=0; i<N; i++)
    {
        for (int32_t z = 0; z < 4; z+= 1)
        {
            ptr[(4*i) + z] = src[z * N + i];
        }
    }
}

void ireorder(int8_t* dest, int32_t* src, int N) // N: SIMD level
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

#ifdef PL3 
    inline int32_t func_g(int32_t sa,int32_t la,int32_t lb){
        return func_g3(sa,la,lb); 
    }

#else

    int32_t func_g(int32_t sa,int32_t la,int32_t lb)
    {
        // solutionée par l'utilisation du masquage mais demande de faire les 2 calculs .. 
        // modèle LDPC 

        int32_t eval ;   
        callEval(eval,sa,0) ;  

        int32_t v1,v2,vf ; 
        callAddSat(v1,la,lb) ;
        callSubSat(v2,lb,la) ; 

        v1 = v1 & ~eval ;
        v2 = v2 & eval ; 
        vf = v1 | v2 ; 

        return vf ; 
    }

#endif

void node_8(int32_t* ptr_sum, int32_t *LLR , int N, char *fz_bits)
{ 
    if( N == 1 )
    {     
        callRinstr(*ptr_sum,*LLR, *fz_bits);
        return;
    }

    for( int x = 0 ; x < N/2; x += 1 )
    {
        callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
    }

         
    // ON CALCULE LA BRANCHE GAUCHE
    node_8(ptr_sum, (LLR+N), N/2, fz_bits);

    // ON CALCULE LES G
    for( int x = 0;  x < N/2; x += 1 )
    {
        (LLR+N)[ x ] = func_g( ptr_sum[x] , LLR[ x ], (LLR+N/2)[ x ]) ;
    }

    // ON CALCULE LA BRANCHE DROITE
    node_8(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
    
    // ON FAIT LES CALCUL DES H (XOR DES SP)
    for(int x = 0 ; x < N/2 ; x += 1 )
    {          
        ptr_sum[x] ^=ptr_sum[ x + (N/2) ] ; 
    }
}

void node(int32_t* ptr_sum, int32_t *LLR , int N, char *fz_bits)
{
    // ON CALCULE LA BRANCHE GAUCHE
    // get the node status 
    char enab1 = *fb_table_tileN++  ; 

    if(enab1==0) // r0 
    {
        // update res with G 
        for( int x = 0;  x < N/2; x += 1 )
        {
            (LLR+N)[ x ] = func_g( ptr_sum[x] ,  LLR[ x ],  (LLR+N/2)[ x ]) ;
        }

    }else if (enab1==1) // r1 
    {
        // ON CALCULE LES F
        for( int x = 0 ; x < N/2; x += 1 )
        {
            callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
            callRinstr(ptr_sum[x] ,(LLR+N)[x], 0);
        }

        // update Res with G 
        for( int x = 0;  x < N/2; x += 1 )
        {
            (LLR+N)[ x ] = func_g( ptr_sum[x] ,  LLR[ x ],  (LLR+N/2)[ x ]) ;
        }

    }else if (enab1==2) // REP
    {
        // Somme des LLR 
        // x > 0 ? PS => 0 
        // x < 0 ? PS => 1 

        // ON CALCULE LES F

        // int32_t tot1 = 0 ;
        // int32_t tot2 = 0 ;
        // int32_t tot3 = 0 ;
        // int32_t tot4 = 0 ; 

        int32_t t12 = 0 ;
        int32_t t34 = 0 ;

 
        // what if saturation ( data stored sur 8 bits) ?
        // 4 totaux différents 
        // possibilité de patch HW mais risque d'etre dégeux via masquage & stuf 
        // autre solution instru custom 

 

        for( int x = 0 ; x < N/2; x += 1 )
        {
            callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;

            // VADD4x8( (4x8 tot , 4x8 LLR)


                // VADD_REP1 ( int16x2_t txx , int16x2_t txx,  4x8 LLRx)

                                // VADD4x8 ( t12 ,t12 , LLR)
                                    // t12[15:0] += LLR[7:0]
                                    // t12[31:16] += LLR[15:0]

                // VADD_REP2 ( t34 ,t34, LLR)
                                    // t34[15:0] += LLR[24:16]
                                    // t34[31:16] += LLR[31:25]


            // printf("LLR %d : %d \n",x,    (LLR+N)[ x ]) ;
            // printf("LLR %d : %d ",x,  ( (LLR+N)[x]<<24 )>>24  ) ;
            // printf("LLR %d : %d ",x,  ( (LLR+N)[x]<<16 )>>24  ) ;
            // printf("LLR %d : %d ",x,  ( (LLR+N)[x]<<8  )>>24  ) ;
            // printf("LLR %d : %d \n",x,  ( (LLR+N)[x]     )>>24  ) ;

            // tot1 += ((LLR+N)[x]<<24 )>>24 ;
            // tot2 += ((LLR+N)[x]<<16 )>>24 ;
            // tot3 += ((LLR+N)[x]<<8  )>>24 ;
            // tot4 += ((LLR+N)[x]     )>>24 ;

            callVADDREP1(t12,t12,(LLR+N)[x]);

            // printf(" vaddrep1 %d  | t1 %d | t2 %d \n",t12
            // , (t12<<16)>>16
            // , (t12)>>16
            // ); 

            callVADDREP2(t34,t34,(LLR+N)[x]); 
            // printf(" vaddrep2 %d  | t3 %d | t4 %d \n",t34
            // , (t34<<16)>>16
            // , (t34)>>16
            // ); 


        }


    //     printf("TOTs\n") ; 
    //     printf("tot1 %d \n",tot1);
    //     printf("tot2 %d \n",tot2);
    //     printf("tot3 %d \n",tot3);
    //     printf("tot4 %d \n",tot4);

    //     printf(" vaddrep1 %d  | t1 %d | t2 %d \n",t12
    //     , (t12<<16)>>16
    //     , (t12)>>16 ); 

    //     printf(" vaddrep2 %d  | t3 %d | t4 %d \n",t34
    //     , (t34<<16)>>16
    //     , (t34)>>16 ); 


    //     if(tot1<0) 
    //         sum = 1; 
    //     if(tot2<0) 
    //         sum += 1<<8;
    //     if(tot3<0) 
    //         sum += 1<<16;
    //     if(tot4<0) 
    //         sum += 1<<24;  

        /*
        sum = (tot4 < 0)<<24  | (tot3 < 0)<<16  | (tot2 < 0)<<8 | (tot1 < 0)
        */
        int32_t sum = 0 ;         
        callVREPSUM(sum,t12,t34);


        // ne faire tourner ce for que si sum est >0 . save qq instrus 
        if (sum>0)
        {            
            for(int x = 0; x < N/2; x++)
                ptr_sum[x] = sum;
        }

        // update Res with G for next node 
        for( int x = 0;  x < N/2; x += 1 )
        {
            (LLR+N)[ x ] = func_g( ptr_sum[x] , LLR[ x ],  (LLR+N/2)[ x ]) ;
        }


    } else 
    if (enab1==3 ) // SPC 
    {
        
/*
        // 4 signes 
        int32_t sign1=0 ; 
        int32_t sign2=0 ; 
        int32_t sign3=0 ; 
        int32_t sign4=0 ; 

        // section à // par 4
        int8_t mina1 = 100  ; 
        int8_t mina2 = 100  ;
        int8_t mina3 = 100  ;
        int8_t mina4 = 100  ;

        int8_t idx_min1= 0 ; 
        int8_t idx_min2= 0 ;
        int8_t idx_min3= 0 ;
        int8_t idx_min4= 0 ;

*/

        int32_t sign = 0 ;
        int32_t idx_min = 0 ;
        int32_t idx_temp = 0 ; 

        // si min est init différement de > 0, necessite également de le abs() ds les ctrls 
        int32_t min = 0x70707070;
        int32_t mask=0;
        
        for( int x = 0 ; x < N/2; x += 1 )
        {
            callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
            callRinstr(ptr_sum[x],(LLR+N)[x], 0);



            // printf("LLR %d : %d \n",x,    (LLR+N)[ x ]) ;
            // printf("LLR %d : %d ",x,     ( (LLR+N)[x]<<24 )>>24  ) ;
            // printf("LLR %d : %d ",x,     ( (LLR+N)[x]<<16 )>>24  ) ;
            // printf("LLR %d : %d ",x,     ( (LLR+N)[x]<<8  )>>24  ) ;
            // printf("LLR %d : %d \n",x,   ( (LLR+N)[x]     )>>24  ) ;

            // printf("PS %d : %d \n",x,    ptr_sum[x]) ;
            // printf("PS %d : %d ",x,     ( ptr_sum[x] <<24 )>>24  ) ;
            // printf("PS %d : %d ",x,     ( ptr_sum[x] <<16 )>>24  ) ;
            // printf("PS %d : %d ",x,     ( ptr_sum[x] <<8  )>>24  ) ;
            // printf("PS %d : %d \n",x,   ( ptr_sum[x]     )>>24  ) ;

            // ne fonctionne pas puisque 4 morceaux différents 
/*
            sign1 ^= (ptr_sum[x]<<24)>>24   ;
            sign2 ^= (ptr_sum[x]<<16)>>24   ;
            sign3 ^= (ptr_sum[x]<< 8)>>24   ;
            sign4 ^= (ptr_sum[x]    )>>24   ;

            // printf("sign1 %d ",    sign1);
            // printf("sign2 %d ",    sign2);
            // printf("sign3 %d ",    sign3);
            // printf("sign4 %d \n",  sign4);

            // printf("sign %d ",     ( sign<<24 )>>24  ) ;
            // printf("sign %d ",     ( sign<<16 )>>24  ) ;
            // printf("sign %d ",     ( sign<<8  )>>24  ) ;
            // printf("sign %d \n",   ( sign     )>>24  ) ;


            int8_t a1 = abs( ((LLR+N)[ x ]<<24)>>24) ; 
            int8_t a2 = abs( ((LLR+N)[ x ]<<16)>>24) ;
            int8_t a3 = abs( ((LLR+N)[ x ]<< 8)>>24) ;
            int8_t a4 = abs( ((LLR+N)[ x ]    )>>24) ;

            
            if (a1<mina1)
            {
                mina1 = a1;
                idx_min1 = x ;     
            }

            if (a2<mina2)
            {
                mina2 = a2;
                idx_min2 = x ;     
            }

            if (a3<mina3)
            {
                mina3 = a3;
                idx_min3 = x ;     
            }

            if (a4<mina4)
            {
                mina4 = a4;
                idx_min4 = x ;     
            }         


*/
            

            sign^=ptr_sum[x] ; 

           
            callVSPCCOMP    (mask ,(LLR+N)[ x ],min) ; 
            callVSPCMIN     (min  ,(LLR+N)[ x ],min); 
            callVSPCUPDATE1 (idx_temp,mask,x ) ;
            callVSPCUPDATE2 (idx_min,idx_temp,idx_min) ; 


        }
   
        // INVERSION DE SIGNE 

        uint8_t* idx_min_ptr = (uint8_t*) idx_min ; 

        ptr_sum[idx_min_ptr[0]]^=sign ; 
        ptr_sum[idx_min_ptr[1]]^=sign ;
        ptr_sum[idx_min_ptr[2]]^=sign ;
        ptr_sum[idx_min_ptr[3]]^=sign ;

/* 
        uint8_t* sign_ptr = (uint8_t*) sign ;

        ptr_sum[idx_min_ptr[0]]^= sign_ptr[0] ; 
        ptr_sum[idx_min_ptr[1]]^= ( sign_ptr[1]<<8 ) ;
        ptr_sum[idx_min_ptr[2]]^= ( sign_ptr[2]<<16) ;
        ptr_sum[idx_min_ptr[3]]^= ( sign_ptr[3]<<24) ;
*/


/*
        printf("sign1 %d min1 %d  idx1 %d \n" ,sign1,  mina1,idx_min1);
        printf("sign %d min %d  idx %d \n" ,sign2,  mina2,idx_min2);
        printf("sign %d min %d  idx %d \n" ,sign3,  mina3,idx_min3);
        printf("sign %d min %d  idx %d \n" ,sign4,  mina4,idx_min4); 

        ptr_sum[idx_min1]^=sign1 ;
        ptr_sum[idx_min2]^=(sign2<<8) ;
        ptr_sum[idx_min3]^=(sign3<<16) ;
        ptr_sum[idx_min4]^=(sign4<<24) ;
*/



        // update Res with G for next node 
        for( int x = 0;  x < N/2; x += 1 )
        {
            (LLR+N)[ x ] = func_g( ptr_sum[x] ,  LLR[ x ],  (LLR+N/2)[ x ]) ;
        }


    } else // opération normale 
    {   
        // if ici permet de mieux dérouler le code afterwards ( reduc insn reduc cycles ) ? 
        // si Noeud inferieur n'est pas particulier 
        if((N/2)==8){                          
                                
            // ON CALCULE LES F
            for( int x = 0 ; x < N/2; x += 1 )
            {
                callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
            }

            // Recursif Node_8 
            node_8( ptr_sum, (LLR+N), N/2, fz_bits) ; 

            // ON CALCULE LES G
            for( int x = 0;  x < N/2; x += 1 )
            {
                (LLR+N)[ x ] = func_g( ptr_sum[x] , LLR[ x ],  (LLR+N/2)[ x ]) ;
            }
        }
        else{
            // ON CALCULE LES F
            for( int x = 0 ; x < N/2; x += 1 )
            {
                callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
            }
            
            node( ptr_sum, (LLR+N), N/2, fz_bits);
                
            // ON CALCULE LES G
            for( int x = 0;  x < N/2; x += 1 )
            {
                (LLR+N)[ x ] = func_g( ptr_sum[x] , LLR[ x ],  (LLR+N/2)[ x ]) ;
            }
        }
        
    }
        

    // ON CALCULE LA BRANCHE DROITE
    // get the node status 
    char enab2 = *fb_table_tileN++  ; 
    
    if(enab2==0) // r0 
    {
        //gestion de ptr ... 

    }else if (enab2==1) // r1 
    {
        // copy leaf calc to PS  
        for( int x = 0 ; x < N/2; x += 1 )
        {
            callRinstr((ptr_sum+N/2)[x],(LLR+N)[x], 0);
        }

    }else if (enab2==2) // REP
    {
        int32_t t12 = 0 ;
        int32_t t34 = 0 ;

        for( int x = 0 ; x < N/2; x += 1 )
        {
            callVADDREP1(t12,t12,(LLR+N)[x]);
            callVADDREP2(t34,t34,(LLR+N)[x]); 
        } 

        int32_t sum = 0 ;         
        callVREPSUM(sum,t12,t34);

        if(sum>0){    
            for (int x = 0; x < N/2; x++)
            (ptr_sum+N/2)[x] = sum ; 
        }
    }
    else if (enab2==3) // SPC
    {

/*
        int32_t sign1=0 ; 
        int32_t sign2=0 ; 
        int32_t sign3=0 ; 
        int32_t sign4=0 ; 

        int8_t idx_min1= 0 ; 
        int8_t idx_min2= 0 ;
        int8_t idx_min3= 0 ;
        int8_t idx_min4= 0 ;

                    // section à // par 4
            int8_t mina1 = 100  ; 
            int8_t mina2 = 100  ;
            int8_t mina3 = 100  ;
            int8_t mina4 = 100  ;

*/


        int32_t sign = 0 ;
        int32_t idx_min = 0 ;
        int32_t idx_temp = 0 ; 
        int32_t min = 0x70707070;
        int32_t mask=0;

        for( int x = 0 ; x < N/2; x += 1 )
        {
            callRinstr((ptr_sum+N/2)[x],(LLR+N)[x], 0);

            // ne fonctionne pas puisque 4 morceaux différents 
            sign^=ptr_sum[x] ; 

            // callVABS(a,(LLR+N)[ x ],0) ; 

            callVSPCCOMP(mask , (LLR+N)[ x ] , min ) ; 
            callVSPCMIN( min,(LLR+N)[ x ],min ); 
            callVSPCUPDATE1(idx_temp,mask,x ) ;
            callVSPCUPDATE2(idx_min,idx_temp,idx_min) ;    

        }

        uint8_t* idx_min_ptr = (uint8_t*) idx_min ; 

        ptr_sum[idx_min_ptr[0]]^=sign ; 
        ptr_sum[idx_min_ptr[1]]^=sign ;
        ptr_sum[idx_min_ptr[2]]^=sign ;
        ptr_sum[idx_min_ptr[3]]^=sign ;

/*
        ptr_sum[idx_min1]^=sign1 ;
        ptr_sum[idx_min2]^=(sign2<<8) ;
        ptr_sum[idx_min3]^=(sign3<<16) ;
        ptr_sum[idx_min4]^=(sign4<<24) ;
*/
    



    }
        
    else // opération normale 
    {
        if( (N/2)==8 ){
            node_8(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
        }else{
            node(ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
        }
    }  

    // ON FAIT LES CALCUL DES H (XOR DES SP)
    for(int x = 0 ; x < N/2 ; x += 1 )
    {          
        ptr_sum[x] ^=ptr_sum[ x + (N/2) ];    
    }
}

// calcule unqiuement le premier f ,  g  et le dernier Xor(h)
void node_top(int32_t* ptr_sum, int32_t *LLR , int N, char *fz_bits)
{

    // if (*fb_table_tileN != 4) {
    //     printf("(EE) TOP LEVEL TILE IS FROZEN !\n");
    //     exit(0);
    // }

    fb_table_tileN+=1 ; 

    // une fois F pr la branche gauche 
    for( int x = 0 ; x < N/2; x += 1 )
    {
        callFinstr( (LLR+N)[ x ], LLR[ x ],(LLR+N/2)[ x ])  ;
    }

    // tt la branche gauche 
    const int not_frozen_value = 4;
    if (*fb_table_tileN++ != not_frozen_value) {
        printf("(EE) Un truc impossible vient de se produire (1:%d)\n", *(fb_table_tileN-1));
        
    } else {
        node( ptr_sum, (LLR+N), N/2, fz_bits);
    }

    // une fois G pour la branche droite   
    for( int x = 0;  x < N/2; x += 1 )
    {

        (LLR+N)[ x ] = func_g( ptr_sum[x] ,  LLR[ x ], (LLR+N/2)[ x ]) ;
    }

    // tt la branche droite 
    if (*fb_table_tileN++ != not_frozen_value) {
        printf("(EE) Un truc impossible vient de se produire (1:%d)\n", *(fb_table_tileN-1));
        
    } else {
         node( ptr_sum+ N/2, (LLR+N), N/2,  fz_bits+ N/2 );
    }

     // ON FAIT LES CALCUL DES H (XOR DES SP)
    for(int x = 0 ; x < N/2 ; x += 1 )
    {          
        // xor
        ptr_sum[x] ^=ptr_sum[ x + (N/2) ]; 
    }

}

