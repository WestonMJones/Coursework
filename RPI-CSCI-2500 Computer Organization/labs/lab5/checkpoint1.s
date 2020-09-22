# Construct a program following the CFG on the following page that requests an integer n using the syscall
# instruction (before the start of the loop) and outputs 0, 1, . . . n-1 on its own line. The MIPS-related PDFs
# from Piazza (under Resources) will help you code up a solution. Use helloworld.s from the last lab to get
# started.
.data
 newline: .asciiz "\n"
.text

main:
li $t0, 0
li $v0, 5
syscall
move $t1, $v0

# t0 = i
# t1 = n

# for (i<n) {
# 	print n
# }

loop_header:
blt $t0,$t1,loop_body
j exit

loop_body:
move $a0, $t0        
li $v0, 1   
syscall
li $v0, 4       # you can call it your way as well with addi 
la $a0, newline       # load address of the string
syscall
j latch

latch:
add $t0,$t0,1
j loop_header

exit: