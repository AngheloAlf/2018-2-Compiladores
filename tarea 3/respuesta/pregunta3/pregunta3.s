	.file	"pregunta3.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s"
.LC1:
	.string	"%i\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	subq	$120, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 104(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	movsbl	(%rsp), %edx
	movsbl	1(%rsp), %eax
	addl	%eax, %edx
	movsbl	2(%rsp), %eax
	subl	%eax, %edx
	movl	$.LC1, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movq	104(%rsp), %rcx
	xorq	%fs:40, %rcx
	je	.L2
	call	__stack_chk_fail
.L2:
	movl	$0, %eax
	addq	$120, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
