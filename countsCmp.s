/*
 * Filename: countsCmp.s
 * Author: Christopher Yeh
 * UserID: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global countsCmp	@ Specify as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment

/*
 * Function Name: countsCmp()
 * Function Prototype: int countsCmp( const void * p1, const void * p2 );
 * Description: Takes two void pointers, but will be passed const anagram_t *
 * Compares the two, by using them for a call to memcmp()
 * Parameters:
 *	r0 - arg 1 -- p1
 *	r1 - arg 2 -- p2
 * Registers used:
 *	r0 - arg 1 -- first anagram and return value
 *	r1 - arg 2 -- second anagram
 * Side Effects: None
 * Error Conditions: None
 * Return Value: The return value of memcmp
 */
countsCmp:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

@ Begin program
	
	/* Get addresses of counts[] for p1 and p2 for call to memcmp() */
	ldr	r2, =COUNTS_OFFSET_G
	ldr	r2, [r2]
	add	r0, r0, r2		@ location of counts[] in p1
	
	ldr	r2, =COUNTS_OFFSET_G
	ldr	r2, [r2]
	add	r1, r1, r2		@ location of counts[] in p2

	ldr	r3, =ALPHABET_SIZE_G
	ldr	r2, [r3]		@ Put 26 in r2 for n bytes arg

	bl	memcmp			@ Return value from memcmp()

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
