	.file	"check_array_index.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"[ERROR] The given array index (%li) is negative.\nExiting with error code -1\n"
	.align 8
.LC1:
	.string	"[ERROR] The given array index (%li) is equal or greater than the array length (%li).\nExiting with error code -2\n"
	.text
	.globl	check_array_index
	.type	check_array_index, @function
check_array_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jns	.L2
	movq	stderr(%rip), %rax
	movq	-16(%rbp), %rdx
	movl	$.LC0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-1, %edi
	call	exit
.L2:
	movq	-16(%rbp), %rax
	cmpq	-8(%rbp), %rax
	jl	.L4
	movq	stderr(%rip), %rax
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movl	$.LC1, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-2, %edi
	call	exit
.L4:
	nop
	leave
	ret
	.size	check_array_index, .-check_array_index
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
