.section .text

# void MatrixMul(const double *rowMatrix, const double *invec, double *outvec,
#                unsigned rowlen, unsigned collen);
.global MatrixMul
MatrixMul:
cmp $0, %rcx
je .Lquit
cmp $0, %r8
je .Lquit
pushq %rbx
xorq %rbx, %rbx
xorq %r9, %r9
xorpd %xmm0, %xmm0

.Louter:
	.Linner:
		movq (%rdi), %xmm1
		mulsd (%rsi, %rbx, 8), %xmm1
		addsd %xmm1, %xmm0
		addq $8, %rdi
		incq %rbx
		cmp %rcx, %rbx
		jb .Linner
	movq %xmm0, (%rdx, %r9, 8)
	xorpd %xmm0, %xmm0
	incq %r9
	xorq %rbx, %rbx
	cmp %r8, %r9
	jb .Louter
popq %rbx
.Lquit:
ret
