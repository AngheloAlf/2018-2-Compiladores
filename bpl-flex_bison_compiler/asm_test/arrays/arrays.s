	.file	"arrays.c"
	.comm	global_arr,80,32
	.section	.rodata
.LC0:
	.string	"%li\n"
	.text
	.globl	print_num
	.type	print_num, @function
print_num:
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
	.size	print_num, .-print_num
	.globl	local_arr_int_const_index
	.type	local_arr_int_const_index, @function
local_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
	movq	$9, -48(%rbp)
	movq	$45, -40(%rbp)
	movq	$34, -32(%rbp)
	movq	$64, -24(%rbp)
	movq	$82, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-8(%rbp), %rax
	leave
	ret
	.size	local_arr_int_const_index, .-local_arr_int_const_index
	.globl	local_arr_int_var_index
	.type	local_arr_int_var_index, @function
local_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$64, %rsp
	movq	$9, -64(%rbp)
	movq	$45, -56(%rbp)
	movq	$34, -48(%rbp)
	movq	$64, -40(%rbp)
	movq	$82, -32(%rbp)
	movq	$2, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-64(%rbp,%rax,8), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-16(%rbp), %rax
	leave
	ret
	.size	local_arr_int_var_index, .-local_arr_int_var_index
	.globl	local_arr_int_var_index_param
	.type	local_arr_int_var_index_param, @function
local_arr_int_var_index_param:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	$9, -48(%rbp)
	movq	$45, -40(%rbp)
	movq	$34, -32(%rbp)
	movq	$64, -24(%rbp)
	movq	$82, -16(%rbp)
	movq	-56(%rbp), %rax
	movq	-48(%rbp,%rax,8), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-8(%rbp), %rax
	leave
	ret
	.size	local_arr_int_var_index_param, .-local_arr_int_var_index_param
	.globl	param_arr_int_const_index
	.type	param_arr_int_const_index, @function
param_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-8(%rbp), %rax
	leave
	ret
	.size	param_arr_int_const_index, .-param_arr_int_const_index
	.globl	param_arr_int_var_index
	.type	param_arr_int_var_index, @function
param_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$2, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-16(%rbp), %rax
	leave
	ret
	.size	param_arr_int_var_index, .-param_arr_int_var_index
	.globl	param_arr_int_var_index_param
	.type	param_arr_int_var_index_param, @function
param_arr_int_var_index_param:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-8(%rbp), %rax
	leave
	ret
	.size	param_arr_int_var_index_param, .-param_arr_int_var_index_param
	.globl	global_arr_int_const_index
	.type	global_arr_int_const_index, @function
