.section .text
.globl AddOppositeScore
.type AddOppositeScore, @function
AddOppositeScore:
	# YOUR CODE HERE

    # Add
    # opposite
    # score

    # a0 is OppositeScore

    #t0 = a0
    add t0, a0, x0

    #t0 ++
    addi t0, t0, 1

    #a0 = t0
    mv a0, t0