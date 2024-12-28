CROSS_COMPILE = aarch64-none-elf-
CC        = $(CROSS_COMPILE)gcc
LD        = $(CROSS_COMPILE)ld
OBJCOPY   = $(CROSS_COMPILE)objcopy

CFLAGS  = -Wall -O2 -nostdlib -ffreestanding -fno-builtin
CFLAGS += -mcpu=cortex-a72 -march=armv8-a
LDFLAGS = -T linker.ld --gc-sections
ASFLAGS = -c

OUT_DIR = bin

SRCS = boot.S main.c src/mmio.c src/videocore.c src/uart.c src/mailbox.c
OBJS = $(SRCS:%.c=$(OUT_DIR)/%.o)
OBJS := $(OBJS:%.S=$(OUT_DIR)/%.o)

all: $(OUT_DIR)/kernel8.img

$(OUT_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(ASFLAGS) $< -o $@

$(OUT_DIR)/kernel8.elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(OUT_DIR)/kernel8.img: $(OUT_DIR)/kernel8.elf
	$(OBJCOPY) $< -O binary $@

clean:
	rm -rf $(OUT_DIR)
	rm -f *.o *.elf *.img

.PHONY: all clean