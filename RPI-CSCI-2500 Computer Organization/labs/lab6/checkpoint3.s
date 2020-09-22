
fib:
addi $sp, $sp, -12 #Store 3 items on the stack
sw $ra, 8($sp)
sw $s0, 4($sp)
sw $s1, 0($sp)
move $s0, $a0
li $v0, 1 # store return value for terminal condition in return register
ble $s0, 2, fibExit # check terminal condition
addi $a0, $s0, -1 # set args for recursive call to f(n-1)
jal fib
move $s1, $v0 # store result of f(n-1) to s1
addi $a0, $s0, -2 # set args for recursive call to f(n-2)
jal fib
add $v0, $s1, $v0 # add result of f(n-1) to it
fibExit:
lw $ra, 8($sp)
lw $s0, 4($sp)
lw $s1, 0($sp)
addi $sp, $sp, 12
jr $ra

main:

# Read string
li $v0, 5
syscall

# Call fibonacci
move $a0, $v0
jal fib
move $a1, $v0 # save return value to a1

# Print result
li $v0, 1
move $a0, $a1
syscall

# Exit
li $v0, 10
syscall
