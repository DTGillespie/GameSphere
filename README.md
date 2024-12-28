### GameSphere - A dedicated Raspberry Pi game console kernel.



```
qemu-system-aarch64 \
-M raspi3b \
-kernel ./kernel8.img \
-serial stdio \
-nographic \
-monitor none
```

```
qemu-system-aarch64 \
-M raspi3b \
-kernel ./kernel8.img \
-serial file:output.log \
-nographic \
-monitor none
```

```
qemu-system-aarch64 \
-M raspi3b \
-kernel ./kernel8.img \
-serial file:output.log \
-nographic \
-monitor none \
-d cpu,mmu,int
```