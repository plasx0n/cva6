#include "stdlib.h"

#define puts printf 
#define abs(N) ((N<0)?(-N):(N))

#include "turbo_k512.h"


// #define CST 

    #define callMax(rd,rs1,rs2) asm volatile("ld.max %0,%1,%2" \
    	                            : "+r" (rd) \
    	                            : "r" (rs1), "r" (rs2));

    #define callsubsat(rd,rs1,rs2) asm volatile("ld.subsat %0,%1,%2" \
    	                            : "+r" (rd) \
    	                            : "r" (rs1), "r" (rs2));



void hard_decide_seq(int *in, int *out, const int size)
{
	for (int i = 0; i < size; i++)
		out[i] = in[i] < 0;
}


#ifndef CST
    #define max(a,b) \
       ({ __typeof__ (a) _a = (a); \
           __typeof__ (b) _b = (b); \
         _a > _b ? _a : _b; })

    int max_(int a, int b){
        return max(a, b);
    }

    int mmax(t_state a){
        const int l1 = max_(max_(a.v[0], a.v[1]), max_(a.v[2], a.v[3]) );
        const int l2 = max_( max_(a.v[4], a.v[5]), max_(a.v[6], a.v[7]) );
        return max_(l1, l2);
    }
#endif 
#ifdef CST
    int mmax(t_state a){
        int l1 ;
        int l2 ;
        int l3 ;
        callMax(l1,a.v[0], a.v[1]) ; 
        callMax(l2,a.v[2], a.v[3]) ;
        callMax(l1,l1,l2); 

        callMax(l2, a.v[4], a.v[5]); 
        callMax(l3, a.v[6], a.v[7]);
        callMax(l2,l2,l3);

        callMax(l3,l1,l2); 
        return (l3);
    }

#endif 

struct t_state init_state( ){
    struct t_state res;
    res.v[0] = 32767;
    res.v[1] = 32767;
    res.v[2] = 32767;
    res.v[3] = 32767;
    res.v[4] = 32767;
    res.v[5] = 32767;
    res.v[6] = 32767;
    res.v[7] = 32767;
    return res;
}
t_metric init_metric(int value){
    t_metric res;
    res.v[0] = value;
    res.v[1] = value;
    return res;
}


// Calcul des transitions suivant le treillis LTE 
    // alpha S-1 > S
#ifndef CST
t_state p_state_alpha(t_state alpha, t_metric gamma){
    t_state res;
    res.v[0] = max_(alpha.v[0] + gamma.v[0], alpha.v[1] - gamma.v[0]);
    res.v[1] = max_(alpha.v[3] + gamma.v[1], alpha.v[2] - gamma.v[1]);
    res.v[2] = max_(alpha.v[4] + gamma.v[1], alpha.v[5] - gamma.v[1]);
    res.v[3] = max_(alpha.v[7] + gamma.v[0], alpha.v[6] - gamma.v[0]);
    res.v[4] = max_(alpha.v[1] + gamma.v[0], alpha.v[0] - gamma.v[0]);
    res.v[5] = max_(alpha.v[2] + gamma.v[1], alpha.v[3] - gamma.v[1]);
    res.v[6] = max_(alpha.v[5] + gamma.v[1], alpha.v[4] - gamma.v[1]);
    res.v[7] = max_(alpha.v[6] + gamma.v[0], alpha.v[7] - gamma.v[0]);
    return res;
}

    // BETA S > S-1
t_state p_state_beta(t_state beta, t_metric gamma){
    t_state res;
    res.v[0] = max_(beta.v[0] + gamma.v[0], beta.v[4] - gamma.v[0]);
    res.v[1] = max_(beta.v[4] + gamma.v[0], beta.v[0] - gamma.v[0]);
    res.v[2] = max_(beta.v[5] + gamma.v[1], beta.v[1] - gamma.v[1]);
    res.v[3] = max_(beta.v[1] + gamma.v[1], beta.v[5] - gamma.v[1]);
    res.v[4] = max_(beta.v[2] + gamma.v[1], beta.v[6] - gamma.v[1]);
    res.v[5] = max_(beta.v[6] + gamma.v[1], beta.v[2] - gamma.v[1]);
    res.v[6] = max_(beta.v[7] + gamma.v[0], beta.v[3] - gamma.v[0]);
    res.v[7] = max_(beta.v[3] + gamma.v[0], beta.v[7] - gamma.v[0]);
    return res;
}
#endif


