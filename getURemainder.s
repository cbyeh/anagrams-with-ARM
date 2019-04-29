/*
 * Filename: getURemainder.s
 * Author: Christopher Yeh
 * UserID: cs30xfv
 * Date: 2/15/2019
 * Sources of Help:
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global getURemainder	@ Specify as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment
			
/*
 * Function Name: getURemainder()
 * Function Prototype: int getURemainder( int dividend, int divisor);
 * Description:
 * 	Returns unsigned remainder
 * 	E.g. getRemainder(4, 3) should return 1
 * Parameters:
 *	r0 - arg 1 -- dividend
 *	r1 - arg 2 -- divisor
 * Side Effects: None
 * Error Conditions: Division by 0
 * Return Value: Unsigned remainder
 */	
getURemainder:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	/* Incoming parameters in r0, r1 */
	udiv	r2, r0, r1		@ r2 = r0 / r1
	mul	r3, r2, r1		@ r3 = r2 * r1
	sub	r2, r0, r3		@ r2 = r0 - r3
	mov	r0, r2			@ Put return value of remainder

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
