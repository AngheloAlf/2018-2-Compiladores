	.section	.rodata
.LC1:
	.string	"%li "
	.text
	.globl	.write_int
	.type	.write_int, @function
.write_int:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	ret
	.size	.write_int, .-.write_int

	.section	.rodata
.LC2:
	.string	"%s "
	.text
	.globl	.write_string
	.type	.write_string, @function
.write_string:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	ret
	.size	.write_string, .-.write_string

