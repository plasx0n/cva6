GCC=/opt/riscv/bin/riscv64-unknown-elf-gcc
AS=/opt/riscv/bin/riscv64-unknown-elf-as
LD=/opt/riscv/bin/riscv64-unknown-elf-ld
DMP=/opt/riscv/bin/riscv64-unknown-elf-objdump


BINARIES = ldpc_int8_cst ldpc_int8 ldpc_int32 ldpc_int32_cst ldpc_int64 ldpc_int64_cst
SRC=./src/stdlib.c

SRC_ASM=./start.S

LINKER_SCRIPT=./rv64.ld

GCC_FLAGS	=-Wall -Wextra -march=rv64imaf -mcmodel=medany -mabi=lp64f -ffreestanding -static -O3
AS_FLAGS	=-march=rv64imafc -mabi=lp64f
LD_FLAGS	=-nostdlib

ldpc_int8 : ./src/ldpc_int8.o
ldpc_int8_cst : ./src/ldpc_int8_cst.o
ldpc_int8 : ./src/ldpc_int32.o
ldpc_int8_cst : ./src/ldpc_int32_cst.o
ldpc_int64 : ./src/ldpc_int64.o
ldpc_int64_cst : ./src/ldpc_int64_cst.o


OBJ=$(SRC:.c=.o)
ASM=$(SRC_ASM:.S=.o)

all: $(BINARIES)

%: $(OBJ) $(ASM)
	$(GCC) $(GCC_FLAGS) $(LD_FLAGS) -T $(LINKER_SCRIPT) $(ASM) $(OBJ) ./src/$@.o -o ./bin/$@

%.o: %.c
	$(GCC) -o $@ -c $< $(GCC_FLAGS)

%.o: %.S
	$(GCC) -o $@ -c $< $(AS_FLAGS)

dump :
	$(DMP) -D --disassemble=process bin/ldpc_int8_cst > dmp.txt
	awk '/process/,/ret/' dmp.txt > process.txt

.PHONY: all clean mrproper dump

clean:
	find . -name *.o -delete
	find . -name *.s -delete
	rm -rf bin/*
