	.file	"other_arrays.c"
	.comm	global_array,80,32
	.text
	.globl	example
	.type	example, @function
example:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	popq	%rbp
	ret
	.size	example, .-example
	.globl	example3
	.type	example3, @function
example3:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$56, %rsp
	movq	%rdi, -56(%rbp)
	movq	$2, -48(%rbp)
	movq	$1, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$3, -8(%rbp)
	movq	-56(%rbp), %rax
	cqto
	idivq	-8(%rbp)
	movq	%rdx, -16(%rbp)
	movq	-16(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	example
	movq	-56(%rbp), %rax
	movq	-48(%rbp,%rax,8), %rax
	leave
	ret
	.size	example3, .-example3
	.globl	example4
	.type	example4, @function
example4:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$global_array, %edi
	call	example
	movq	-24(%rbp), %rax
	movq	global_array(,%rax,8), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leave
	ret
	.size	example4, .-example4
	.globl	example5
	.type	example5, @function
example5:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	example
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	leave
	ret
	.size	example5, .-example5
	.globl	example6
	.type	example6, @function
example6:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$88, %rsp
	movq	%rdi, -88(%rbp)
	movq	$9, -80(%rbp)
	movq	$7, -72(%rbp)
	movq	$53, -64(%rbp)
	movq	$42, -56(%rbp)
	movq	$4, -48(%rbp)
	movq	$357, -40(%rbp)
	movq	$2014, -32(%rbp)
	leaq	-80(%rbp), %rax
	movq	-88(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-88(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	example
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	leave
	ret
	.size	example6, .-example6
	.globl	example7
	.type	example7, @function
example7:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	salq	$3, %rax
	addq	$global_array, %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	example
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	leave
	ret
	.size	example7, .-example7
	.globl	example8
	.type	example8, @function
example8:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	%rax, (%rdx)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	example
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leave
	ret
	.size	example8, .-example8
	.globl	example9
	.type	example9, @function
example9:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$72, %rsp
	movq	%rdi, -72(%rbp)
	movq	$9, -64(%rbp)
	movq	$7, -56(%rbp)
	movq	$53, -48(%rbp)
	movq	$42, -40(%rbp)
	movq	$4, -32(%rbp)
	movq	$357, -24(%rbp)
	movq	$2014, -16(%rbp)
	movq	-72(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rdx, -64(%rbp,%rax,8)
	movq	-72(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	example
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leave
	ret
	.size	example9, .-example9
	.globl	example10
	.type	example10, @function
example10:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, global_array(,%rax,8)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$global_array, %edi
	call	example
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leave
	ret
	.size	example10, .-example10
	.section	.rodata
.LC0:
	.string	"%i: %i\n"
	.text
	.globl	init_global
	.type	init_global, @function
init_global:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	jmp	.L20
.L21:
	movl	-4(%rbp), %eax
	imull	-4(%rbp), %eax
	leal	5(%rax), %edx
	movl	$9, %eax
	subl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$9, %eax
	subl	-4(%rbp), %eax
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	imull	-4(%rbp), %eax
	addl	$5, %eax
	movslq	%eax, %rdx
	movslq	%ecx, %rax
	movq	%rdx, global_array(,%rax,8)
	addl	$1, -4(%rbp)
.L20:
	cmpl	$9, -4(%rbp)
	jle	.L21
	nop
	leave
	ret
	.size	init_global, .-init_global
	.section	.rodata
.LC1:
	.string	"%li\n"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp
	movl	$0, %eax
	call	init_global
	movq	$2, -80(%rbp)
	movq	$1, -72(%rbp)
	movq	$56, -64(%rbp)
	movq	$987, -56(%rbp)
	movq	$357, -48(%rbp)
	movq	$2014, -40(%rbp)
	movq	$65856, -32(%rbp)
	movq	$1, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-80(%rbp,%rax,8), %rax
	movq	%rax, -16(%rbp)
	movl	$3, %edi
	call	example9
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$4, %edi
	call	example10
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	leaq	-80(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	example8
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	example
	leave
	ret
	.size	main, .-main
	.globl	example2
	.type	example2, @function
example2:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$120, %rax
	movq	$42, (%rax)
	nop
	popq	%rbp
	ret
	.size	example2, .-example2
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
