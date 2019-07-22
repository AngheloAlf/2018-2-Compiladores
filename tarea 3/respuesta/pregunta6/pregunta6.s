	.file	"pregunta6.c"
	.section	.rodata
.LC0:
	.string	"y = %lf"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$32, -12(%rbp)
	cmpl	$1, -20(%rbp)
	setg	%al
	movb	%al, -13(%rbp)
	movl	-12(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	$20, %eax
	imull	-12(%rbp), %eax
	subl	$135, %eax
	imull	-12(%rbp), %eax
	addl	$42, %eax
	pxor	%xmm0, %xmm0
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, -8(%rbp)
	cmpb	$0, -13(%rbp)
	je	.L2
	movq	-8(%rbp), %rax
	movq	%rax, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	movl	$.LC0, %edi
	movl	$1, %eax
	call	printf
.L2:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
