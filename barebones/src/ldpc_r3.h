
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

static inline int8_t minmax( int8_t rs1 , int8_t rs2, int8_t rs3  ){
    int8_t rd ; 
    asm volatile(" ld3_minmax %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

static inline int8_t ld_rsign_nmess( int8_t rs1 , int8_t rs2, int8_t rs3  ){
    int8_t rd ; 
    asm volatile(" ld3_rsign_nmess %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}

static inline int8_t ld_min_sorting( int8_t rs1 , int8_t rs2, int8_t rs3  ){
    int8_t rd ; 
    asm volatile(" ld3_min_sorting %0,%1,%2,%3" \
                            : "=r" (rd) \
                            : "r" (rs1), "r" (rs2), "r"(rs3)); 
    return rd;
}