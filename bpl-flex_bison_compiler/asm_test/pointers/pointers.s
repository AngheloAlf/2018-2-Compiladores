	.file	"pointers.c"
	.text
	.globl	pointer_left
	.type	pointer_left, @function
pointer_left:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	$5, (%rax)
	movq	-8(%rbp), %rax
	movq	$10, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	ret
	.size	pointer_left, .-pointer_left
	.section	.rodata
.LC0:
	.string	"asdfasdfasdf"
	.text
	.globl	point
	.type	point, @function
point:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
	movq	$85, -48(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	$42, (%rax)
	movq	-24(%rbp), %rax
	movq	$21, (%rax)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	extern_point_int
	movq	-32(%rbp), %rax
	movq	$.LC0, (%rax)
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	ret
	.size	point, .-point
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
