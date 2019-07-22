	.file	"strings.c"
	.comm	global_array,80,32
	.section	.rodata
.LC0:
	.string	"un string de prueba"
.LC1:
	.string	"otro string"
	.text
	.globl	asdfasdf
	.type	asdfasdf, @function
asdfasdf:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$.LC0, -8(%rbp)
	movq	$.LC1, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	extern_function
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	extern_function
	movq	global_array(%rip), %rax
	movq	%rax, %rdi
	call	extern_function
	nop
	leave
	ret
	.size	asdfasdf, .-asdfasdf
	.section	.rodata
.LC2:
	.string	"lets try out"
.LC3:
	.string	"how this works"
.LC4:
	.string	"!!!"
.LC5:
	.string	"this is a parameter"
	.text
	.globl	other_test_function
	.type	other_test_function, @function
other_test_function:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	$.LC2, -8(%rbp)
	movq	$.LC3, -16(%rbp)
	movq	$.LC4, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	extern_function
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	extern_function
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	extern_function
	movl	$.LC5, %edi
	call	extern_function
	nop
	leave
	ret
	.size	other_test_function, .-other_test_function
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
