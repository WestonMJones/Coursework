#############################################################################
#############################################################################
## Assignment 3: Weston Jones
#############################################################################
#############################################################################

#############################################################################
#############################################################################
## Data segment
#############################################################################
#############################################################################

.data

matrix_a:    .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
matrix_b:    .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
result:      .word 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0

newline:     .asciiz "\n"
tab:         .asciiz "\t"

prompt1:     .asciiz "Enter the values for matrix A:\n"
prompt2:     .asciiz "Enter the values for matrix B:\n"
output:      .asciiz "Product A x B matrices:\n"


#############################################################################
#############################################################################
## Text segment
#############################################################################
#############################################################################

.text                  # this is program code
.align 2               # instructions must be on word boundaries
.globl main            # main is a global label
.globl multiply
.globl matrix_multiply
.globl matrix_print
.globl matrix_ask

#############################################################################
matrix_ask:
#############################################################################
# Ask the user for the current matrix residing in the $a0 register
    sub $sp, $sp, 4
    sw $ra, 0($sp)

    # init our counter
    li $t0, 0
    # t1 holds our the address of our matrix
    move $t1, $a0

ma_head:
# if counter less than 16, go to ma_body
# else go to exit
    li $t2, 16
    blt $t0, $t2, ma_body
    j ma_exit

ma_body:
    # read int
    li $v0, 5
    syscall
    li $t2, 4
    # ints are 4 bytes
    multu $t0, $t2
    mflo $t2
    add $t2, $t2, $t1
    sw $v0, 0($t2)
    j ma_latch

ma_latch:
    addi $t0, $t0, 1
    j ma_head

ma_exit:
    lw $ra, 0($sp)
    add $sp, $sp, 4
    jr $ra

#############################################################################
main:
#############################################################################
    # alloc stack and store $ra
    sub $sp, $sp, 4
    sw $ra, 0($sp)

    # load A, B, and result into arg regs
    li $v0, 4
    la $a0, prompt1
    syscall

    la $a0, matrix_a
    jal matrix_ask

    li $v0, 4
    la $a0, prompt2
    syscall

    la $a0, matrix_b
    jal matrix_ask

    la $a0, matrix_a
    la $a1, matrix_b
    la $a2, result
    jal matrix_multiply

    li $v0, 4
    la $a0, output
    syscall

    la $a0, result 
    jal matrix_print

    # restore $ra, free stack and return
    lw $ra, 0($sp)
    add $sp, $sp, 4
    jr $ra

##############################################################################
multiply:
##############################################################################  
# mult subroutine $a0 times $a1 and returns in $v0

    # start with $t0 = 0
    add $t0,$zero,$zero
mult_loop:
    # loop on a1
    beq $a1,$zero,mult_eol

    add $t0,$t0,$a0
    sub $a1,$a1,1
    j mult_loop

mult_eol:
    # put the result in $v0
    add $v0,$t0,$zero

    jr $ra

