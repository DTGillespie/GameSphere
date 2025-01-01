    .section .text.boot
    .align 7
    .globl _start
  
_start:
  
    //Drop to EL1 if in EL2
	mrs     x0, CurrentEL       // Read current EL
	lsr     x0, x0, #2          // Shift right to get numeric EL
	cmp     x0, #2
	b.ne    1f                  // If not EL2, skip

	// Switch to EL1
    mov     x0, #(1 << 31)      // HCR_EL2: RW to indicate AARCH64 EL1
    msr     HCR_EL2, x0
    mov	    x0, sp              // Copy current stack pointer
    msr	    SP_EL1, x0
    mrs	    x0, ELR_EL2         // Return address
    add	    x0, x0, #4          // Skip current instruction
    msr	    ELR_EL2, x0
    mrs	    x0, SPSR_EL2        // Current status
    bic	    x0, x0, #0b1111   // Clear mode bits
    mov     x1, #0b0101       // Load the immediate value into another register
    orr     x0, x0, x1          // Perform the ORR with the value in x1
	msr     SPSR_EL2, x0
    eret                        // Return to EL1

1:

    // Set stack pointer
    ldr		x0, =0x8000000      // Arbitrary top of stack
    mov		sp, x0

	// Clear BSS
	ldr		x1, =__bss_start__
	ldr		x2, =__bss_end__
	mov		x3, #0

clear_bss:
    cmp		x1, x2             // Check if we have reached the end
    b.ge	done_clear         // If so, exit loop
    str		x3, [x1], #8       // Store 0 and increment pointer
    b		clear_bss          // Repeat

done_clear:
    // Jump to main()
    bl		main

hang:
	wfe                     // Wait for an interrupt
	b		hang            // Loop indefinitely

.align 3
_bss_start: .quad __bss_start__
_bss_end:   .quad __bss_end__
