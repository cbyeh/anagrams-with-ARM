/*
 * Filename: getBucketIndex.s
 * Author: Christopher Yeh
 * UserID: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global getBucketIndex	@ Specify as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment

/*
 * Function Name: getBucketIndex()
 * Function Prototype: unsigned int getBucketIndex( unsigned int hashcode,
 *						    size_t tablesize );
 * Description:
 *	Returns the location in a queryTable given a hashcode and tablesize.
 *	The location uses a call to getURemainder
 * Parameters:
 *	r0 - arg 1 -- hashcode
 *	r1 - arg 2 -- tablesize
 * Side Effects: None
 * Error Conditions: Error in getURemainder, i.e. tablesize signed neg or 0
 * Return Value: The index in the hashtable of an anagram
 */
getBucketIndex:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

@ Begin program
	bl	getURemainder		@ Get and return hashcode % tableSize

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
