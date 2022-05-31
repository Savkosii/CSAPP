	.file	"asm.c"
	.text
	.globl	decode2
	.type	decode2, @function
decode2:
.LFB0:
	.cfi_startproc
	endbr64
	movq	%rsi, %rax
	subq	%rdx, %rax
	salq	$63, %rax
	sarq	$63, %rax
	imulq	%rdi, %rsi
	xorq	%rsi, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	decode2, .-decode2
	.globl	loop
	.type	loop, @function
loop:
.LFB1:
	.cfi_startproc
	endbr64
	movl	%esi, %ecx
	movl	$1, %eax
	movl	$0, %edx
.L3:
	movq	%rdi, %rsi
	andq	%rax, %rsi
	orq	%rsi, %rdx
	salq	%cl, %rax
	testq	%rax, %rax
	jne	.L3
	movq	%rdx, %rax
	ret
	.cfi_endproc
.LFE1:
	.size	loop, .-loop
	.globl	cread_alt
	.type	cread_alt, @function
cread_alt:
.LFB2:
	.cfi_startproc
	endbr64
	testq	%rdi, %rdi
	leaq	zero.0(%rip), %rax
	cmove	%rax, %rdi
	movq	(%rdi), %rax
	ret
	.cfi_endproc
.LFE2:
	.size	cread_alt, .-cread_alt
	.globl	cread
	.type	cread, @function
cread:
.LFB3:
	.cfi_startproc
	endbr64
	movl	$0, %eax
	testq	%rdi, %rdi
	je	.L7
	movq	(%rdi), %rax
.L7:
	ret
	.cfi_endproc
.LFE3:
	.size	cread, .-cread
	.globl	siwtch3
	.type	siwtch3, @function
siwtch3:
.LFB4:
	.cfi_startproc
	endbr64
	cmpl	$3, %edx
	je	.L11
	ja	.L12
	testl	%edx, %edx
	je	.L13
	movq	$59, (%rdi)
	movq	(%rsi), %rax
	ret
.L12:
	cmpl	$4, %edx
	movl	$12, %eax
	movl	$27, %edx
	cmove	%rdx, %rax
	ret
.L13:
	movq	(%rsi), %rax
	movq	%rax, (%rdi)
	ret
.L11:
	movq	(%rsi), %rax
	movq	%rax, (%rdi)
	movl	$27, %eax
	ret
	.cfi_endproc
.LFE4:
	.size	siwtch3, .-siwtch3
	.globl	switch_prob
	.type	switch_prob, @function
switch_prob:
.LFB5:
	.cfi_startproc
	endbr64
	subq	$60, %rsi
	cmpq	$5, %rsi
	ja	.L24
	leaq	.L19(%rip), %rdx
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L19:
	.long	.L22-.L19
	.long	.L23-.L19
	.long	.L22-.L19
	.long	.L21-.L19
	.long	.L20-.L19
	.long	.L18-.L19
	.text
.L22:
	leaq	0(,%rdi,8), %rax
	ret
.L23:
	leaq	75(%rdi), %rax
	ret
.L21:
	movq	%rdi, %rax
	sarq	$3, %rax
	ret
.L20:
	movq	%rdi, %rax
	salq	$4, %rax
	subq	%rdi, %rax
	movq	%rax, %rdi
.L18:
	imulq	%rdi, %rdi
	leaq	75(%rdi), %rax
	ret
.L24:
	movq	%rdi, %rax
	ret
	.cfi_endproc
.LFE5:
	.size	switch_prob, .-switch_prob
	.local	zero.0
	.comm	zero.0,8,8
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
