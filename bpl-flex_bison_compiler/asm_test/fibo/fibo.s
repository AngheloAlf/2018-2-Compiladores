	.file	"fibo.c"
	.comm	__count,8,8
	.text
	.globl	fibo
	.type	fibo, @function
fibo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	__count(%rip), %rax
	addq	$1, %rax
	movq	%rax, __count(%rip)
	cmpq	$1, -40(%rbp)
	jg	.L2
	movl	$1, %eax
	jmp	.L3
.L2:
	movq	-40(%rbp), %rax
	subq	$1, %rax
	movq	%rax, -8(%rbp)
	movq	-40(%rbp), %rax
	subq	$2, %rax
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fibo
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fibo
	movq	%rax, -32(%rbp)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
.L3:
	leave
	ret
	.size	fibo, .-fibo
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
