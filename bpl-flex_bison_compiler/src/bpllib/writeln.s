	.file	"writeln.c"
	.text
	.globl	writeln
	.type	writeln, @function
writeln:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$10, %edi
	call	putchar
	nop
	popq	%rbp
	ret
	.size	writeln, .-writeln
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
