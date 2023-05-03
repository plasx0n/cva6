GCC=/opt/riscv/bin/riscv64-unknown-elf-gcc
AS=/opt/riscv/bin/riscv64-unknown-elf-as
LD=/opt/riscv/bin/riscv64-unknown-elf-ld
DMP=/opt/riscv/bin/riscv64-unknown-elf-objdump


BINARIES = ldpc_int8x8_inter ldpc_int8x4_inter ldpc_int8_cst simd_unit_test
SRC=./src/stdlib.c

SRC_ASM=./start.S

LINKER_SCRIPT=./rv64.ld

GCC_FLAGS	=-Wall -Wextra -march=rv64imafc -mcmodel=medany -mabi=lp64f -ffreestanding -static -O3
AS_FLAGS	=-march=rv64imafc -mabi=lp64f
LD_FLAGS	=-nostdlib

SRC_DIR = ./src/

ldpc_int8x8_inter : $(SRC_DIR)ldpc_int8x8_inter.o
ldpc_int8x4_inter : $(SRC_DIR)ldpc_int8x4_inter.o
ldpc_int8_cst : 	$(SRC_DIR)ldpc_int8_cst.o
simd_unit_test :	$(SRC_DIR)simd_unit_test.o

OBJ=$(SRC:.c=.o)
ASM=$(SRC_ASM:.S=.o)

all: $(BINARIES)

%: $(OBJ) $(ASM)
	$(GCC) $(GCC_FLAGS) $(LD_FLAGS) -T $(LINKER_SCRIPT) $(ASM) $(OBJ) ./src/$@.o -o ./bin/$@

%.o: %.c
	$(GCC) -o $@ -c $< $(GCC_FLAGS)

%.o: %.S
	$(GCC) -o $@ -c $< $(AS_FLAGS)


dump: ldpc_int8x4_inter
	$(DMP) -d ./bin/$^ > dmp.txt

.PHONY: all clean mrproper dump

clean:
	find . -name *.o -delete
	find . -name *.s -delete
	rm -rf bin/*
