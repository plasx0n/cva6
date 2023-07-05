
# SYSTEM/TOOLCHAIN TOOLS 
RISCV ?= /opt/riscv/bin/
GCC =	$(RISCV)riscv64-unknown-elf-gcc
AS = 	$(RISCV)riscv64-unknown-elf-as
LD =	$(RISCV)riscv64-unknown-elf-ld
DMP=  	$(RISCV)riscv64-unknown-elf-objdump

# FEC 
ECC_DIR = ldpc_nb_int8/
EXEC = ldpc_nb_int8.c
SRC = $(ECC_DIR)$(EXEC)

# CORE DEPENDENT 
SRC_ASM =./start.S
LINKER_SCRIPT=./rv64.ld

# PROGRAMS FLAG
GCC_FLAGS	=-Wall -Wextra -march=rv64imafdc -mcmodel=medany -mabi=lp64f -ffreestanding
AS_FLAGS	=-march=rv64imafc -mabi=lp64f
LD_FLAGS	=-nostdlib

OBJ=$(SRC:.c=.o)
ASM=$(SRC_ASM:.S=.o)

$(EXEC): $(OBJ) $(ASM)
	$(GCC) $(GCC_FLAGS) $(LD_FLAGS) -T $(LINKER_SCRIPT) $(ASM) $(OBJ) -o ./bin/$@

%.o: %.c
	$(GCC) -o $@ -c $< $(GCC_FLAGS)

%.o: %.S
	$(GCC) -o $@ -c $< $(AS_FLAGS)


dump: $(EXEC)
	$(DMP) -d ./bin/$^ > dmp.txt

.PHONY: all clean mrproper dump

clean:
	find . -name *.o -delete
	find . -name *.s -delete
	
mrproper: clean
	rm ./bin/$(EXEC)