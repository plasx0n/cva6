/*
   SERV dependent à cause des instrus .. 
   voir pour refractor les vars temporaires 
   Ajouter eventuellement une autre instru dans le kernel .. 

*/


#include <stdint.h>
#include "ldpc_r3_int8x4.h"

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

int8_tx4 r1,r2,r3,r4,Res,Dummy ; 
int8_tx4 min1,min2,a ; 




r2 		= 0xaabbccdd; 
r3 		= 0x7E7E7E7E;
r4 		= 0x81818181; 

// a= 1 ;//x01
// b= -10 ; //xF6
// c= -127 ; //x81
// d= 126 ; //x7E


/*---*/
// r1 = (a) | (b<<8) | (c<<16) | (d <<24) ; 
//   int32_t vect = v1 | (v2<<8) | (v3<<16) | (v4<<24) ;

// r1 = 0x7E81F601 ; 
// Dummy = callAbs(r1,0); // seems ok 
/*---*/


/*---*/
//126 / 127 / 10 / 1 
// int8_tx4 min2 = 0x7E7F0A01 ;

// 1 / 2 / 3 / 4 
// int8_tx4 min1 	= 0x01020304 ; 

// 0 / 1/ 5 / 10  
// int8_tx4 a 		= 0x0001050A ; 

// 1/2/5/10
// puis 
// 1/2/5/1
// Dummy = minmax(min1,a,min2); 
//ok 
/*---*/

/*---*/
//126 / 127 / 10 / 1 
// min2 = 0x7E7F0A01 ;

// 1 / 2 / 3 / 4 
// min1 	= 0x01020304 ; 
// Dummy = callMin(min2,min1); 
// idk 
/*---*/

/*---*/
Dummy =ld_rsign_nmess(r4,r1,r2); //seems ok 

/*---*/

// Dummy =ld_min_sorting(r4,r1,r2); 

}
