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
