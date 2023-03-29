/*
   SERV dependent à cause des instrus .. 
   voir pour refractor les vars temporaires 
   Ajouter eventuellement une autre instru dans le kernel .. 

*/


#include <stdint.h>
#include "ldpc_r3.h"

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

printf("TEST ADDSAT\n"); 

int8_tx4 r1,r2,Res ; 

r1 = 0xaabbccdd; 
r2 = 0xaabbccdd; 

displayVector(r1);
displayVector(r2);
callAddSat(Res,r1,r2) ; 
displayVector(Res) ; 

}
