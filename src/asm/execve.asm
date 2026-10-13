bits 64
section .text
global _execve

_execve:
	mov rax, 59
	syscall
	ret
