
main:
li $t0, 12 #a
li $t1, 8 #b

loop:

beq $t0,$t1,loopend

#if a > b jump to loopb

bgt $t0,$t1,loopb

#else continue down and do b - a

sub $t1,$t1,$t0
j loop

loopb:
sub $t0,$t0,$t1
j loop


loopend:

move $a0, $t0        
li $v0, 1   
syscall
