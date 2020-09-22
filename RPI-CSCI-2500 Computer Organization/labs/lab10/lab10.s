.data

array:       .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
newline:     .asciiz "\n"
tab:         .asciiz "\t"

.text
.globl main

main:
    la $s0, array
    # 64 = 16 * 4
    li $s1, 64
    add $s1, $s0, $s1
    j loop_header

loop_header:
    blt $s0, $s1, loop_body
    j loop_exit

loop_body:
    lw $a0, 0($s0)
    li $v0, 1
    syscall
    li $v0, 4
    la $a0, newline
    syscall
    
    lw $t0, 0($s0)
    addi $t0, $t0, 1
    sw $t0, 0($s0)
    j loop_latch

loop_latch:
    add $s0, $s0, 4
    j loop_header

loop_exit:

jr $ra          # retrun to caller
