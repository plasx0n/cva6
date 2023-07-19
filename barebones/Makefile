RISCV_TC=/opt/riscv64i

GCC=	$(RISCV_TC)/bin/riscv64-unknown-elf-gcc
AS=		$(RISCV_TC)/bin/riscv64-unknown-elf-as
LD=		$(RISCV_TC)/bin/riscv64-unknown-elf-ld
DMP=	$(RISCV_TC)/bin/riscv64-unknown-elf-objdump

EXEC=turbo
SRC= src/stdlib.c src/turbo.c
#SRC=./src/helloworld.c
SRC_ASM=./start.S

LINKER_SCRIPT=./rv64.ld

GCC_FLAGS=-Wall -Wextra -march=rv64i -mcmodel=medany -ffreestanding
# GCC_FLAGS=-Wall -Wextra -march=rv64imafc -mcmodel=medany -mabi=lp64f -ffreestanding
AS_FLAGS=-march=rv64imafc -mabi=lp64f
LD_FLAGS=-nostdlib

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