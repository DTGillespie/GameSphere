CROSS_COMPILE = aarch64-none-elf-
CC        = $(CROSS_COMPILE)gcc
LD        = $(CROSS_COMPILE)ld
OBJCOPY   = $(CROSS_COMPILE)objcopy

# Common compiler flags
CFLAGS  = -Wall -g -O0 -nostdlib -ffreestanding -fno-builtin
CFLAGS += -march=armv8-a

LDFLAGS = -T linker.ld --gc-sections
ASFLAGS = -c

OUT_DIR = bin

SRCS = boot.S main.c src/mmio.c src/videocore.c src/uart.c src/mailbox.c src/gpio.c src/util.c
OBJS = $(SRCS:%.c=$(OUT_DIR)/%.o)
OBJS := $(OBJS:%.S=$(OUT_DIR)/%.o)

# Default target (override with "make raspi3" or "make raspi4")
TARGET_CPU ?= cortex-a53  # Default to Pi 3B
QEMU_MACHINE ?= raspi3b   # Default QEMU machine
TARGET_DEF ?=

# Define targets for Pi models
raspi3:
	$(MAKE) all TARGET_CPU=cortex-a53 QEMU_MACHINE=raspi3b TARGET_DEF=-DRASPI3

raspi4:
	$(MAKE) all TARGET_CPU=cortex-a72 QEMU_MACHINE=raspi3b TARGET_DEF=-DRASPI4

all: $(OUT_DIR)/kernel8.img

$(OUT_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TARGET_DEF) -mcpu=$(TARGET_CPU) -c $< -o $@

$(OUT_DIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TARGET_DEF) -mcpu=$(TARGET_CPU) $(ASFLAGS) $< -o $@

$(OUT_DIR)/kernel8.elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(OUT_DIR)/kernel8.img: $(OUT_DIR)/kernel8.elf
	$(OBJCOPY) $< -O binary $@

run:
	qemu-system-aarch64 -M $(QEMU_MACHINE) -kernel $(OUT_DIR)/kernel8.img -serial stdio -monitor none -nographic

clean:
	rm -rf $(OUT_DIR)
	rm -f *.o *.elf *.img

.PHONY: all clean raspi3 raspi4 run
