#include <stdarg.h>
#include <stdint.h>

long cycles();
long insn();
void perfs_init();
void perfs_end();
void display_perf(); 

static void printf_c(int c);
static void printf_s(char *p);
static void printf_d(int val);
int printf(const char *format, ...);