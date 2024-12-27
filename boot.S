  .section .text.boot
  .align 7
  .globl _start
  
// _start is the label that firmware will jump to in 64-bit mode.
_start:
  
  	//--------------------------------------------------
  	// 1. If CPU starts in EL2 (Hypervisor); drop to EL1,
  	//    If CPU is already at EL1, instructions will do nothing.
  	//--------------------------------------------------

	mrs   	x0, CurrentEL       // Read current EL
	lsr   	x0, x0, #2          // Shift right to get numeric EL
	cmp   	x0, #2
	b.ne  	1f                  // If not EL2, skip

  	// In EL2, so switch to EL1
  	// HCR_EL2 (bit 32 = RW to indicate AARCH 64 EL1)
  	mov   	x0, #(1 << 31)
  	msr   	HCR_EL2, x0
  	// SCTLR_EL1 may need to be set up as well

  	// Change EL using ERET
  	mov		x0, sp
  	msr		SP_EL1, x0
  	mrs		x0, ELR_EL2           // Next instr
  	add		x0, x0, #4            // Skip
  	msr		ELR_EL2, x0
  	mrs		x0, SPSR_EL2
  	bic		x0, x0, #0b1111     // Clear mode bits
  	mov		x1, #5
	orr 		x0, x0, x0
	msr   		SPSR_EL2, x0
  	eret

1:

  	//--------------------------------------------------
  	// 2. At EL1. Set up stack pointer, clear BSS, jump to main()
  	//--------------------------------------------------

  	// Set stack pointer (Arbitrary top of stack)
  	ldr		x0, =0x8000000
  	mov		sp, x0

	// Clear BSS
	ldr		x1, =_bss_start
	ldr		x2, =_bss_end
	mov		x3, #0

clear_bss:
  	cmp		x1, x2
  	b.ge		done_clear
  	str		x3, [x1], #8
  	b		clear_bss

done_clear:
  	// Jump to main()
  	bl		main

hang:
	wfe
	b		hang

	.align 3
_bss_start: .quad __bss_start__
_bss_end:   .quad __bss_end__
