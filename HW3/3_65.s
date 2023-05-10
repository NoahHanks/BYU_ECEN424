	.file	"3_65.c"
	.text
	.p2align 4
	.globl	transpose_optimized
	.type	transpose_optimized, @function
transpose_optimized:
.LFB0:
	.cfi_startproc
	endbr64
	movq	%rdi, %rdx
	leaq	128(%rdi), %r8
.L3:
	xorl	%eax, %eax
.L2:
	movq	(%rdx,%rax), %rcx
	movq	32(%rdi,%rax,4), %rsi
	movq	%rsi, (%rdx,%rax)
	movq	%rcx, 32(%rdi,%rax,4)
	addq	$8, %rax
	cmpq	$32, %rax
	jne	.L2
	addq	$32, %rdx
	cmpq	%r8, %rdx
	jne	.L3
	ret
	.cfi_endproc
.LFE0:
	.size	transpose_optimized, .-transpose_optimized
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
