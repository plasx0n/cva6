
#include "stdint.h"
#include "./stdlib.h"
#define int8x4 int32_t

/*
ld3_rsign_nmess
ld3_copyxorvecto
ld3_maxsub
ld3_min_sorting
ld3_minmax
ld3_readvn
ld3_sign3
*/

/*
pl3_g
pl3_vidx_min_comp
pl3_vsc_update
pl3_find_min_pos
*/

static inline int32_t custom_r4_template(int32_t rs1, int32_t rs2,int32_t rs3){
    int32_t rd ; 
    asm volatile("ld3_minmax %0,%1,%2,%3" \
                            :"=r"(rd) \
                            :"r"(rs1),"r"(rs2),"r"(rs3));           
    return rd;
}


static inline int32_t pl3_g(int32_t rs1, int32_t rs2,int32_t rs3){
    int32_t rd ; 
    asm volatile("pl3_g %0,%1,%2,%3" \
                            :"=r"(rd) \
                            :"r"(rs1),"r"(rs2),"r"(rs3));           
    return rd;
}

static inline int32_t pl3_vidx_min_comp(int32_t rs1, int32_t rs2,int32_t rs3){
    int32_t rd ; 
    asm volatile("pl3_vidx_min_comp %0,%1,%2,%3" \
                            :"=r"(rd) \
                            :"r"(rs1),"r"(rs2),"r"(rs3));           
    return rd;
}

static inline int32_t pl3_vsc_update(int32_t rs1, int32_t rs2,int32_t rs3){
    int32_t rd ; 
    asm volatile("pl3_vsc_update %0,%1,%2,%3" \
                            :"=r"(rd) \
                            :"r"(rs1),"r"(rs2),"r"(rs3));           
    return rd;
}

static inline int32_t pl3_find_min_pos(int32_t rs1, int32_t rs2,int32_t rs3){
    int32_t rd ; 
    asm volatile("pl3_find_min_pos %0,%1,%2,%3" \
                            :"=r"(rd) \
                            :"r"(rs1),"r"(rs2),"r"(rs3));           
    return rd;
}




int main(int argc, char const *argv[])
{
    
    int8x4 a,b,c,d ; 
    a = pl3_g(b,c,d);

    return 0;
}