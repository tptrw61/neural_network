.section .text

# double Dot(const double *vec1, const double *vec2, unsigned len);
.global Dot
Dot:
xorpd %xmm0, %xmm0 # initialize dot to 0
cmp $0, %rdx
je .Lquit1
movq $0, %rcx

.Llp1:
movq (%rdi, %rcx, 8), %xmm1
mulsd (%rsi, %rcx, 8), %xmm1
addsd %xmm1, %xmm0
inc %rcx
cmp %rdx, %rcx
jb .Llp1

.Lquit1:
ret

# void AddTo(double *vec1, const double *vec2, unsigned len);
.global AddTo
AddTo:
cmp $0, %rdx
je .Lquit2
movq $0, %rcx

.Llp2:
movq (%rdi, %rcx, 8), %xmm0
addsd (%rsi, %rcx, 8), %xmm0
movq %xmm0, (%rdi, %rcx, 8)
inc %rcx
cmp %rdx, %rcx
jb .Llp2

.Lquit2:
ret

# void Add(const double *vec1, const double *vec2, double *outvec,
#          unsigned len);
.global Add
Add:
cmp $0, %rdx
je .Lquit3
movq $0, %r8
xchg %r8, %rcx

.Llp3:
movq (%rdi, %rcx, 8), %xmm0
addsd (%rsi, %rcx, 8), %xmm0
movq %xmm0, (%rdx, %rcx, 8)
inc %rcx
cmp %r8, %rcx
jb .Llp3

.Lquit3:
ret

# void SMulTo(double *vec, double d, unsigned len);
.global SMulTo
SMulTo:
cmp $0, %rsi
je .Lquit4
mov $0, %rcx

.Llp4:
movq (%rdi, %rcx, 8), %xmm1
mulsd %xmm0, %xmm1
movq %xmm1, (%rdi, %rcx, 8)
inc %rcx
cmp %rsi, %rcx
jb .Llp4

.Lquit4:
ret

# void SMul(const double *invec, double *outvec, double d, unsigned len);
.global SMul
SMul:
cmp $0, %rdx
je .Lquit5
mov $0, %rcx

.Llp5:
movq (%rdi, %rcx, 8), %xmm1
mulsd %xmm0, %xmm1
movq %xmm1, (%rsi, %rcx, 8)
inc %rcx
cmp %rdx, %rcx
jb .Llp5

.Lquit5:
ret
