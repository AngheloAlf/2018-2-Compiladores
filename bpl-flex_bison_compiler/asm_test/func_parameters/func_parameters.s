	.file	"func_parameters.c"
	.text
	.globl	params
	.type	params, @function
params:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	movq	16(%rbp), %rdi
	call	extern_arr_int
	movq	24(%rbp), %rax
	movq	%rax, %rdi
	call	extern_arr_int
	movl	$0, %eax
	leave
	ret
	.size	params, .-params
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	$1, -8(%rbp)
	movq	$2, -16(%rbp)
	movq	$3, -24(%rbp)
	movq	$4, -32(%rbp)
	movq	-16(%rbp), %r8
	movq	-8(%rbp), %rdi
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	subq	$8, %rsp
	pushq	-8(%rbp)
	pushq	-32(%rbp)
	pushq	-24(%rbp)
	movq	%r8, %r9
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	multiple_parameter
	addq	$32, %rsp
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
