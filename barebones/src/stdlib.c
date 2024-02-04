#include <stdarg.h>

static void printf_c(int c)
{
	*((volatile int*)0x10000000) = c;
}

static void printf_s(char *p)
{
	while (*p)
		*((volatile int*)0x10000000) = *(p++);
}

static void printf_d(int val)
{
	char buffer[32];
	char *p = buffer;
	if (val < 0) {
		printf_c('-');
		val = -val;
	}
	while (val || p == buffer) {
		*(p++) = '0' + val % 10;
		val = val / 10;
	}
	while (p != buffer)
		printf_c(*(--p));
}

int printf(const char *format, ...)
{
	int i;
	va_list ap;

	va_start(ap, format);

	for (i = 0; format[i]; i++)
		if (format[i] == '%') {
			while (format[++i]) {
				if (format[i] == 'c') {
					printf_c(va_arg(ap,int));
					break;
				}
				if (format[i] == 's') {
					printf_s(va_arg(ap,char*));
					break;
				}
				if (format[i] == 'd') {
					printf_d(va_arg(ap,int));
					break;
				}
			}
		} else
			printf_c(format[i]);

	va_end(ap);
}

long insn_start,insn_stop,insn_tot ; 
long cycle_start,cycle_stop , cycle_tot ; 

long cycles(){
	long cycles;
	asm volatile ("rdcycle %0" : "=r"(cycles));
	// printf("[time() -> %d]", cycles);
	return cycles;
}

long insn(){
	long insns;
	asm volatile ("rdinstret %0" : "=r"(insns));
	// printf("[insn() -> %d]", insns);
	return insns;
}

void perfs_init(){
    insn_start  = insn() ; 
    cycle_start = cycles()  ; 
}

void perfs_end(){
    cycle_stop= cycles();
	insn_stop = insn(); 

	cycle_tot = cycle_stop - cycle_start ; 
	insn_tot = insn_stop - insn_start ; 
}