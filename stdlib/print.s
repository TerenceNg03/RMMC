.section .text
#.globl _start
.globl putchar
.globl puts

# a0: input char
# Test passed
putchar:
	la a1, putchar_buf
	sb a0, 0(a1)
	li a0, 1
	li a2, 1                   
	li a7, 64                   
	ecall                       # system call
	li a0,1
	ret
	
# a0: char*
# Test passed
puts:
	li a2, 0
	mv t0, a0
	lw t1, 0(t0) # t1 = a0[0]
puts_loop:
	beq t1, x0, puts_loop_end
	addi a2, a2, 1
	addi t0, t0, 1
	lw t1, 0(t0)
	j puts_loop
puts_loop_end:
	mv a1, a0
	li a0, 1
	li a7, 64
	ecall
	li a0, 1
	ret
	

_start:
	li a0, 'a'
	call putchar
	li a0, '\n'
	call putchar
	la a0, puts_test
	call puts
	li a0, 0
	li a1, 0
	li a2, 0
	li a3, 0
	li a7, 93                   # _NR_sys_exit
	ecall                       # system call

.section .rodata
puts_test:
	.string "Hello, world\n"

.section .data
putchar_buf:
	.string "H"
