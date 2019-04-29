/*
 * Filename: isInBounds.s
 * Author: Christopher Yeh
 * UserID: cs30xfv
 * Date: 1/23/2019
 * Sources of Help: None
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global isInBounds	@ Specify as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment

/*
 * Function Name: isInBounds()
 * Function Prototype: int isInBounds( int a, int b, int c);
 * Description:
 * Checks if value is between minBound and maxBound(both inclusive)
 * Returns 1 if val is in that range, 0 otherwise
 * Parameters:
 *	r0 - arg 1 -- value
 *	r1 - arg 2 -- minBound
 *	r2 - arg 3 -- maxBound
 * Registers used:
 *	r0 - arg 1 -- value
 *	r1 - arg 2 -- minBound
 *	r2 - arg 3 -- maxBound
 * Side Effects: None
 * Error Conditions: 
 * 	Return -1 if minBound > maxBound
 * Return Value:
 *	-1, 0, and 1, for error case, bad case, and good case respectively.
 */
isInBounds:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

@ Incoming parameters in r0, r1, r2
	cmp	r1, r2			@ Compare minBound with maxBound
	ble	if			@ minBound <= maxBound, move on
	mov 	r0, -1			@ Error case, minBound > maxBound
	b	end

if:
	cmp	r0, r1			@ Compare value to minBound
	blt	else			@ Does not meet, branch to else
	cmp	r0, r2			@ Compare value to maxBound
	bgt	else			@ Does not meet, branch to else
	mov 	r0, 1			@ Good case, value is within bounds
	b	end			@ Branch to end

else:
	mov 	r0, 0			@ Bad case, value is not within bounds

end:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@    return
