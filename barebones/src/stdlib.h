#include <stdarg.h>
#include <stdint.h>

static void printf_c(int c);
static void printf_s(char *p);
static void printf_d(int val);
int printf(const char *format, ...);

long cycles();
long insn();
void perf_init();
void perfs_end(); 
