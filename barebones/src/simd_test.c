#include "./stdlib.h"

#define int8_tx4 int32_t
#define int8_tx8 int64_t 


void displayVector( int8_tx4 vector ){
	printf("V4[31:24] %d ",   vector>>24) ;
	printf("V3[23:16] %d ",  (vector<<8)>>24) ;
	printf("V2[15:8]  %d ",  (vector<<16)>>24) ;
	printf("V1[7:0]   %d \n",(vector<<24)>>24) ;
}

void displayVectorHex_int8x4( int8_tx4 vector ){
	printf("V4[31:24] %x ",   vector>>24) ;
	printf("V3[23:16] %x ",  (vector<<8)>>24) ;
	printf("V2[15:8]  %x ",  (vector<<16)>>24) ;
	printf("V1[7:0]   %x \n",(vector<<24)>>24) ;
}



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



int main() {

  int8_tx8 vec64, 
  vec64_test=0 ,
  vec64_test2 = 0 ;  
  vec64_test = 0x1122334455667788 ;  

  printf("addsat \n"); 
  displayVector_int8x8(vec64_test) ; 
  callAddSat(vec64,vec64_test, vec64_test);
  displayVector_int8x8(vec64) ;


  vec64_test2 = 0x8899aa44ff55ee66 ;
  printf("subsat \n "); 
  displayVector_int8x8(vec64_test) ; 
  callSubSat(vec64,vec64_test2, vec64_test);
  displayVector_int8x8(vec64) ;

  displayVector_int8x8(vec64_test) ; 
  callFinstr(vec64,vec64_test, vec64_test);
  displayVector_int8x8(vec64) ;

  displayVector_int8x8(vec64_test) ; 
  callRinstr(vec64,vec64_test, vec64_test);
  displayVector_int8x8(vec64) ;
  

/*

    int8_t a, b, c, d ; 
    a = 10 ;
    b = 5 ; 
    c = 15 ; 
    d = 20 ; 



  // 0x00000000140f050a

    int8_tx4 test_vec = a | b<<8 | c << 16 | d <<24 ; 
    int8_tx4 sat_vec =  125 | 124 << 8 | 123 << 16 | 122 << 24 ;
    int8_tx4 res_vec ;

    // displayVector(test_vec) ; 
     
    // callAddSat(res_vec,test_vec,test_vec) ; 
    // callAddSat(res_vec,sat_vec,sat_vec) ; 

    // test de addsat 
    printf("addsat\n"); 
    callAddSat(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    printf("subsat\n"); 
    callSubSat(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    printf("F\n"); 
    callFinstr(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    printf("R\n"); 
    callRinstr(res_vec,test_vec,test_vec) ; 
    displayVector(res_vec) ; 

    // saturations 
    printf("test saturation\n\n"); 
    displayVector(sat_vec) ;
    
    printf("addsat\n"); 
    callAddSat(res_vec,sat_vec,sat_vec) ; 
    displayVector(res_vec) ; 

    printf("subsat\n"); 
    callSubSat(res_vec,sat_vec,sat_vec) ; 
    displayVector(res_vec) ; 



*/

  return 0;
}