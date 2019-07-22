	.file	"arithmetic.c"
	.section	.rodata
.LC0:
	.string	"%li\n"
	.text
	.globl	print_int
	.type	print_int, @function
print_int:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	ret
	.size	print_int, .-print_int
	.globl	addition
	.type	addition, @function
addition:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	addition, .-addition
	.globl	substraction
	.type	substraction, @function
substraction:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	subq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	substraction, .-substraction
	.globl	mul
	.type	mul, @function
mul:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	imulq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	mul, .-mul
	.globl	div
	.type	div, @function
div:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cqto
	idivq	-32(%rbp)
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	div, .-div
	.globl	mod
	.type	mod, @function
mod:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cqto
	idivq	-32(%rbp)
	movq	%rdx, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	mod, .-mod
	.globl	neg
	.type	neg, @function
neg:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	negq	%rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	neg, .-neg
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
