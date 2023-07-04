#include <stdarg.h>
#include <stdint.h>

void *memset(void *s, int c, int n) ; 
long cycles();
long insn();

void displayVector( int32_t v1, int32_t v2, int32_t v3);
void displayVectorV1( int32_t v1); 


static void printf_c(int c);
static void printf_s(char *p);
static void printf_d(int val);
int printf(const char *format, ...);
