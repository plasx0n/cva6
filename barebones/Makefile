GCC=/opt/riscv/bin/riscv64-unknown-elf-gcc
AS=/opt/riscv/bin/riscv64-unknown-elf-as
LD=/opt/riscv/bin/riscv64-unknown-elf-ld
DMP=/opt/riscv/bin/riscv64-unknown-elf-objdump


TERM=screen

BINARIES = ldpc_int64_r3_cst ldpc_int64 ldpc_int64_cst ldpc_int8_r3_cst ldpc_int8 ldpc_int8_cst ldpc_int64 ldpc_int32 ldpc_int32_cst ldpc_int32_r3_cst 
SRC=./common/stdlib.c

SRC_ASM=./common/start.S

LINKER_SCRIPT=./common/rv64.ld

GCC_FLAGS	=-Wall -Wextra -march=rv64imafc -mcmodel=medany -mabi=lp64f -ffreestanding -static -O3
AS_FLAGS	=-march=rv64imafc -mabi=lp64f
LD_FLAGS	=-nostdlib

ldpc_int8 			: ./src/ldpc_int8.o
ldpc_int8_cst 		: ./src/ldpc_int8_cst.o
ldpc_int8_r3_cst 	: ./src/ldpc_int8_r3_cst.o

ldpc_int32			: ./src/ldpc_int32.o
ldpc_int32_cst		: ./src/ldpc_int32_cst.o
ldpc_int32_r3_cst	: ./src/ldpc_int32_r3_cst.o

ldpc_int64 			: ./src/ldpc_int64.o
ldpc_int64_cst 		: ./src/ldpc_int64_cst.o
ldpc_int64_r3_cst 	: ./src/ldpc_int64_r3_cst.o


OBJ=$(SRC:.c=.o)
ASM=$(SRC_ASM:.S=.o)

all: $(BINARIES)

test_all : 
	make test_code ECC=ldpc_int8
	make test_code ECC=ldpc_int8_cst
	make test_code ECC=ldpc_int8_r3_cst
	make test_code ECC=ldpc_int32
	make test_code ECC=ldpc_int32_cst
	make test_code ECC=ldpc_int32_r3_cst
	make test_code ECC=ldpc_int64
	make test_code ECC=ldpc_int64_cst
	make test_code ECC=ldpc_int64_r3_cst

test_code :
	../work-ver/Variane_testharness bin/$(ECC)> res/$(ECC)

%: $(OBJ) $(ASM)
	$(GCC) $(GCC_FLAGS) $(LD_FLAGS) -T $(LINKER_SCRIPT) $(ASM) $(OBJ) ./src/$@.o -o ./bin/$@

%.o: %.c
	$(GCC) -o $@ -c $< $(GCC_FLAGS) -I includes/

%.o: %.S
	$(GCC) -o $@ -c $< $(AS_FLAGS)


dump: $(EXEC)
	$(DMP) -d ./bin/$^ > dmp.txt

.PHONY: all clean mrproper dump

clean:
	find . -name *.o -delete
	find . -name *.s -delete
	rm -rf bin/*
	rm -rf res/*