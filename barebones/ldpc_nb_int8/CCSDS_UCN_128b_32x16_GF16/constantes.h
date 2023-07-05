#ifndef CONSTANTES
#define CONSTANTES

#include <math.h>

#define _GF_        		 16
#define _LOG2GF_    		  4

#define _KSYMBOL_   		 16
#define _NSYMBOL_   		 32
#define _MESSAGE_   		 80

#define _DEG_CN_               5
#define _DEG_COMPUTATIONS_    16

#define _KBIT_      		(_KSYMBOL_*_LOG2GF_)
#define _NBIT_      		(_NSYMBOL_*_LOG2GF_)

#define _NmKSYMBOL_ 	 	(_NSYMBOL_-_KSYMBOL_)
#define _NmKBIT_     		(_NBIT_-_KBIT_)

#endif
