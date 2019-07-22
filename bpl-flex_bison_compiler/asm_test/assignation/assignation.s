	.file	"assignation.c"
	.comm	global_long,8,8
	.comm	global_pointer,8,8
	.comm	global_string,8,8
	.comm	global_arr,80,32
	.text
	.globl	long_add
	.type	long_add, @function
long_add:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -24(%rbp)
	movq	global_long(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	42(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	ret
	.size	long_add, .-long_add
	.globl	long_pointer
	.type	long_pointer, @function
long_pointer:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -24(%rbp)
	movq	global_pointer(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	42(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	ret
	.size	long_pointer, .-long_pointer
	.globl	long_ampesand
	.type	long_ampesand, @function
long_ampesand:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -24(%rbp)
	movq	$global_long, -8(%rbp)
	movq	global_pointer(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	42(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	ret
	.size	long_ampesand, .-long_ampesand
	.globl	long_arr
	.type	long_arr, @function
long_arr:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -24(%rbp)
	movq	global_arr+24(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	ret
	.size	long_arr, .-long_arr
	.globl	long_arr_ampersand
	.type	long_arr_ampersand, @function
long_arr_ampersand:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -24(%rbp)
	movq	$global_arr+56, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	ret
	.size	long_arr_ampersand, .-long_arr_ampersand
	.globl	long_arr_par
	.type	long_arr_par, @function
long_arr_par:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -24(%rbp)
	movq	$24, -8(%rbp)
	movq	-24(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, (%rdx)
	nop
	popq	%rbp
	ret
	.size	long_arr_par, .-long_arr_par
	.section	.rodata
.LC0:
	.string	"99"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$99, global_long(%rip)
	movq	$.LC0, global_string(%rip)
	movq	$42, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	leaq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	long_add
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	long_add
	movq	-8(%rbp), %rax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
