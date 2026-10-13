bits 64
section .text
global _mount

_mount:
	mov rax, 165
%ifdef SUPPORT_FSOPTIONS
	mov r10, rcx
%else
	xor edx, edx
	xor r10, r10
%endif
	syscall
	ret
