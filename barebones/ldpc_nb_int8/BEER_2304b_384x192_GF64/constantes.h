#ifndef CONSTANTES
#define CONSTANTES

#include <math.h>

#define _GF_        		 64
#define _LOG2GF_    		  6

#define _KSYMBOL_   		192
#define _NSYMBOL_   		384
#define _MESSAGE_   		768

#define _DEG_CN_               4
#define _DEG_COMPUTATIONS_   192

#define _KBIT_      		(_KSYMBOL_*_LOG2GF_)
#define _NBIT_      		(_NSYMBOL_*_LOG2GF_)

#define _NmKSYMBOL_ 	 	(_NSYMBOL_-_KSYMBOL_)
#define _NmKBIT_     		(_NBIT_-_KBIT_)

#endif
