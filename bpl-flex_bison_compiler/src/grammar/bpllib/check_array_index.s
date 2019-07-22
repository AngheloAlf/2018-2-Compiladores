	.section	.rodata
.LC3:
	.string "[ERROR] The given array index (%li) is negative.\nExiting with error code -1\n"
	.align 8
.LC4:
	.string "[ERROR] The given array index (%li) is equal or greater than the array length (%li).\nExiting with error code -2\n"
	.text
	.globl	.check_array_index
	.type	.check_array_index, @function
.check_array_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jns		.L5
	movq	stderr(%rip), %rax
	movq	-16(%rbp), %rdx
	movl	$.LC3, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-1, %edi
	call	exit
.L5:
	movq	-16(%rbp), %rax
	cmpq	-8(%rbp), %rax
	jl		.L4
	movq	stderr(%rip), %rax
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movl	$.LC4, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-2, %edi
	call	exit
.L4:
	leave
	ret
	.size   .check_array_index, .-.check_array_index
