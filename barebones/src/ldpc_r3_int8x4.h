
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

#define callSign(rd,rs1,rs2) asm volatile("ld.sign %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

#define callEval(rd,rs1,rs2) asm volatile("ld.eval %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 


#define callAddSat(rd,rs1,rs2) asm volatile("ld.addsat %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 


static inline int sign3( int rs1 , int rs2, int rs3  ){
    int rd ; 
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

static inline int32_t ld_min_sorting( int32_t rs1 , int32_t rs2, int32_t rs3  ){
    int32_t rd ; 
    asm volatile(" ld3_min_sorting %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}