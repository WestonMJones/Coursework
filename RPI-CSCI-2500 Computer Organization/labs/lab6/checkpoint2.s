.data
 Fizz: .asciiz "Fizz"
 Buzz: .asciiz "Buzz"
 FizzBuzz: .asciiz "FizzBuzz"
 newline: .asciiz "\n"
.text

main:
# t0 = 0
# t1 = i
# t2 = 21
# t3 = 3
# t4 = 3 and 5 remainder holder
# t5 = 5
# t6 = 3 remainder holder
# t7 = 5 remainder holder

li $t0, 0
li $t1, 1
li $t2, 21
li $t3, 3
li $t4, 0
li $t5, 5

li $t6, 0
li $t7, 0

loop_header:
blt $t1,$t2,loop_body
j exit


loop_body:
#Check 3 and 5
div $t1, $t3
mfhi $t6

div $t1, $t5
mfhi $t7

add $t4,$t6,$t7

beq $t4,$t0,write_fizzbuzz
beq $t6,$t0,write_fizz
beq $t7,$t0,write_buzz

move $a0, $t1        
li $v0, 1   
syscall
j latch

write_fizzbuzz:
li $v0, 4    
la $a0, FizzBuzz
syscall
j latch

write_fizz:
li $v0, 4    
la $a0, Fizz
syscall
j latch

write_buzz:
li $v0, 4    
la $a0, Buzz
syscall
j latch

latch:

#Print new line
li $v0, 4        
la $a0, newline
syscall

#Reset Registers
li $t4, 0
li $t6, 0
li $t7, 0

add $t1,$t1,1
j loop_header

exit:
jr $ra