.data
 newline: .asciiz "\n"
.text

main:
li $t0, 0 #i
li $t2, 0 #sum
li $v0, 5
syscall
move $t1, $v0 #n

# t0 = i
# t1 = n
# t2 = sum

loop_header:
blt $t0,$t1,loop_body
j exit

loop_body:
add $t2,$t2,$t0
j latch


latch:
add $t0,$t0,1
j loop_header


exit:

move $a0, $t2        
li $v0, 1   
syscall

jr $ra