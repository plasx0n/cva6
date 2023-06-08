/*

    Quantif du decodeur pour insertion sur le cibles RV 

	SUR cible RV : la tc ne peut supporter des flotants 
	le test doit donc utiliser les trames Ldpcs déja mises en formes 

     
*/


// CONFIGURATION SC SYS basique 
// #define BASE_FUNC_8b
// #define EXT_FUNC_8b

// CONFIGURATION SC SYS basique + Instrus 
#define abs(N) ((N<0)?(-N):(N))

#define BASE_FUNC_8b 
#define EXT_FUNC_8b

#include "includes.h"

// goes in heap 

    int8_t LLR[2*codw_N]       = {0} ; 
    int8_t PS[codw_N]          = {0};    

    int8_t decode_out_[K ]     = {0} ; 

// main 
int main(int argc , char * argv[]) 
{

    for (int i = 0; i < codw_N; i++)    
        LLR[i] = codw[i] ;

    long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 

    // 4 cycles pour sortir les infos 
	cycle_start= cycles()-4;
	insn_start = insn()-4; 

    // node 8   => standard SC 
    // node top => Fast 
    
    node_top( PS, LLR, codw_N, froozen_bits );
    // node_top( PS, LLR, codw_N, froozen_bits );

	cycle_stop= cycles()-4;
	insn_stop = insn()-4; 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 

	printf("cycles	: %d \n", cycle_tot) ; 
	printf("insn	: %d \n", insn_tot);

    int j= 0; 
    for( int i=0 ; i <codw_N ; i++)
    {
        if( froozen_bits[i]==0 )
        decode_out_[j++] = PS[i] ;
    }

    printf("errors \n") ;
    for (int i = 0; i < K; i++)  
    {
        if(decode_out_[i] != U[i])
        {
            printf("E @ ") ;
            printf("%d \n",i) ;
            printf("decode_out: %d \n",decode_out_[i] ) ;
            printf("U: %d \n",U[i] ) ;
        } 
    }
    printf(" DONE \n") ; 
 


}