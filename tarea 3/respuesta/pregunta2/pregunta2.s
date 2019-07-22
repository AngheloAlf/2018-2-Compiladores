	.file	"pregunta2.c"
	.text
	.globl	square
	.type	square, @function
square:
.LFB38:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L3
	movsbl	(%rdi), %edx
	movsbl	1(%rdi), %eax
	addl	%edx, %eax
	movsbl	2(%rdi), %edx
	subl	%edx, %eax
	ret
.L3:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE38:
	.size	square, .-square
	.globl	square_pure
	.type	square_pure, @function
square_pure:
.LFB39:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L6
	movsbl	(%rdi), %edx
	movsbl	1(%rdi), %eax
	addl	%edx, %eax
	movsbl	2(%rdi), %edx
	subl	%edx, %eax
	ret
.L6:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE39:
	.size	square_pure, .-square_pure
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s"
.LC1:
	.string	"%i"
	.text
	.globl	main
	.type	main, @function
main:
.LFB40:
	.cfi_startproc
	subq	$120, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 104(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	movq	%rsp, %rdi
	call	square_pure
	leal	(%rax,%rax), %edx
	movl	$.LC1, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movq	104(%rsp), %rcx
	xorq	%fs:40, %rcx
	je	.L8
	call	__stack_chk_fail
.L8:
	movl	$0, %eax
	addq	$120, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE40:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
