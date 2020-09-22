main: 
li $t0, 6
li $t1, 5

bgt $t0,$t1, end

add $t0,$t0,$t1
move $a0, $t0        
li $v0, 1   
syscall

end: