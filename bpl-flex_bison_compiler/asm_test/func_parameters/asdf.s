	.file	"asdf.c"
	.section	.rodata
.LC0:
	.string	"%li %li %li %li \n"
	.text
	.globl	extern_arr_int
	.type	extern_arr_int, @function
extern_arr_int:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$24, %rax
	movq	(%rax), %rsi
	movq	-8(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rsi, %r8
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	ret
	.size	extern_arr_int, .-extern_arr_int
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
