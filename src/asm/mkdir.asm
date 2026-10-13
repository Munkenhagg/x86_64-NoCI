bits 64
section .text
global _mkdir

_mkdir:
	mov rax, 83
	syscall
	ret
