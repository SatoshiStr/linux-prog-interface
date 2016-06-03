	.file	"longjump.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d, %d\n"
	.text
	.globl	dojump
	.type	dojump, @function
dojump:
.LFB24:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	%edi, %edx
	movl	%esi, %ecx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movl	$1, %esi
	movl	$env, %edi
	call	__longjmp_chk
	.cfi_endproc
.LFE24:
	.size	dojump, .-dojump
	.globl	dojump2
	.type	dojump2, @function
dojump2:
.LFB25:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	%edi, %edx
	movl	%esi, %ecx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movl	$2, %esi
	movl	$env, %edi
	call	__longjmp_chk
	.cfi_endproc
.LFE25:
	.size	dojump2, .-dojump2
	.section	.rodata.str1.1
.LC1:
	.string	"first ret: %d, %d\n"
.LC2:
	.string	"back from 1: %d, %d\n"
.LC3:
	.string	"back from 2"
	.text
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$111, 8(%rsp)
	movl	$222, 12(%rsp)
	movl	$env, %edi
	call	_setjmp
	cmpl	$1, %eax
	je	.L7
	cmpl	$2, %eax
	je	.L8
	testl	%eax, %eax
	.p2align 4,,3
	jne	.L10
	movl	$333, 8(%rsp)
	movl	$444, 12(%rsp)
	movl	12(%rsp), %ecx
	movl	8(%rsp), %edx
	movl	$.LC1, %esi
	movl	$1, %edi
	call	__printf_chk
	movl	12(%rsp), %esi
	movl	8(%rsp), %edi
	call	dojump
.L7:
	movl	12(%rsp), %ecx
	movl	8(%rsp), %edx
	movl	$.LC2, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	jmp	.L10
.L8:
	movl	$.LC3, %edi
	call	puts
.L10:
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.local	env
	.comm	env,200,32
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.1) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
