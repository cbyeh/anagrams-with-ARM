/*
 * Filename: hashcodeCmp.s
 * Author: Christopher Yeh
 * UserID: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	/* PARAM STACK SPACE ALLOCATIONS */
	.equ	PARAM_SPACE, 8
	
	/* Offset for our formal parameters, p1 and p2 */
	.equ	P1_OFFSET, -8	
	.equ	P2_OFFSET, -12

	.global hashcodeCmp	@ Specify as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment

/*
 * Function Name: hashcodeCmp()
 * Function Prototype: int hashcodeCmp( const void * p1, const void * p2 );
 * Description: Takes two void pointers, but will be passed const anagram_t *
 * Compares the two, returning an int representing p1 same, smaller, or larger.
 * Parameters:
 *	r0 - arg 1 -- p1
 *	r1 - arg 2 -- p2
 * Registers used:
 *	r0 - arg 1 -- first anagram and return value
 *	r1 - arg 2 -- second anagram
 *	r2 - dummy variable to load addresses
 * Stack variables:
 *	p1hashOffset - [fp -8] -- unsigned int to store hashcode
 *	p2hashOffset - [fp -12] -- unsigned int to store hashcode
 * Side Effects: None
 * Error Conditions: None
 * Return Value:
 *  0, if the two anagrams have the same hashcode
 * +1, if p1 has a larger hashcode
 * -1, if p2 has a larger hashcode
 */
hashcodeCmp:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, PARAM_SPACE

@ Begin program
	/* Store formal params */
	str	r0, [fp, P1_OFFSET]
	str	r1, [fp, P2_OFFSET]

	/* Begin comparing */
	ldr	r0, [fp, P1_OFFSET]
	ldr     r1, [fp, P2_OFFSET]
	ldr	r2, =HASHCODE_OFFSET_G
	ldr	r2, [r2]
	ldr	r0, [r0, r2]
	ldr	r1, [r1, r2]
	cmp     r0, r1
	beq	equal			@ Same hashcodes
	cmp	r0, r1			
	blo	smaller			@ p1 hash < p2 hash
	mov	r0, 1			@ Else p2 hash > p1 hash, Return 1
	b	end

smaller:
	mov	r0, -1			@ Return -1
	b	end

equal:
	mov 	r0, 0			@ Return 0
end:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
