
# System copmiler 
GCC=/opt/riscv/bin/riscv64-unknown-elf-gcc
AS=/opt/riscv/bin/riscv64-unknown-elf-as
LD=/opt/riscv/bin/riscv64-unknown-elf-ld
DMP=/opt/riscv/bin/riscv64-unknown-elf-objdump

# Programs 
BINARIES = polar_fsc_int8

SRC=./src/stdlib.c
SRC_ASM=./start.S
LINKER_SCRIPT=./rv64.ld

# GCC optimizations and flags 
GCC_FLAGS=-Wall -Wextra -march=rv64imafc -mcmodel=medany -mabi=lp64f -ffreestanding -static -O3
AS_FLAGS=-march=rv64imafc -mabi=lp64f
LD_FLAGS=-nostdlib


polar_fsc_int8 			: ./src/polar_fsc_int8.o

OBJ=$(SRC:.c=.o)
ASM=$(SRC_ASM:.S=.o)

all: $(BINARIES)

%: $(OBJ) $(ASM)
	$(GCC) $(GCC_FLAGS) $(LD_FLAGS) -T $(LINKER_SCRIPT) $(ASM) $(OBJ) ./src/$@.o -o ./bin/$@

%.o: %.c
	$(GCC) -o $@ -c $< $(GCC_FLAGS)

%.o: %.S
	$(GCC) -o $@ -c $< $(AS_FLAGS)


dump: $(BINARIES)
	$(DMP) -d ./bin/$^ > $^.txt

clean:
	find . -name *.o -delete
	find . -name *.s -delete
	rm -rf bin/*

.PHONY: all clean mrproper dump