global_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	global_arr+24(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-8(%rbp), %rax
	leave
	ret
	.size	global_arr_int_const_index, .-global_arr_int_const_index
	.globl	global_arr_int_var_index
	.type	global_arr_int_var_index, @function
global_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$2, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	global_arr(,%rax,8), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-16(%rbp), %rax
	leave
	ret
	.size	global_arr_int_var_index, .-global_arr_int_var_index
	.globl	global_arr_int_var_index_param
	.type	global_arr_int_var_index_param, @function
global_arr_int_var_index_param:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	global_arr(,%rax,8), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num
	movq	-8(%rbp), %rax
	leave
	ret
	.size	global_arr_int_var_index_param, .-global_arr_int_var_index_param
	.globl	print_num_arr
	.type	print_num_arr, @function
print_num_arr:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	ret
	.size	print_num_arr, .-print_num_arr
	.globl	addr_local_arr_int_const_index
	.type	addr_local_arr_int_const_index, @function
addr_local_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
	movq	$9, -48(%rbp)
	movq	$45, -40(%rbp)
	movq	$34, -32(%rbp)
	movq	$64, -24(%rbp)
	movq	$82, -16(%rbp)
	leaq	-48(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_local_arr_int_const_index, .-addr_local_arr_int_const_index
	.globl	addr_local_arr_int_var_index
	.type	addr_local_arr_int_var_index, @function
addr_local_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$64, %rsp
	movq	$9, -64(%rbp)
	movq	$45, -56(%rbp)
	movq	$34, -48(%rbp)
	movq	$64, -40(%rbp)
	movq	$82, -32(%rbp)
	movq	$2, -8(%rbp)
	leaq	-64(%rbp), %rax
	movq	-8(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_local_arr_int_var_index, .-addr_local_arr_int_var_index
	.globl	addr_local_arr_int_var_index_param
	.type	addr_local_arr_int_var_index_param, @function
addr_local_arr_int_var_index_param:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	$9, -48(%rbp)
	movq	$45, -40(%rbp)
	movq	$34, -32(%rbp)
	movq	$64, -24(%rbp)
	movq	$82, -16(%rbp)
	leaq	-48(%rbp), %rax
	movq	-56(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_local_arr_int_var_index_param, .-addr_local_arr_int_var_index_param
	.globl	addr_param_arr_int_const_index
	.type	addr_param_arr_int_const_index, @function
addr_param_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_param_arr_int_const_index, .-addr_param_arr_int_const_index
	.globl	addr_param_arr_int_var_index
	.type	addr_param_arr_int_var_index, @function
addr_param_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$2, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_param_arr_int_var_index, .-addr_param_arr_int_var_index
	.globl	addr_param_arr_int_var_index_param
	.type	addr_param_arr_int_var_index_param, @function
addr_param_arr_int_var_index_param:
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
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_param_arr_int_var_index_param, .-addr_param_arr_int_var_index_param
	.globl	addr_global_arr_int_const_index
	.type	addr_global_arr_int_const_index, @function
addr_global_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$global_arr+24, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_global_arr_int_const_index, .-addr_global_arr_int_const_index
	.globl	addr_global_arr_int_var_index
	.type	addr_global_arr_int_var_index, @function
addr_global_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$2, -8(%rbp)
	movq	-8(%rbp), %rax
	salq	$3, %rax
	addq	$global_arr, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_global_arr_int_var_index, .-addr_global_arr_int_var_index
	.globl	addr_global_arr_int_var_index_param
	.type	addr_global_arr_int_var_index_param, @function
addr_global_arr_int_var_index_param:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	salq	$3, %rax
	addq	$global_arr, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	print_num_arr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leave
	ret
	.size	addr_global_arr_int_var_index_param, .-addr_global_arr_int_var_index_param
	.section	.rodata
.LC1:
	.string	"arr[%li] -> %li\n"
	.text
	.globl	print_arr
	.type	print_arr, @function
print_arr:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L40
.L41:
	movq	-8(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addq	$1, -8(%rbp)
.L40:
	movq	-8(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jl	.L41
	nop
	leave
	ret
	.size	print_arr, .-print_arr
	.globl	set_local_arr_int_const_index
	.type	set_local_arr_int_const_index, @function
set_local_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	$9, -48(%rbp)
	movq	$45, -40(%rbp)
	movq	$34, -32(%rbp)
	movq	$64, -24(%rbp)
	movq	$82, -16(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -24(%rbp)
	leaq	-48(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	print_arr
	nop
	leave
	ret
	.size	set_local_arr_int_const_index, .-set_local_arr_int_const_index
	.globl	set_local_arr_int_var_index
	.type	set_local_arr_int_var_index, @function
set_local_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$64, %rsp
	movq	%rdi, -56(%rbp) # value
	movq	$9, -48(%rbp) # arr
	movq	$45, -40(%rbp)
	movq	$34, -32(%rbp)
	movq	$64, -24(%rbp)
	movq	$82, -16(%rbp)
	movq	$2, -8(%rbp) # index

	movq	-56(%rbp), %r12


	movq	-8(%rbp), %r15 # index
	movq	%r12, -48(%rbp,%r15,8)

	leaq	-48(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	print_arr
	nop
	leave
	ret
	.size	set_local_arr_int_var_index, .-set_local_arr_int_var_index
	.globl	set_local_arr_int_var_index_param
	.type	set_local_arr_int_var_index_param, @function
set_local_arr_int_var_index_param:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	$9, -48(%rbp)
	movq	$45, -40(%rbp)
	movq	$34, -32(%rbp)
	movq	$64, -24(%rbp)
	movq	$82, -16(%rbp)
	movq	-56(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	%rdx, -48(%rbp,%rax,8)
	leaq	-48(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	print_arr
	nop
	leave
	ret
	.size	set_local_arr_int_var_index_param, .-set_local_arr_int_var_index_param
	.globl	set_param_arr_int_const_index
	.type	set_param_arr_int_const_index, @function
set_param_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)

	movq	-8(%rbp), %rax # array
	leaq	24(%rax), %rdx # &array[3]
	movq	-16(%rbp), %rax # value
	movq	%rax, (%rdx) # set

	movq	-8(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	print_arr
	nop
	leave
	ret
	.size	set_param_arr_int_const_index, .-set_param_arr_int_const_index
	.globl	set_param_arr_int_var_index
	.type	set_param_arr_int_var_index, @function
set_param_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp) # arr
	movq	%rsi, -32(%rbp) # value
	movq	$2, -8(%rbp) # index


	# movq	-8(%rbp), %rax # index
	# leaq	0(,%rax,8), %rdx # index*3
	movq	-32(%rbp), %r12 # value

	movq	-8(%rbp), %r15 # index
	movq	%r15, -16(%rbp) # index*3

	salq	$3, -16(%rbp) # index*3


	# movq	-8(%rbp), %r15 # index
	# salq	$3, %r15 # index*3
	# movq	%r15, -16(%rbp) # index*3

	movq	-24(%rbp), %r15 # &arr
	addq	-16(%rbp), %r15 # &arr[index]
	movq	%r12, (%r15) # set


	movq	-24(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	print_arr
	nop
	leave
	ret
	.size	set_param_arr_int_var_index, .-set_param_arr_int_var_index
	.globl	set_param_arr_int_var_index_param
	.type	set_param_arr_int_var_index_param, @function
set_param_arr_int_var_index_param:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp) # arr
	movq	%rsi, -16(%rbp) # index
	movq	%rdx, -24(%rbp) # value

	movq	-16(%rbp), %rax # index
	leaq	0(,%rax,8), %rdx # index*3
	movq	-8(%rbp), %rax # &arr
	addq	%rax, %rdx # &arr[index]
	movq	-24(%rbp), %rax # value
	movq	%rax, (%rdx) # set

	movq	-8(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	print_arr
	nop
	leave
	ret
	.size	set_param_arr_int_var_index_param, .-set_param_arr_int_var_index_param
	.globl	set_global_arr_int_const_index
	.type	set_global_arr_int_const_index, @function
set_global_arr_int_const_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)

	movq	-8(%rbp), %rax # value
	movq	%rax, global_arr+24(%rip) # set

	movl	$5, %esi
	movl	$global_arr, %edi
	call	print_arr
	nop
	leave
	ret
	.size	set_global_arr_int_const_index, .-set_global_arr_int_const_index
	.globl	set_global_arr_int_var_index
	.type	set_global_arr_int_var_index, @function
set_global_arr_int_var_index:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp) # value
	movq	$2, -8(%rbp) # index

	movq	-8(%rbp), %rax # index
	movq	-24(%rbp), %rdx # value
	movq	%rdx, global_arr(,%rax,8) # set

	movl	$5, %esi
	movl	$global_arr, %edi
	call	print_arr
	nop
	leave
	ret
	.size	set_global_arr_int_var_index, .-set_global_arr_int_var_index
	.globl	set_global_arr_int_var_index_param
	.type	set_global_arr_int_var_index_param, @function
set_global_arr_int_var_index_param:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp) # index
	movq	%rsi, -16(%rbp) # value

	movq	-16(%rbp), %rdx # value


	movq	-8(%rbp), %rax # index
	movq	%rdx, global_arr(,%rax,8) # set

	movl	$5, %esi
	movl	$global_arr, %edi
	call	print_arr
	nop
	leave
	ret
	.size	set_global_arr_int_var_index_param, .-set_global_arr_int_var_index_param
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
	movq	$9, -48(%rbp)
	movq	$45, -40(%rbp)
	movq	$34, -32(%rbp)
	movq	$64, -24(%rbp)
	movq	$82, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L52
.L53:
	movl	-4(%rbp), %eax
	leal	5(%rax), %ecx
	movl	-4(%rbp), %eax
	cltq
	movq	-48(%rbp,%rax,8), %rdx
	movl	-4(%rbp), %eax
	cltq
	movq	%rdx, global_arr(,%rax,8)
	movl	-4(%rbp), %eax
	cltq
	movq	global_arr(,%rax,8), %rdx
	movslq	%ecx, %rax
	movq	%rdx, global_arr(,%rax,8)
	addl	$1, -4(%rbp)
.L52:
	cmpl	$4, -4(%rbp)
	jle	.L53
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	param_arr_int_var_index
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	addr_param_arr_int_var_index
	movl	$0, %eax
	call	addr_global_arr_int_var_index
	leaq	-48(%rbp), %rax
	movq	$-59, %rsi
	movq	%rax, %rdi
	call	set_param_arr_int_var_index
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
