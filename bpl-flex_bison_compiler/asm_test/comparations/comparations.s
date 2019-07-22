	.file	"comparations.c"
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
	.globl	leq
	.type	leq, @function
leq:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-32(%rbp), %rax
	setle	%al
	movzbq	%al, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	leq, .-leq
	.globl	lss
	.type	lss, @function
lss:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-32(%rbp), %rax
	setl	%al
	movzbl	%al, %eax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	lss, .-lss
	.globl	equ
	.type	equ, @function
equ:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-32(%rbp), %rax
	sete	%al
	movzbl	%al, %eax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	equ, .-equ
	.globl	neq
	.type	neq, @function
neq:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-32(%rbp), %rax
	setne	%al
	movzbl	%al, %eax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	neq, .-neq
	.globl	gtr
	.type	gtr, @function
gtr:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-32(%rbp), %rax
	setg	%al
	movzbl	%al, %eax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	gtr, .-gtr
	.globl	geq
	.type	geq, @function
geq:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-32(%rbp), %rax
	setge	%al
	movzbl	%al, %eax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	movq	-8(%rbp), %rax
	leave
	ret
	.size	geq, .-geq
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
