.section .text
.globl SubBallspeedx
.type SubBallspeedx, @function
SubBallspeedx:
	# YOUR CODE HERE

    # sub
    # ballspeedx

    # a0 is ballspeedx

    #t0 = 0
    add t0,x0,x0

    #t0 = a0
    add t0, t0, a0

    #t0 = -a0
#    muli t0, t0,-1

    #a0 = t0
    mv a0, t0