#ifdef CST
t_state p_state_alpha(t_state alpha, t_metric gamma){
    t_state res;
    callMax( res.v[0], alpha.v[0] + gamma.v[0], alpha.v[1] - gamma.v[0]);
    callMax( res.v[1], alpha.v[3] + gamma.v[1], alpha.v[2] - gamma.v[1]);
    callMax( res.v[2], alpha.v[4] + gamma.v[1], alpha.v[5] - gamma.v[1]);
    callMax( res.v[3], alpha.v[7] + gamma.v[0], alpha.v[6] - gamma.v[0]);
    callMax( res.v[4], alpha.v[1] + gamma.v[0], alpha.v[0] - gamma.v[0]);
    callMax( res.v[5], alpha.v[2] + gamma.v[1], alpha.v[3] - gamma.v[1]);
    callMax( res.v[6], alpha.v[5] + gamma.v[1], alpha.v[4] - gamma.v[1]);
    callMax( res.v[7], alpha.v[6] + gamma.v[0], alpha.v[7] - gamma.v[0]);
    return res;
}

// BETA S > S-1
t_state p_state_beta(t_state beta, t_metric gamma){
    t_state res;
    callMax(res.v[0] ,beta.v[0] + gamma.v[0], beta.v[4] - gamma.v[0]);
    callMax(res.v[1] ,beta.v[4] + gamma.v[0], beta.v[0] - gamma.v[0]);
    callMax(res.v[2] ,beta.v[5] + gamma.v[1], beta.v[1] - gamma.v[1]);
    callMax(res.v[3] ,beta.v[1] + gamma.v[1], beta.v[5] - gamma.v[1]);
    callMax(res.v[4] ,beta.v[2] + gamma.v[1], beta.v[6] - gamma.v[1]);
    callMax(res.v[5] ,beta.v[6] + gamma.v[1], beta.v[2] - gamma.v[1]);
    callMax(res.v[6] ,beta.v[7] + gamma.v[0], beta.v[3] - gamma.v[0]);
    callMax(res.v[7] ,beta.v[3] + gamma.v[0], beta.v[7] - gamma.v[0]);
    return res;
}

#endif 


// VA POSER PROBLEME POUR SIMD 

// transition (joint prob) n-normalisé S-1 > S
    // transitions 0 ::positive ::+  
    // STD LTE 
t_state pp(t_state alpha, t_metric gamma, t_state beta){
    t_state ext_1;
    ext_1.v[0] = alpha.v[0] + gamma.v[0] + beta.v[0];
    ext_1.v[1] = alpha.v[1] + gamma.v[0] + beta.v[4];
    ext_1.v[2] = alpha.v[2] + gamma.v[1] + beta.v[5];
    ext_1.v[3] = alpha.v[3] + gamma.v[1] + beta.v[1];
    ext_1.v[4] = alpha.v[4] + gamma.v[1] + beta.v[2];
    ext_1.v[5] = alpha.v[5] + gamma.v[1] + beta.v[6];
    ext_1.v[6] = alpha.v[6] + gamma.v[0] + beta.v[7];
    ext_1.v[7] = alpha.v[7] + gamma.v[0] + beta.v[3];
    return ext_1;
}
// transitions 1 ::negatives :: -
// ??? dans l'autre sens ? ?
t_state mp(t_state alpha, t_metric gamma, t_state beta){
    t_state ext_0;
    ext_0.v[0] = alpha.v[0] - gamma.v[0] + beta.v[4];
    ext_0.v[1] = alpha.v[1] - gamma.v[0] + beta.v[0];
    ext_0.v[2] = alpha.v[2] - gamma.v[1] + beta.v[1];
    ext_0.v[3] = alpha.v[3] - gamma.v[1] + beta.v[5];
    ext_0.v[4] = alpha.v[4] - gamma.v[1] + beta.v[6];
    ext_0.v[5] = alpha.v[5] - gamma.v[1] + beta.v[2];
    ext_0.v[6] = alpha.v[6] - gamma.v[0] + beta.v[3];
    ext_0.v[7] = alpha.v[7] - gamma.v[0] + beta.v[7];
    return ext_0;
}

