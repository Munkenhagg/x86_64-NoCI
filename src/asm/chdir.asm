bits 64
section .text
global _chdir

_chdir:
	mov rax, 80
	syscall
	ret
