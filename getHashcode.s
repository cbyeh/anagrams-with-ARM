/*
 * Filename: getHashcode.s
 * Author: Christopher Yeh
 * UserID: cs30xfv
 * Date: 2/14/2019
 * Sources of Help: None
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp
	
	/* PARAM AND LOCAL VAR STACK SPACE ALLOCATIONS */
	.equ	LOCAL_VAR_SPACE, 8
	.equ	PARAM_SPACE, 8
	
	/* Offset for array counts, location of counts[0] */
	.equ	COUNTS_OFFSET, -16	

	.equ	HASH_OFFSET, -8	@ Offset for local var hash
	.equ	I_OFFSET, -12	@ Offset for local var i

	.global getHashcode	@ Specify as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment

/*
 * Function Name: getHashcode()
 * Function Prototype: unsigned int getHashcode( unsigned char counts[] );
 * Description:
 *	Generates a hashcode from counts. 
 * Registers used:
 *	r0 - arg 1 -- counts[]
 *	r1 - hash
 *	r2 - i
 * Stack variables:
 *	hash - [fp -8] -- only used as tmp unsigned int to store hash in return
 *	i - [fp -12] -- int used for for loop
 * Side Effects: None
 * Error Conditions: None 
 * Return Value:
 *      The hashcode that corresponds to counts.	
 */
getHashcode:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, LOCAL_VAR_SPACE
	sub	sp, sp, PARAM_SPACE

@ Begin program
	str	r0, [fp, COUNTS_OFFSET]	@ Store formal param r0 

	ldr	r2, =HASH_START_VAL_G	@ Load address of global var
	ldr	r1, [r2]		@ Store HASH_START_VAL into r1
	str	r1, [fp, HASH_OFFSET]	@ Store HASH_START_VAL into hash

	/* Begin for loop, set i = 0 */
	mov	r3, 0			
	str	r3, [fp, I_OFFSET]	
	ldr	r3, [fp, I_OFFSET]	@ Get current val of i

loop:	
	ldr	r2, =HASH_PRIME_G	@ Load address of global var
	ldr	r2, [r2]		@ Store HASH_PRIME into r2
	ldr	r1, [fp, HASH_OFFSET]	@ Put hash in r2	
	
	mul	r3, r2, r1		@ r3 = hash * HASHPRIME

	/* Get counts[i] */
	ldr	r0, [fp, COUNTS_OFFSET]
	ldr	r1, [fp, I_OFFSET]
	ldrb	r1, [r0, r1]

	add	r3, r3, r1		@ r3 = previous mul + counts[i]

	str	r3, [fp, HASH_OFFSET]	@ Store new hash val

	/* Test to execute loop again */
	ldr	r3, [fp, I_OFFSET]	@ Get current val of i
	add	r3, r3, 1		@ i++
	str	r3, [fp, I_OFFSET]	

	ldr	r3, [fp, I_OFFSET]	@ Get current val of i
	ldr	r2, =ALPHABET_SIZE_G	@ Load address of global var
	ldr	r2, [r2]		@ Store ALPHABET_SIZE into r2

	cmp	r3, r2			@ i < ALPHABET_SIZE
	blt	loop			@ Positive logic to loop again

end_loop:
	ldr	r0, [fp, HASH_OFFSET]	@ Return hash

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
