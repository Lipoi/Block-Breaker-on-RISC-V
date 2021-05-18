.section .text
.globl SubBallspeedx
.type SubBallspeedy, @function
SubBallspeedy:
	# YOUR CODE HERE

    # sub
    # ballspeedy

    # a0 is ballspeedy

    #t0 = 0
    add t0,x0,x0

    #t0 = a0
    add t0, t0, a0

    #t0 = -a0
 #   muli t0, t0,-1

    #a0 = t0
    mv a0, t0