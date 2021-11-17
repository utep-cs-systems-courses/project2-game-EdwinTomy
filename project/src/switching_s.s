  	.arch msp430g2553
	.p2align 1,0

	.extern blink_count
	
	.text
	.global switching

switching:

	cmp #63, &blink_count
	jl less
	jmp more
	
less:
	xor #1, &P1OUT
  	jmp out
  
more:
	xor #64, &P1OUT
  	jmp out
  
out:
	pop r0
