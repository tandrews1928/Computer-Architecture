.text
la $5 0     
li $4 0
syscall
la $0 0         # A = S
la $1 0         # move B to the end
lb $2 $1        # load the byte at addr B into $2
beqz $2 2       # if $t3 == 0, branch out of loop
addi $1 $1 1    # increment B
b 4             # repeat the last four steps
subi $1 $1 1    # subtract 1 to move B back
bge $0 $1 6     # if A >= B, it's a palindrome.
lb $2 $0        # load the byte at addr A into $t3,
lb $3 $1        # load the byte at addr B into $t4.
bne $2 $3 7     # if $t3 != $t4, not a palindrome.
addi $0 $0 1    # increment A,
subi $1 $1 1    # decrement B,
b 7             # repeat the last 7 steps.
la $6 1         # is a palin
li $4 1         # is a palin
syscall         # is a palin
b -5            # skip to line 27
la $6 2         # not a palin
li $4 1         # not a palin
syscall         # not a palin
li $4 2
syscall

.data
string_space 0
is_palin_msg 1
not_palin_msg 2