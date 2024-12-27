CROSS_COMPILE = aarch64-none-elf-
CC			= $(CROSS_COMPILE)gcc
LD			= $(CROSS_COMPILE)ld
OBJCOPY	= $(CROSS_COMPILE)objcopy

CFLAGS	= -Wall -O2 -nostdlib -ffreestanding -fno-builtin
# Targeting ARMv8 AArch64
CFLAGS += -mcpu=cortex-a72 -march=armv8-a

LDFLAGS = -T linker.ld --gc-sections
ASFLAGS = -c

all: kernel8.img

boot.o: boot.S
		$(CC) $(CFLAGS) $(ASFLAGS) boot.S -o boot.o

main.o: main.c
		$(CC) $(CFLAGS) -c main.c -o main.o

kernel8.elf: boot.o main.o linker.ld
		$(LD) $(LDFLAGS) boot.o main.o -o kernel8.elf

kernel8.img: kernel8.elf
		$(OBJCOPY) kernel8.elf -O binary kernel8.img

clean:
	rm -f *.0 *.elf *.img