t_metric c_gamma(int sys, int par){
    t_metric g;
    g.v[0] = sys + par;
    g.v[1] = sys - par;
    return g;
}
int div0_75( int a) {
    int sign = a > 0 ; 
    int A = abs(a) ; 
    int B = A >> 2 ; 
    int C = A - B ; 
    return (sign==0)? -C :C ; 
}


// i_sys :: 1 ere partie des infos du vecteur, full  
//          output du premier decodeur 
// i_par :: moitié suivante des infos 
//          same mais l'autre moitié 
// i_ext :: retour du second decoder d'apres o_ext
//          message original mais interleaved 

void do_action(
        int* i_sys,
        int* i_par,
        int* i_ext,
        int* o_ext,
        int lastIter
) {

    #ifdef DEBUG 

    dump("SYS", (int*)i_sys, _KBITS);
    dump("PAR", (int*)i_par, _KBITS);
    dump("?XT", (int*)i_ext, _KBITS, 8);

    #endif 

    
    //double array, avec pr idex == nb de bits k
    t_state     alpha[_KBITS];
    t_metric    gamma[_KBITS];
    int         temp[_KBITS];

    t_state alpha_z1 = init_state( );

    
    for (int k = 0; k < _KBITS; k++){

            // printf("do_action() 1 \n"); 

            alpha[k] = alpha_z1; // ON MEMORISE LES VALEURS DE ALPHA // necessaires pour next state 

            int llr_ext;
            // int val = div0_75(i_ext[k]) ;
            // int val = (i_ext[k] *3)/4 ; 
            int val ; 
            #ifdef CST
            callsubsat(val,i_ext[k],0); 
            #else 
            val = (i_ext[k] *3)/4 ;
            #endif 

            if( lastIter == 0) llr_ext  = val ; 
            else               llr_ext  = i_ext[k];

            const int llr_sys = i_sys[k];
            const int llr_par = i_par[k];
            // scaled max log map 
            // app-LLR => l(uk) + l_sys + le 
            const int sys     =  (llr_ext + llr_sys)>>1 ; //0.5f scaling 
            const int par     =  (          llr_par)>>1 ;
            // algo max log map 
            const t_metric g   = c_gamma(sys, par);

            alpha_z1 = p_state_alpha( alpha_z1, g );

            temp [k] = llr_ext + llr_sys;
            gamma[k] = g;
        }

        t_state beta_z1 = init_state( );
        
        
        //  juste la tail 
        for (int k = (_KBITS_TB-1); k > (_KBITS-1); k--){

            // printf("do_action() 2 \n"); 
            
            const int llr_sys = i_sys[k];
            const int llr_par = i_par[k];
            const int llr_ext = 0;
            // llr ext bien nécessaire ici ? ==> non
            const int sys     =  (llr_ext + llr_sys) >>1 ;
            const int par     =  (          llr_par) >>1 ;
            // pk refaire gamma ? ptet opti ici à voir avec le scaling sur llr_sys & llr_par
            const t_metric g    = c_gamma(    sys,      par);
            beta_z1             = p_state_beta( beta_z1, g );
        }

        // full treillis 
        // transitions 
       
        for (int k = _KBITS - 1; k >= 0; k--){
            
            // printf("do_action() 3 \n"); 

            // redclération :: lisibilité ?? 
            t_metric g          = gamma[k];
            const t_state betac = beta_z1;
            beta_z1             = p_state_beta( beta_z1, g );
            

            // algo max-log-map 
            // app LLR =        MAxR1( alpha + gamma +beta)
            //              -   MAxR0 (alpha + gamma +beta)   
            //   avec les states transitions 
            //mp && pp ?? quel algo ? 
            const t_state ext_1 = pp(alpha[k], gamma[k], betac);
            const t_state ext_0 = mp(alpha[k], gamma[k], betac);

            const int max1     = mmax( ext_1 );
            const int max0     = mmax( ext_0 );


            // maxv:: app_llr :: l(uk|y)
            const int maxv     = max1 - max0; 

            // fait ressortir Le depuis l'equ 
            // le = maxv - l_i_ext_ -Lsys
            // temp :: l_i_ext_ -Lsys ( calc dans alpha) 
            const int resu     = maxv - temp[k];
            if( lastIter == 1 ) o_ext[k] = maxv;
            else                   o_ext[k] = resu;
        }

        #ifdef DEBUG 
        dump("EXT", (int*)o_ext, _KBITS);
        #endif 

}

    int sys_N[]={-5,-5,-5,5,5,5,-5,5,-5,-5,-5,-5,5,5,5,-5,5,5,-5,-5,5,5,5,5,5,5,5,5,5,-5,-5,-5,-5,-5,-5,-5,5,5,5,5,-5,-5,-5,5,-5,-5,5,5,5,5,5,5,-5,5,-5,-5,-5,-5,-5,-5,-5,-5,5,-5,-5,5,-5,5,-5,5,-5,5,-5,-5,5,5,5,5,5,5,5,5,-5,-5,-5,5,5,-5,-5,5,-5,-5,5,5,5,-5,5,5,-5,-5,-5,5,5,5,5,5,-5,5,-5,5,5,-5,-5,-5,5,5,-5,-5,5,-5,-5,-5,5,5,5,5,5,-5,5,-5,-5,5,-5,5,5,-5,-5,5,5,5,-5,5,-5,-5,-5,5,5,-5,-5,-5,-5,-5,5,-5,-5,5,5,-5,5,5,-5,-5,5,5,-5,5,5,5,5,-5,5,-5,-5,5,5,5,5,-5,-5,5,5,-5,-5,5,-5,-5,-5,-5,-5,5,-5,5,5,-5,5,5,5,-5,5,5,5,-5,5,-5,-5,5,5,-5,5,5,5,-5,-5,5,5,-5,5,5,5,5,-5,5,-5,5,5,-5,-5,-5,5,-5,5,5,5,5,5,5,5,5,5,-5,-5,5,-5,5,-5,-5,-5,5,-5,-5,-5,5,5,-5,5,5,5,5,5,5,5,-5,5,5,5,5,-5,5,5,5,-5,-5,5,-5,5,-5,5,-5,5,-5,-5,-5,-5,5,-5,5,-5,5,5,5,5,5,5,5,-5,-5,5,5,-5,-5,5,-5,-5,5,-5,5,-5,-5,-5,-5,5,-5,-5,5,5,5,5,-5,-5,5,5,-5,5,5,5,-5,-5,5,-5,5,5,5,5,-5,5,-5,5,-5,5,-5,-5,5,5,5,5,-5,-5,-5,5,-5,5,5,-5,-5,-5,5,5,-5,5,5,-5,-5,5,-5,-5,5,-5,-5,-5,5,-5,-5,5,-5,5,-5,-5,-5,5,-5,5,5,5,-5,5,5,5,-5,5,5,5,-5,5,-5,5,5,-5,-5,-5,5,-5,-5,5,-5,-5,-5,5,-5,-5,5,5,5,5,5,5,-5,5,-5,-5,5,5,-5,5,5,-5,-5,-5,5,-5,-5,-5,5,-5,5,-5,5,5,5,-5,5,-5,5,5,5,5,5,5,-5,5,5,5,5,-5,-5,5,-5,5,5,5,5,-5,5,5,5,5,-5,5,-5,-5,-5,-5,5,-5,-5,-5,5,5,-5,5,-5,5,5,-5,5,-5,-5,5,5,5,-5,-5,5,5,5,5,5,5,-5,5,5,-5,5,-5,-5,5,5,-5,5,-5,-5,5,5,5,5,5, } ; 
    int sys_I[]={-5,-5,-5,-5,5,5,5,-5,-5,5,-5,-5,5,-5,-5,5,5,5,-5,5,-5,-5,-5,5,5,5,5,5,5,5,5,-5,5,-5,-5,5,5,-5,5,-5,5,-5,5,-5,-5,5,5,-5,5,5,-5,5,5,-5,5,5,5,-5,-5,-5,5,5,-5,5,5,-5,5,5,-5,5,5,5,-5,-5,-5,5,-5,-5,5,-5,-5,5,5,5,-5,5,5,-5,5,5,5,-5,5,-5,-5,5,5,5,-5,-5,5,5,-5,-5,5,5,-5,-5,5,-5,-5,5,-5,5,5,-5,5,5,5,-5,-5,5,5,5,5,5,-5,-5,5,-5,-5,-5,-5,-5,5,-5,-5,-5,-5,-5,-5,-5,5,-5,-5,5,5,5,5,5,-5,5,5,5,5,-5,5,5,-5,5,-5,-5,5,-5,5,-5,-5,-5,-5,5,5,-5,-5,-5,-5,5,5,5,-5,5,-5,5,-5,5,-5,5,5,-5,5,5,-5,-5,5,-5,5,-5,5,5,-5,5,-5,-5,5,5,5,-5,5,-5,-5,5,5,5,-5,-5,5,-5,-5,-5,5,-5,-5,5,-5,-5,5,-5,5,5,5,5,5,-5,5,-5,5,-5,-5,5,5,5,5,-5,5,-5,-5,5,5,-5,-5,5,-5,5,-5,-5,5,5,5,5,5,5,5,5,-5,5,5,-5,5,-5,-5,-5,-5,-5,-5,-5,5,-5,-5,5,5,-5,5,5,-5,5,-5,5,-5,5,5,5,-5,5,5,5,-5,5,-5,-5,5,-5,-5,5,5,5,5,5,5,5,5,5,5,-5,5,5,5,5,-5,5,5,-5,5,5,5,-5,5,5,5,-5,-5,5,-5,5,-5,-5,-5,5,5,-5,5,-5,5,5,-5,5,-5,5,5,5,5,5,-5,-5,-5,5,5,-5,-5,-5,-5,5,-5,-5,5,5,5,5,5,-5,-5,-5,5,-5,5,-5,5,-5,5,5,5,5,5,-5,5,-5,5,5,5,5,5,-5,-5,5,-5,5,-5,5,-5,-5,-5,5,-5,-5,-5,5,5,5,-5,-5,-5,-5,5,5,-5,5,5,-5,5,5,5,-5,-5,5,5,-5,5,5,-5,5,-5,5,5,-5,5,5,-5,5,-5,-5,-5,-5,-5,5,5,-5,-5,-5,5,5,-5,5,5,5,-5,5,-5,-5,-5,-5,5,-5,5,-5,-5,5,5,-5,-5,5,-5,5,-5,5,5,-5,5,-5,5,5,-5,5,-5,-5,5,5,5,5,-5,5,-5,-5,5,5,-5,5,5,5,5,-5,5,5,-5,5,5,5,5,5,-5,-5,5,5,5,-5,-5,-5,5, } ; 
    int par_N[]={-5,5,-5,-5,5,-5,5,5,5,-5,5,5,-5,-5,5,5,-5,5,5,-5,-5,5,-5,-5,-5,5,5,-5,5,5,-5,5,5,5,-5,-5,-5,-5,-5,5,-5,-5,-5,5,5,5,-5,-5,5,5,-5,5,5,5,-5,-5,-5,-5,-5,-5,-5,-5,5,5,5,-5,5,-5,5,-5,5,-5,5,5,5,-5,-5,-5,5,5,-5,5,5,-5,5,-5,5,-5,-5,5,5,5,-5,-5,5,-5,5,-5,-5,-5,5,5,5,-5,5,-5,5,5,5,5,5,5,5,5,5,-5,5,-5,5,-5,5,-5,-5,5,-5,-5,-5,-5,-5,-5,-5,-5,5,5,-5,5,-5,5,5,5,-5,-5,5,-5,-5,-5,-5,5,5,-5,-5,5,5,-5,-5,5,-5,-5,5,5,-5,5,5,5,5,-5,5,5,-5,-5,5,-5,5,5,5,-5,5,5,-5,-5,5,5,-5,-5,-5,-5,5,-5,5,-5,-5,-5,5,5,5,5,-5,-5,5,5,5,-5,-5,5,-5,5,5,-5,-5,-5,-5,-5,5,-5,5,-5,5,-5,5,-5,5,5,5,5,5,5,5,5,5,5,5,5,-5,5,-5,-5,-5,5,5,5,5,-5,5,-5,5,5,-5,5,-5,5,-5,-5,5,5,5,5,-5,5,-5,-5,-5,-5,-5,5,-5,-5,5,-5,-5,5,-5,-5,5,5,-5,-5,-5,-5,5,-5,5,-5,5,-5,-5,-5,-5,5,5,5,5,5,5,5,-5,5,5,5,5,5,-5,5,5,5,5,5,-5,-5,-5,-5,5,5,5,-5,-5,5,5,5,5,-5,-5,-5,-5,5,-5,5,-5,5,-5,-5,-5,-5,5,-5,5,5,-5,-5,-5,-5,-5,-5,-5,-5,5,-5,-5,-5,5,5,-5,5,-5,-5,-5,5,-5,-5,5,5,-5,5,5,-5,-5,5,5,5,5,5,5,-5,-5,-5,5,-5,5,-5,-5,-5,5,5,5,-5,-5,-5,-5,-5,-5,5,-5,5,5,5,5,5,5,5,5,5,5,-5,-5,-5,-5,5,5,-5,-5,5,-5,5,-5,-5,-5,-5,-5,-5,-5,-5,-5,5,-5,-5,-5,5,5,-5,5,5,-5,5,-5,-5,5,5,-5,-5,5,-5,5,-5,-5,5,5,-5,5,5,5,5,-5,5,5,-5,-5,-5,5,5,5,5,-5,-5,-5,-5,5,-5,5,5,5,5,-5,5,-5,5,-5,-5,5,5,5,-5,5,-5,-5,5,-5,5,5,5,-5,-5,-5,-5,-5,-5,5,5,-5,-5,5,5,-5,-5,5,-5,5,5,-5,-5,5,-5,5,5,5,5,5, } ; 
    int par_I[]={-5,5,-5,5,-5,5,5,5,5,-5,5,5,5,5,-5,-5,5,-5,5,5,5,-5,5,-5,5,5,-5,5,-5,-5,-5,-5,-5,-5,-5,-5,-5,5,-5,5,-5,5,-5,5,5,5,-5,5,5,-5,5,5,-5,5,5,-5,-5,5,5,-5,5,5,-5,-5,-5,5,-5,-5,-5,-5,5,-5,5,-5,-5,-5,5,-5,5,-5,5,5,5,-5,-5,5,5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,5,-5,5,-5,-5,5,-5,-5,-5,-5,5,-5,5,-5,-5,-5,5,-5,-5,5,-5,-5,5,-5,5,-5,-5,5,5,5,5,-5,5,5,5,5,5,-5,5,5,5,-5,-5,-5,5,-5,5,5,5,5,5,-5,-5,-5,-5,5,-5,5,-5,-5,5,-5,5,5,-5,5,5,5,5,-5,5,5,-5,5,-5,5,-5,5,5,5,-5,-5,-5,-5,5,-5,-5,-5,5,-5,-5,-5,5,-5,-5,-5,-5,5,5,-5,-5,5,-5,5,5,5,-5,-5,5,-5,5,5,5,-5,5,5,-5,-5,-5,5,5,5,-5,5,5,5,5,5,5,-5,5,-5,5,5,5,5,-5,-5,5,-5,5,-5,5,5,5,-5,-5,5,5,-5,-5,-5,5,-5,5,5,5,-5,5,-5,-5,-5,5,-5,5,-5,-5,5,-5,5,-5,5,5,5,-5,5,-5,5,5,5,5,-5,5,-5,5,5,-5,-5,-5,5,-5,5,5,-5,-5,5,-5,5,5,5,5,-5,-5,5,-5,-5,-5,5,5,-5,5,-5,5,5,-5,-5,-5,-5,-5,5,5,5,5,-5,-5,5,5,5,-5,5,5,-5,5,5,5,5,5,-5,5,5,5,5,5,5,-5,-5,-5,5,-5,-5,-5,-5,5,5,-5,-5,-5,5,5,5,5,5,-5,-5,5,-5,-5,-5,-5,5,5,-5,5,-5,5,-5,5,-5,-5,5,5,-5,-5,5,-5,-5,-5,-5,5,5,5,5,-5,5,-5,5,-5,5,5,-5,5,-5,5,-5,-5,5,-5,5,-5,-5,5,5,5,5,-5,5,-5,5,-5,5,5,-5,-5,5,5,5,5,5,-5,-5,-5,5,5,5,5,5,-5,-5,5,5,5,-5,5,5,-5,5,-5,-5,5,5,5,5,-5,-5,5,-5,5,-5,5,-5,-5,-5,-5,-5,-5,-5,5,5,5,5,5,-5,5,-5,-5,5,-5,-5,-5,5,-5,5,5,5,-5,-5,-5,-5,-5,-5,-5,-5,-5,5,-5,-5,5,5,5,-5,5,-5,5,-5,5,-5,-5,5,5,5,-5,-5,5,5,-5,5, } ; 


    // input siso_(n)
    int l_e1n[KBITS] ;
    // output siso_n
    int l_e2n[KBITS] ;
    // input siso_i
    int l_e1i[KBITS] ;
    // output siso_i
    int l_e2i[KBITS] ;
    // store 
    int s[KBITS] ; 


