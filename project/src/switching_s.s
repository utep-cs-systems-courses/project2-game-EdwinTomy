  .arch msp430g2553
	.p2align 1,0

	.extern blink_count
	.extern green_turn
	.extern red_turn
  

switching:

	cmp #63, &blink_count
	jl less
	jmp more
	
less:
	xor #red_turn, &P1OUT
  	jmp out
  
more:
	xor #green_turn, &P1OUT
  	jmp out
  
out:
	pop r0
