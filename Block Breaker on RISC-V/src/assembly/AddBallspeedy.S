.section .text
.globl AddBallspeedy
.type AddBallspeedy, @function
AddBallspeedy:
	# YOUR CODE HERE

    # add
    # ballspeedy

    # a0 is ballspeedy
    # a1 is ballcenter

    #t0 = 0
    add t0,x0,x0

    #t0 = ballspeedy = a0
    add t0, t0, a0

    #t1 = ballcenter[0]
    lw t1, 0(a1)

    #t1 = t1 + t0 ballcenter[0]+speedy
    add t1, t1, t0

    #a0 = t1
    mv a0, t1