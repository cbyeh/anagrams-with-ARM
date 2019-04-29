/*
 * Filename: anagramCmp.s
 * Author: Christopher Yeh
 * UserID: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	/* PARAM AND LOCAL VAR STACK SPACE ALLOCATIONS */
	.equ	PARAM_SPACE, 8
	
	/* Offset for our formal params location */
	.equ	ANAGRAM_ONE_OFFSET, -8
	.equ	ANAGRAM_TWO_OFFSET, -12

	.global anagramCmp	@ Specify as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment

/*
 * Function Name: anagramCmp()
 * Function Prototype: int anagramCmp( const void * p1, const void * p2 );
 * Description: Takes two void pointers, but will be passed const anagram_t *
 * Compares the two, first by hashcodes, then by counts[]
 * Parameters:
 *	r0 - arg 1 -- p1
 *	r1 - arg 2 -- p2
 * Registers used:
 *	r0 - arg 1 -- first anagram and return value
 *	r1 - arg 2 -- second anagram
 * Side Effects: None
 * Error Conditions: None
 * Return Value:
 *  0, if the two anagrams have the same hashcode and counts
 *  1, if p1 has a larger hashcode, or the same hashcode but greater counts
 * -1, if p2 has a larger hashcode, or the same hashcode but greater counts
 */
anagramCmp:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, PARAM_SPACE

@ Begin program
	/* Store formal params */
	str	r0, [fp, ANAGRAM_ONE_OFFSET]
	str	r1, [fp, ANAGRAM_TWO_OFFSET]

	@@@@/* Load registers for comparing hashcodes */
	ldr	r0, [fp, ANAGRAM_ONE_OFFSET]
	ldr	r1, [fp, ANAGRAM_TWO_OFFSET]
	bl	hashcodeCmp
	cmp	r0, 0			@ See if we return equal
	beq	same_hashcode		@ Same, branch to check counts

	cmp	r0, 0			@ Return smaller
	blt	less			

	/* p1 hashcode > p2 hashcode */
	mov	r0, 1			@ Return bigger
	b	end			

same_hashcode:
	ldr	r0, [fp, ANAGRAM_ONE_OFFSET]
	ldr	r1, [fp, ANAGRAM_TWO_OFFSET]
	bl	countsCmp
	cmp	r0, 0			@ Check if anagrams are equal
	beq	end			@ Return equal, 0
	cmp	r0, 0			@ Check if s1 bytes < s2
	blt	less		

	/* p1 bytes > p2 bytes */
	mov	r0, 1			@ Return bigger
	b	end

less:
	mov	r0, -1			@ Return smaller

end:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