int main() {

    printf(" Test start\n "); 
    int nb_iter=1  ; 

    long insn_start , insn_stop, insn_tot ; 
    long cycle_start, cycle_stop, cycle_tot ; 

    cycle_start= cycles()-4;
	insn_start = insn()-4; 

    do_action( sys_N , par_N , l_e1n , l_e2n, 0 ) ;


    for (int iter = 0; iter < nb_iter; iter++){
	
        printf("iter n %d\n",iter);
        // interl from siso_i => siso_n
        for (int i = 0; i < _KBITS; i++)
            l_e1i[i] = l_e2n[f_PI[i]] ; 

        // siso i 
        do_action( sys_I , par_I , l_e1i , l_e2i,0); 

        // interl from siso_n => siso_i
        for (int i = 0; i < _KBITS; i++)
            l_e1n[ f_PI[i] ] = l_e2i[i] ;
    
        int last = ( iter ==(nb_iter-1 )) ; 
        // siso_n
        do_action( sys_N , par_N , l_e1n , l_e2n, last ) ;
    }
    
    hard_decide_seq(l_e2n , s , KBITS) ; 

    printf(" test END \n "); 

    cycle_stop= cycles()-4;
	insn_stop = insn()-4; 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 

	printf("cycles	: %d \n", cycle_tot) ; 
	printf("insn	: %d \n", insn_tot);

    for (int i = 0; i < KBITS; i++){
        if( t_sys[i]!=t_sys_err[i])
            printf (" E ") ; 
    }

    printf( "\n correction \n") ; 
    

    for (int i = 0; i < KBITS; i++){ 
        if( t_sys[i]!=s[i])
            printf("E") ;
    }

  return 0;
}
