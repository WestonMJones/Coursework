.data
 newline: .asciiz "\n"
 star: .asciiz "*"
.text

main:
li $t0, 0 # r
li $t1, 0 # c
li $v0, 5
syscall
move $t2, $v0 #n

# t0 = r
# t1 = c
# t2 = n


loop_header_rows:
#New Line Code
li $v0, 4        
la $a0, newline
syscall

# If r<n
li $t1, 0 
blt $t0,$t2,loop_header_cols
j exit


loop_header_cols:
#If c<r
ble $t1,$t0,loop_body
j latch_rows

loop_body:
li $v0, 4       # syscall 4 (print_str)
la $a0, star     # argument: string
syscall         # print the string
j latch_cols

latch_cols:
add $t1,$t1,1
j loop_header_cols

latch_rows:
add $t0,$t0,1
j loop_header_rows

exit:
jr $ra