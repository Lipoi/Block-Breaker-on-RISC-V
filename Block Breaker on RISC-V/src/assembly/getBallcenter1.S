.section .text
.globl getBallcenter1
.type getBallcenter1 @function
getBallcenter1:
	# YOUR CODE HERE

    # a0 is ballcenter

    #t0 = 0
    add t0,x0,x0

    #t0 = padcenter[1]
    lw t0,4(a0)

    #a0 = t0
    mv a0, t0
