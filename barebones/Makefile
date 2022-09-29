GCC= /opt/riscv/bin/riscv64-unknown-elf-gcc
AS=riscv64-unknown-elf-as
LD=riscv64-unknown-elf-ld
DMP=/opt/riscv/bin/riscv64-unknown-elf-objdump

EXEC=hello.elf
SRC=./src/helloworld.c ./src/uart.c
#SRC=./src/helloworld.c
SRC_ASM=./start.S

LINKER_SCRIPT=./rv64.ld

GCC_FLAGS=-Wall -Wextra -march=rv64imafc -mcmodel=medany -mabi=lp64f -ffreestanding
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