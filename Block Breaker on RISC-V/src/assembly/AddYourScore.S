.section .text
.globl AddYourScore
.type AddYourScore, @function
AddYourScore:
	# YOUR CODE HERE

    # Add
    # your
    # score

    # a0 is yourscore

    #t0 = a0
    add t0, a0, x0

    #t0 ++
    addi t0, t0, 1

    #a0 = t0
    mv a0, t0