	.file	"2.c"
	.local	env
	.comm	env,200,32
	.section	.rodata
.LC0:
	.string	"first errjmp"
.LC1:
	.string	"return by longjmp in errjmp"
	.text
	.globl	errjmp
	.type	errjmp, @function
errjmp:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$env, %edi
	call	_setjmp
	testl	%eax, %eax
	jne	.L2
	movl	$.LC0, %edi
	call	puts
	jmp	.L4
.L2:
	movl	$.LC1, %edi
	call	puts
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	errjmp, .-errjmp
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	errjmp
	movl	$1, %esi
	movl	$env, %edi
	call	longjmp
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.1) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
