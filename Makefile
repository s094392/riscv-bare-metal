CC = riscv64-linux-gnu-gcc 
LD = riscv64-linux-gnu-ld
 
all: clean startup.o main.o
	$(LD) -T link.ld -o kernel.elf startup.o main.o
	
main.o: main.c
	$(CC) -mcmodel=medany -c -g main.c -o main.o

startup.o: startup.S
	$(CC) -c startup.S -o startup.o

clean:
	rm -f *.o kernel.elf

run: all
	qemu-system-riscv64 -M sifive_u -kernel kernel.elf -serial stdio
