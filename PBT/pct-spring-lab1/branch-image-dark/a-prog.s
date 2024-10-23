	.file	"prog.c"
	.text
	.p2align 4
	.globl	wtime
	.type	wtime, @function
wtime:
.LFB22:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$1, %edi
	movq	%rsp, %rsi
	call	clock_gettime
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	8(%rsp), %xmm0
	mulsd	.LC0(%rip), %xmm0
	cvtsi2sdq	(%rsp), %xmm1
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	addsd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE22:
	.size	wtime, .-wtime
	.p2align 4
	.globl	image_is_dark
	.type	image_is_dark, @function
image_is_dark:
.LFB23:
	.cfi_startproc
	testl	%edx, %edx
	jle	.L11
	movslq	%esi, %r11
	xorl	%r10d, %r10d
	xorl	%r9d, %r9d
	xorl	%ecx, %ecx
	addq	%rdi, %r11
	.p2align 4,,10
	.p2align 3
.L6:
	movslq	%r10d, %r8
	leaq	(%rdi,%r8), %rax
	addq	%r11, %r8
	testl	%esi, %esi
	jle	.L10
	.p2align 4,,10
	.p2align 3
.L8:
	cmpb	$-128, (%rax)
	sbbl	$-1, %ecx
	addq	$1, %rax
	cmpq	%r8, %rax
	jne	.L8
.L10:
	addl	$1, %r9d
	addl	%esi, %r10d
	cmpl	%r9d, %edx
	jne	.L6
.L5:
	imull	%esi, %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	cmpl	%ecx, %eax
	setg	%al
	movzbl	%al, %eax
	ret
.L11:
	xorl	%ecx, %ecx
	jmp	.L5
	.cfi_endproc
.LFE23:
	.size	image_is_dark, .-image_is_dark
	.p2align 4
	.globl	image_is_dark_opt
	.type	image_is_dark_opt, @function
image_is_dark_opt:
.LFB24:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	testl	%edx, %edx
	jle	.L19
	movq	%rdi, %r11
	movslq	%esi, %rbx
	xorl	%r10d, %r10d
	xorl	%r9d, %r9d
	xorl	%edi, %edi
	addq	%r11, %rbx
	.p2align 4,,10
	.p2align 3
.L15:
	movslq	%r10d, %r8
	leaq	(%r11,%r8), %rax
	addq	%rbx, %r8
	testl	%esi, %esi
	jle	.L18
	.p2align 4,,10
	.p2align 3
.L16:
	movsbl	(%rax), %ecx
	addq	$1, %rax
	shrl	$31, %ecx
	addl	%ecx, %edi
	cmpq	%rax, %r8
	jne	.L16
.L18:
	addl	$1, %r9d
	addl	%esi, %r10d
	cmpl	%r9d, %edx
	jne	.L15
.L14:
	imull	%esi, %edx
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	cmpl	%edi, %eax
	setg	%al
	movzbl	%al, %eax
	ret
.L19:
	.cfi_restore_state
	xorl	%edi, %edi
	jmp	.L14
	.cfi_endproc
.LFE24:
	.size	image_is_dark_opt, .-image_is_dark_opt
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Time %.6f, dark %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$132710400, %edi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	call	malloc
	xorl	%edi, %edi
	movq	%rax, %r12
	leaq	15360(%r12), %rbx
	leaq	132725760(%r12), %rbp
	call	srand
	.p2align 4,,10
	.p2align 3
.L23:
	leaq	-15360(%rbx), %r13
	.p2align 4,,10
	.p2align 3
.L24:
	call	rand
	addq	$1, %r13
	cltd
	shrl	$24, %edx
	addl	%edx, %eax
	movzbl	%al, %eax
	subl	%edx, %eax
	movb	%al, -1(%r13)
	cmpq	%rbx, %r13
	jne	.L24
	leaq	15360(%r13), %rbx
	cmpq	%rbp, %rbx
	jne	.L23
	xorl	%eax, %eax
	call	wtime
	xorl	%eax, %eax
	call	wtime
	xorl	%eax, %eax
	call	wtime
	movl	$8640, %edx
	movq	%r12, %rdi
	movl	$15360, %esi
	movsd	%xmm0, 8(%rsp)
	call	image_is_dark_opt
	movl	%eax, %ebx
	xorl	%eax, %eax
	call	wtime
	subsd	8(%rsp), %xmm0
	movl	%ebx, %esi
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movq	%r12, %rdi
	call	free
	addq	$24, %rsp
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	-400107883
	.long	1041313291
	.ident	"GCC: (GNU) 13.2.1 20231205 (Red Hat 13.2.1-6)"
	.section	.note.GNU-stack,"",@progbits
