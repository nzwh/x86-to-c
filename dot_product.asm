section .text
bits 64

default rel
global dp_imp_asm

dp_imp_asm:
	mulss xmm0, xmm1
	ret