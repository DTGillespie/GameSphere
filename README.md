# GameSphere
A Raspberry Pi game console kernel with a fixed function render pipeline. The purpose of the GameSphere project is to provide a modern, well-documented, and maintained system for low-level graphics programming enthusiasts and those nostalgic for 6th gen gaming consoles.

### CPU Models

#### Raspberry Pi 3/3b
```
cortex-a53
```

#### Raspberry Pi 4+
```
cortex-a72
```

## Commands

#### Compiling for cortex-a53 (Raspberry Pi 3b)
```
make raspi3
```

#### Compiling for cortex-a72 (Raspberry Pi 4+)
```
make raspi4
```

*Note: Defaults to cortex-a53 for QEMU debugging if none is specified.*

### QEMU & Debugging

#### This command will disable the QEMU monitor and redirect the UART0 output to the terminal
```
qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio -monitor none -nographic
```

#### Running QEMU with logging
```
qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio -monitor none -nographic -d cpu_reset,int -D qemu-log.txt
```

### QEMU with GDB Debugging Support

#### Launching QEMU with GDB support
```
qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio -monitor none -nographic -S -s
```

#### Attach GDB to QEMU (Note: Use the kernel8.elf for debugging not the kernel8.img)
```
gdb-multiarch kernel8.elf

target remote localhost:1234
```

#### Set breakpoints
```
b configure_mmio_base
continue
```

#### Step through
```
next    # Step to the next line
print debug_reg    # Print the value of the debug_reg pointer
print *debug_reg   # Print the value stored in the debug register
```

#### Inspect memory
```
x/x 0x3F003000  # Examine the memory at the debug register address (Pi 3B)
```

# Device Tree Souce (dt-blob.dts)

#### Compile command
``` bash
dtc -I dts -O dtb -o dt-blob.bin dt-blob.dts
```

# Misc.

### GDB Commands

#### Set variable
```
set $pc=0x80000
```

#### Inspect registers
```
info registers
```

#### Examine PC
```
x/4i $pc  # Disassemble 4 instructions at the current PC
```

#### Start execution
```
continue
```

#### Disassemble binary
```
aarch64-none-elf-objdump -D -b binary -m aarch64 kernel8.img
```

### Misc. Commands

#### Examine ELF and Binary Contents
```
readelf -h bin/kernel8.elf | grep "Entry point"
```