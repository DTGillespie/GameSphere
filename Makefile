CROSS_COMPILE = aarch64-none-elf-
CC        = $(CROSS_COMPILE)gcc
LD        = $(CROSS_COMPILE)ld
OBJCOPY   = $(CROSS_COMPILE)objcopy

CFLAGS  = -Wall -O2 -nostdlib -ffreestanding -fno-builtin
# Targeting ARMv8 AArch64
CFLAGS += -mcpu=cortex-a72 -march=armv8-a
#CFLAGS += -std=c11

LDFLAGS = -T linker.ld --gc-sections
ASFLAGS = -c

# Where we want to store all build artifacts
OUT_DIR = bin

# Default target: build the final IMG in our bin folder
all: $(OUT_DIR)/kernel8.img

# Build rules
# -------------------------------------------------

# 1) boot.o -> goes to bin/boot.o
$(OUT_DIR)/boot.o: boot.S
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(ASFLAGS) $< -o $@

# 2) main.o -> goes to bin/main.o
$(OUT_DIR)/main.o: main.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 3) Link to create bin/kernel8.elf
$(OUT_DIR)/kernel8.elf: $(OUT_DIR)/boot.o $(OUT_DIR)/main.o
	$(LD) $(LDFLAGS) $^ -o $@

# 4) Convert ELF -> IMG
$(OUT_DIR)/kernel8.img: $(OUT_DIR)/kernel8.elf
	$(OBJCOPY) $< -O binary $@

# Convenience short-hands
boot.o: $(OUT_DIR)/boot.o
	@ln -sf $< $@

main.o: $(OUT_DIR)/main.o
	@ln -sf $< $@

kernel8.elf: $(OUT_DIR)/kernel8.elf
	@ln -sf $< $@

kernel8.img: $(OUT_DIR)/kernel8.img
	@ln -sf $< $@

# Cleanup
clean:
	rm -rf $(OUT_DIR)
	rm -f *.o *.elf *.img

.PHONY: all clean
