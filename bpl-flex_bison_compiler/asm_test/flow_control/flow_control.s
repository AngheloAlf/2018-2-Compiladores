	.file	"flow_control.c"
	.section	.rodata
.LC0:
	.string	"%li\n"
	.text
	.globl	print_int
	.type	print_int, @function
print_int:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	ret
	.size	print_int, .-print_int
	.globl	if_test
	.type	if_test, @function
if_test:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	setg	%al
	movzbl	%al, %eax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L3
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	jmp	.L5
.L3:
	movq	-24(%rbp), %rax
	negq	%rax
	movq	%rax, %rdi
	call	print_int
.L5:
	nop
	leave
	ret
	.size	if_test, .-if_test
	.globl	while_test
	.type	while_test, @function
while_test:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	jmp	.L7
.L9:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_int
	cmpq	$0, -8(%rbp)
	jle	.L8
	subq	$1, -8(%rbp)
	jmp	.L7
.L8:
	cmpq	$0, -8(%rbp)
	jns	.L7
	addq	$1, -8(%rbp)
.L7:
	cmpq	$0, -8(%rbp)
	jne	.L9
	nop
	leave
	ret
	.size	while_test, .-while_test
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
