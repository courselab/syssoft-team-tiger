all: main.bin

main.bin: main.o libc.o
	ld -m elf_i386 -Ttext 0x7c00 -o main.elf main.o libc.o
	objcopy -O binary main.elf main.bin

main.o: main.c
	gcc -m32 -ffreestanding -c main.c -o main.o

libc.o: libc.S
	gcc -m32 -ffreestanding -c libc.S -o libc.o

clean:
	rm -f *.o *.elf *.bin
