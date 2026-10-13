bits 64
section .text
global _chroot

_chroot:
	mov rax, 161
	syscall
	ret
