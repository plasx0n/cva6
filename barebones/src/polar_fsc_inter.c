/*

plusieurs problèmes identifiés dans le simd 4x8 Polaire 
FSC only  :
    

    noeuds RO et R1 doivent fonctionner mais c'est tout 

    noeuds pas fonctionels immédiatements 

    REP : 4 totaux séparés 
        4 totaux différents 
        possibilité de patch HW mais risque d'etre dégeux via masquage & stuf 
        autre solution instru custom 
    
    SPC : pire encore 
        certains noeuds doivent sort les minimums de chaque elements de trames 
        8  |8  |8  |8 
        chaque element peut avoir un min différent 

        nécessite l'utilisation de la fonction abs()  



     
*/

#include "stdint.h"
//#define PL3
#include "code.h"

    int32_t data_out[K] ;
    int8_t codw_out[codw_N*2] ;

// main 
int main() 
{


	long insn_start,insn_stop,insn_tot ; 
	long cycle_start,cycle_stop , cycle_tot ; 

    printf("POLAR FSC 4*int8 vecto inter  N:%d K:%d\n" , codw_N,K);

    int32_t LLR[2*codw_N]       = {0} ; 
    int32_t PS[codw_N]          = {0};    
    int32_t decode_out_[K ]     = {0} ; 

    // 4 cycles pour sortir les infos 
	cycle_start= cycles()-4;
	insn_start = insn()-4; 


    reorder(LLR,codw,codw_N) ;

    // ------------

    // direct node_8 => pas d'application du FSC
    // node_8( PS, LLR, codw_N, froozen_bits );

   // node_top => controle pour le FSC
    node_top( PS, LLR, codw_N, froozen_bits );

    // ------------
    int j= 0;
    for( int i=0 ; i <codw_N ; i++)
    {
        if(!froozen_bits[i])
        data_out[j++] = PS[i] ;
    }

    ireorder(codw_out,data_out,K) ; 

    // -------
    cycle_stop= cycles()-4;
	insn_stop = insn()-4; 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 

	printf("\n|=======================|\n");
	printf("cycles	: %d \n", cycle_tot) ; 
	printf("insn	: %d \n", insn_tot); 
	printf("|=======================|\n");
	// ------------

    printf("errors \n") ;
    for (int i = 0; i < K; i++)  
    {
        if(codw_out[i] != U[i])
        {
            printf("E @ ") ;
            printf("%d \n",i) ;
            printf("codw_out[i]: %d \n",codw_out[i] ) ;
            printf("U: %d \n",U[i] ) ;
        } 
    }
    printf(" DONE \n") ; 



    return 0 ; 
}
