	.section	.rodata
.LC0:
	.string	"%li"
	.text
	.globl	read
	.type	read, @function
read:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movq	-8(%rbp), %rax
	leave
	ret
	.size	read, .-read