##############################################################################
matrix_multiply: 
##############################################################################
# mult matrices A and B together of square size N and store in result.

    # alloc stack and store regs
    sub $sp, $sp, 24
    sw $ra, 0($sp)
    sw $a0, 4($sp)
    sw $a1, 8($sp)
    sw $s0, 12($sp)
    sw $s1, 16($sp)
    sw $s2, 20($sp)

    #Setup local vars
    li $s0, 0 #i
    li $s1, 0 #j
    li $s2, 0 #k

    #store addresses of matrices in registers
    move $s3 $a0
    move $s4 $a1

    #setup constants
    li $t1, 4  #4
    li $t2, 16 #16

    #setup for i loop
    i_loop_header:
    #Reset j
    li $s1,0
    #if i<4
    blt $s0,$t1,j_loop_header
    j loop_end

    #setup for j loop
    j_loop_header:
    #Reset K
    li $s2, 0
    #if j<4
    blt $s1,$t1,k_loop_header
    j i_loop_latch

    #setup for k loop
    k_loop_header:
    #if k<4
    blt $s2,$t1,multiply_body
    j j_loop_latch

    multiply_body:

    # compute A[i][k] address and load into $t3
    # A[i][k] = (16*i) + (4*k) + $s3
    # $t5 will hold address

    li $t5, 0

    #Compute 16*i
    move $a0, $t2
    move $a1, $s0
    jal multiply
    add $t5, $t5, $v0

    #Compute 4*k
    move $a0, $t1
    move $a1, $s2
    jal multiply
    add $t5, $t5, $v0

    #Add pointer to offset and load into $t3
    add $t5,$t5,$s3
    lw $t3, ($t5)

    # compute B[k][j] address and load into $t4
    # B[k][j] = (16*k) + (4*j) + $s4
    # $t6 will hold address

    li $t6, 0

    #Compute 16*k
    move $a0, $t2
    move $a1, $s2
    jal multiply
    add $t6, $t6, $v0

    #Compute 4*j
    move $a0, $t1
    move $a1, $s1
    jal multiply
    add $t6, $t6, $v0

    #Add pointer to offset and load into $t4
    add $t6,$t6,$s4
    lw $t4, ($t6)

    # call the multiply function
    move $a0,$t3
    move $a1,$t4
    jal multiply

    #store result in $t9
    move $t9, $v0

    #compute Result[i][j] address and load into $t7
    # R[i][j] = (16*i) + (4*j) + $a2
    # $t8 will hold address

    li $t8, 0

    #Compute 16*i
    move $a0, $t2
    move $a1, $s0
    jal multiply
    add $t8, $t8, $v0

    #Compute 4*j
    move $a0, $t1
    move $a1, $s1
    jal multiply
    add $t8, $t8, $v0

    #add offset to pointer
    add $t8,$t8,$a2

    lw $t0, ($t8)
    add $t9, $t0, $t9
    sw $t9, ($t8)

    j k_loop_latch

    # increment k and jump back or exit
    k_loop_latch:
    add $s2,$s2,1
    j k_loop_header

    #increment j and jump back or exit
    j_loop_latch:
    add $s1,$s1,1
    j j_loop_header

    #increment i and jump back or exit
    i_loop_latch:
    add $s0,$s0,1
    j i_loop_header

    loop_end:

    # retore saved regs from stack
    lw $s2, 20($sp)
    lw $s1, 16($sp)
    lw $s0, 12($sp)
    lw $a1, 8($sp)
    lw $a0, 4($sp)
    lw $ra, 0($sp)

    # free stack and return
    add $sp, $sp, 24
    jr $ra

##############################################################################
matrix_print:
##############################################################################

    # alloc stack and store regs.
    sub $sp, $sp, 16
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    sw $a0, 12($sp)

    li $t0, 4 # size of array
    li $t6, 16 # size of row
    li $t1, 0 # r
    li $t2, 0 # c
    move $t3, $a0 #address of matrix

    # do your two loops here
    loop_header_rows:
    li $t2, 0 #reset column count 
    # If r<4
    blt $t1,$t0,loop_header_cols
    j exit

    loop_header_cols:
    #If c<4
    blt $t2,$t0,loop_body
    j latch_rows

    loop_body:
    #Current cell is (16*r) + (4*c) + $t3
    li $t4, 0
    li $t5, 0

    #Compute 16*r
    multu $t1, $t6
    mflo $t4

    #Compute 4*c
    multu $t2, $t0
    mflo $t5

    #Compute address
    add $t4,$t4,$t5
    add $t4,$t4,$t3

    lw $t5, 0($t4)

    #Print cell value
    move $a0, $t5       
    li $v0, 1   
    syscall

    #Print tab
    li $v0, 4        
    la $a0, tab
    syscall
    j latch_cols

    latch_cols:
    add $t2,$t2,1
    j loop_header_cols

    latch_rows:
    add $t1,$t1,1

    #Print new line
    li $v0, 4        
    la $a0, newline
    syscall

    j loop_header_rows

    exit:
    # setup to jump back and return

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $a0, 12($sp)
    add $sp, $sp, 16
    jr $ra
