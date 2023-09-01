#include <stdint.h>

#define N   34
#define k   20
#define Nmk 14

#define nb_VN 	N
#define nb_CN 	Nmk


#ifdef _8b

    #define qtf ("int8_t")

    int8_t codw[]	={1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
    int8_t err_[] 	={1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 

    int8_t accuVn[] ={3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 } ; 

    // deg de chaque CN
    int8_t deg_Cns[] = {8,8,10,10,8,8,10,10,4,4,6,6,6,6  }; 

    int8_t c2v [nb_CN * nb_VN ]= {0} ; 

    int8_t posVn[]= {
        1, 3, 4, 6, 13, 19, 20, 22,
        0, 2, 5, 7, 12, 18, 21, 23,
        1, 6, 9, 11, 12, 14, 16, 18, 22, 24,
        0, 7, 8, 10, 13, 15, 17, 19, 23, 25,
        1, 2, 6, 8, 16, 21, 24, 26,
        0, 3, 7, 9, 17, 20, 25, 27,
        2, 4, 8, 10, 13, 14, 16, 18, 20, 26,
        3, 5, 9, 11, 12, 15, 17, 19, 21, 27,
        1, 2, 23, 28,
        0, 3, 22, 29,
        1, 3, 10, 15, 23, 30,
        0, 2, 11, 14, 22, 31,
        1, 10, 15, 18, 22, 32,
        0, 11, 14, 19, 23, 33,
    } ; 

#endif

#ifdef _32b

    #define qtf    ("int32_t")

    int32_t codw[]	={1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
    int32_t err_[] 	={1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 

    int32_t accuVn[] ={3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 } ; 

    // deg de chaque CN
    int32_t deg_Cns[] = {8,8,10,10,8,8,10,10,4,4,6,6,6,6  }; 

    int32_t c2v [nb_CN * nb_VN ]= {0} ; 

    int32_t posVn[]= {
        1, 3, 4, 6, 13, 19, 20, 22,
        0, 2, 5, 7, 12, 18, 21, 23,
        1, 6, 9, 11, 12, 14, 16, 18, 22, 24,
        0, 7, 8, 10, 13, 15, 17, 19, 23, 25,
        1, 2, 6, 8, 16, 21, 24, 26,
        0, 3, 7, 9, 17, 20, 25, 27,
        2, 4, 8, 10, 13, 14, 16, 18, 20, 26,
        3, 5, 9, 11, 12, 15, 17, 19, 21, 27,
        1, 2, 23, 28,
        0, 3, 22, 29,
        1, 3, 10, 15, 23, 30,
        0, 2, 11, 14, 22, 31,
        1, 10, 15, 18, 22, 32,
        0, 11, 14, 19, 23, 33,
    } ; 

#endif

#ifdef _64b

    #define qtf    ("int64_t")
    int64_t codw[]	={1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 
    int64_t err_[] 	={1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0}; 

    int64_t accuVn[] ={3, 5, -4, -4, 0,-7, 1,-4,-5, 0,-4,-3, 0, 0,-4,-3, 4,-7,-1, -4, 5, 7, 2, 6, 1,-2,-7,4,1,-1, 0,-4,-9, -4 } ; 

    // deg de chaque CN
    int64_t deg_Cns[] = {8,8,10,10,8,8,10,10,4,4,6,6,6,6  }; 

    int64_t c2v [nb_CN * nb_VN ]= {0} ; 

    int64_t posVn[]= {
        1, 3, 4, 6, 13, 19, 20, 22,
        0, 2, 5, 7, 12, 18, 21, 23,
        1, 6, 9, 11, 12, 14, 16, 18, 22, 24,
        0, 7, 8, 10, 13, 15, 17, 19, 23, 25,
        1, 2, 6, 8, 16, 21, 24, 26,
        0, 3, 7, 9, 17, 20, 25, 27,
        2, 4, 8, 10, 13, 14, 16, 18, 20, 26,
        3, 5, 9, 11, 12, 15, 17, 19, 21, 27,
        1, 2, 23, 28,
        0, 3, 22, 29,
        1, 3, 10, 15, 23, 30,
        0, 2, 11, 14, 22, 31,
        1, 10, 15, 18, 22, 32,
        0, 11, 14, 19, 23, 33,
    } ; 


#endif