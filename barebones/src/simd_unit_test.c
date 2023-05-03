/*
   SERV dependent à cause des instrus .. 
   voir pour refractor les vars temporaires 
   Ajouter eventuellement une autre instru dans le kernel .. 

*/


#include <stdint.h>

// if rS1 > 0 ? 1 : 0 
#define callSign(rd,rs1,rs2) asm volatile("ld.sign %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

#define callAbs(rd,rs1,rs2) asm volatile("ld.abs %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

#define callMax(rd,rs1,rs2) asm volatile("ld.max %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

#define callMin(rd,rs1,rs2) asm volatile("ld.min %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

//  rS1 =>1  ? rs2 : -rS2 
#define callNmess(rd,rs1,rs2) asm volatile("ld.nmess %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2));

#define callSubSat(rd,rs1,rs2) asm volatile("ld.subsat %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

#define callAddSat(rd,rs1,rs2) asm volatile("ld.addsat %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 								



#define callRsign(rd,rs1,rs2) asm volatile("ld.rsign %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 

#define callEval(rd,rs1,rs2) asm volatile("ld.eval %0,%1,%2" \
	                            : "=r" (rd) \
	                            : "r" (rs1), "r" (rs2)); 






#define int8_tx4 int32_t
#define int8_tx8 int64_t 

/**/
void displayVector( int8_tx4 vector ){
	printf("V4[31:24] %d ",   vector>>24) ;
	printf("V3[23:16] %d ",  (vector<<8)>>24) ;
	printf("V2[15:8]  %d ",  (vector<<16)>>24) ;
	printf("V1[7:0]   %d \n",(vector<<24)>>24) ;
}

/**/
void displayVectorHex_int8x4( int8_tx4 vector ){
	printf("V4[31:24] %x ",   vector>>24) ;
	printf("V3[23:16] %x ",  (vector<<8)>>24) ;
	printf("V2[15:8]  %x ",  (vector<<16)>>24) ;
	printf("V1[7:0]   %x \n",(vector<<24)>>24) ;
}

/**/
void displayVector_int8x8( int8_tx8 vector ){
	printf("=========================\n"); 
  printf("V8[64:56]:%d ",    vector     >>56) ;
	printf("V7[55:48]:%d ",   (vector<<8 )>>56) ;
	printf("V6[47:40]:%d ",   (vector<<16)>>56) ;
	printf("V5[39:32]:%d \n", (vector<<24)>>56) ;
	printf("V4[31:24]:%d ",   (vector<<32)>>56) ;
	printf("V3[23:16]:%d ",   (vector<<40)>>56) ;
	printf("V2[15:8] :%d ",   (vector<<48)>>56) ;
	printf("V1[7:0]  :%d \n", (vector<<56)>>56) ;
	printf("=========================\n"); 
}

int main( ) 
{

int8_tx8 r1,r2,r3,r4,Res,Dummy ; 
int8_tx8 min1,min2,a ; 

r2 		= 0xaabbccdd; 
r3 		= 0x7E7E7E7E;
r4 		= 0x81818181; 

// a= 1 ;//x01
// b= -10 ; //xF6
// c= -127 ; //x81
// d= 126 ; //x7E


/*---*/
// 		r1 = (a) | (b<<8) | (c<<16) | (d <<24) ; 
//   	int32_t vect = v1 | (v2<<8) | (v3<<16) | (v4<<24) ;

    // r1 		= 0x7E81F6017E81F601 ; 
    // callAbs(Dummy,r1,0); 
    // printf("dummy %x \n", Dummy); 
    // displayVector_int8x8(Dummy) ; 

// ok
/*---*/


/*---*/
// a= 1 ;//x01
// b= -10 ; //xF6
// c= -127 ; //x81
// d= 126 ; //x7E


    // r1 		= 0x7E81F6017E81F601 ; 

    // 1/2/5/10
    // puis 
    // 1/2/5/1
    // callSign(Dummy,r1,0) ; 
    // printf("sign %x \n", Dummy); 
    // displayVector_int8x8(Dummy) ; 

    //ok 
/*---*/

/*---*/
//126 / 127 / 10 / 1 
// 1 / 2 / 3 / 4 

    // min2 	= 0x7E7F0A017E7F0A01 ;
    // min1 	= 0x0102030401020304 ; 
    // callMin(Dummy,min2,min1);
    // printf("dummy %x \n", Dummy); 
    // displayVector_int8x8(Dummy) ; 

// ok

/*---*/

/*---*/
//126 / 127 / 10 / 1 
// 1 / 2 / 3 / 4 

    // min2 	= 0x7E7F0A017E7F0A01 ;
    // min1 	= 0x0102030401020304 ; 
    // callMax(Dummy,min2,min1);
    // printf("dummy %x \n", Dummy); 
    // displayVector_int8x8(Dummy) ; 

// ok

/*---*/

/*---*/
    // 0 / 0/ 5 / 11  
    // r1 = 0x0000050B ; 

    // 126 / 127 / 10 / 1 
    // r2 = 0x7E7F0A01 ;

    // callNmess(Dummy,r1,r2); //to test
    // printf("dummy : %x",Dummy); 
    // displayVector(Dummy) ;  

    // ok

/*---*/

    //126 / 127 / 10 / 1 
    // 1 / 2 / 3 / 4 

    // min1 	= 0x7E7F0A017E7F0A01 ;
    // min2 	= min1 ; 

    // callAddSat(Dummy,min1,min2); //to test
    // printf("dummy : %x",Dummy); 
    // displayVector_int8x8(Dummy) ; 

    // ok add/sub sat 

/*---*/
// a= 1 ;//x01
// b= -10 ; //xF6
// c= -127 ; //x81
// d= 126 ; //x7E

//126 / 127 / 10 / 1  //126 / 127 / 10 / 1 

    // r1 		= 0x7E81F6017E81F601 ; 
    // min1 	= 0x7E7F0A017E7F0A01 ;
    // min2 	= min1 ; 

    // // a ^ (( b >=0 )? 1 : 0 ))

    // callRsign(Dummy,min1,r1); //to test
    // printf("dummy : %x",Dummy); 
    // displayVector_int8x8(Dummy) ; 

    // to test 

/*---*/
// a= 1 ;//x01
// b= -10 ; //xF6
// c= -127 ; //x81
// d= 126 ; //x7E

//126 / 127 / 10 / 1  //126 / 127 / 10 / 1 

    r1 		= 0x7E81F6017E81F601 ; 
    min1 	= 0x7E7F0A017E7F0A01 ;

    // a ^ (( b >=0 )? 1 : 0 ))

    callEval(Dummy,min1,r1); //to test
    printf("dummy : %x",Dummy); 
    displayVector_int8x8(Dummy) ; 

    // seems ok 

/*---*/



return 1 ; 
}
