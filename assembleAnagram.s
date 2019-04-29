/*
 * Filename: assembleAnagram.s
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
	.equ	PARAM_SPACE, 8
	
	/* Offset for parameter originalWord */
	.equ	ORIGINAL_WORD_OFFSET, -8
	/* Offset for parameter anagram */
	.equ	ANAGRAM_OFFSET, -12

	.global assembleAnagram	@ Specify as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment

/*
 * Function Name: assembleAnagram()
 * Function Prototype: void assembleAnagram( const char * originalWord,
 *					     anagram_t * anagram );
 * Description: Assemble an anagram_t given a word, and a pointer to the
 *	anagram being assembled
 * Parameters:
 *	r0 - arg 1 -- originalWord
 *	r1 - arg 2 -- * anagram
 * Registers used:
 *	r0 - arg 1 -- also storing offsets and storing return values 
 *	r1 - arg 2 -- also loading offsets
 *	r2 - used to hold balue of MAX_WORD_SIZE = 48
 *	r3 - used to hold strlen() of originalWord
 * Side Effects: None
 * Error Conditions: None
 * Return Value:
 *	None, but anagram will be assembled with originalWord,
 *	counts, and hashcode
 */
assembleAnagram:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, PARAM_SPACE

@ Begin program
	/* Store formal params */
	str	r0, [fp, ORIGINAL_WORD_OFFSET]
	str	r1, [fp, ANAGRAM_OFFSET]

	/* Check if original word has more than 48 characters */
	ldr	r0, [fp, ORIGINAL_WORD_OFFSET]
	bl	strlen
	ldr	r3, =MAX_WORD_SIZE_G
	ldr	r3, [r3]		@ r3 = 48
	mov	r2, r0			@ Keep length in r2
	cmp	r2, r3			@ Check length >= 48
	bge	large_word		@ Go to large word

	// Otherwise len < 48, load registers for call to strncpy() 
	ldr	r0, [fp, ANAGRAM_OFFSET]
	ldr	r1, =ORIGINAL_WORD_OFFSET_G
	ldr	r1, [r1]
	add	r0, r0, r1		@ Address of anagram's originalWord
	// Address of parameter originalWord
	ldr	r1, [fp, ORIGINAL_WORD_OFFSET]
	bl	strncpy			@ Store original word in struct

large_word:
	/* Load registers for call to strncpy(), n = 47 */
	ldr	r0, [fp, ANAGRAM_OFFSET]
	ldr	r1, =ORIGINAL_WORD_OFFSET_G
	ldr	r1, [r1]
	add	r0, r0, r1		@ Address of anagram's originalWord
	@ Address of parameter originalWord
	ldr	r1, [fp, ORIGINAL_WORD_OFFSET]
	ldr	r2, =MAX_WORD_SIZE_G
	ldr	r2, [r2]
	// sub	r2, r2, 1		@ n = 47
	bl	strncpy			@ Store original word in struct
	b	make_last_null		@ Skip not_large_word

make_last_null:
	/* Store counts[47] as null */
	ldr	r0, [fp, ANAGRAM_OFFSET]
	ldr	r1, =ORIGINAL_WORD_OFFSET_G
	ldr	r1, [r1]
	add	r0, r0, r1		@ Address of anagram's originalWord
	ldr	r2, =MAX_WORD_SIZE_G
	ldr	r2, [r2]
	add	r0, r0, r2		
	sub	r0, r0, 1		@ Address of originalWord at 47
	mov	r3, 0
	strb	r3, [r0]

	/* Load registers for call to countChars() */
	ldr	r0, [fp, ANAGRAM_OFFSET]
	ldr	r1, =COUNTS_OFFSET_G
	ldr	r1, [r1]
	add	r0, r0, r1		@ Address of anagram's counts[]
	@ Address of parameter originalWord
	ldr	r1, [fp, ORIGINAL_WORD_OFFSET]

	bl	countChars 		@ word[] filled with char count

	/* Load registers for call to getHashcode() */
	ldr	r0, [fp, ANAGRAM_OFFSET]
	ldr	r1, =COUNTS_OFFSET_G
	ldr	r1, [r1]
	add	r0, r0, r1		@ Address of anagram's counts[]
	bl	getHashcode		@ Hashcode now in r0

	/* Store hashcode to our anagram */
	ldr	r2, =HASHCODE_OFFSET_G
	ldr	r1, [fp, ANAGRAM_OFFSET]@ Address of anagram
	ldr	r2, [r2]
	add	r1, r1, r2		@ Address of anagram's hashcode
	str	r0, [r1]		@ Store result of getHashcode()
					@ to anagram's hashcode

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
