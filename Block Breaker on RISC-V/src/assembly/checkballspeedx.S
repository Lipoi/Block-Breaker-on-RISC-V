.section .text
.globl checkballspeedx
.type checkballspeedx, @function
checkballspeedx:

	# YOUR CODE HERE

    # add
    # ballspeedx

    # a0 is ballspeedx
    # a1 is ballcenter

    #t0 = 0
    add t0,x0,x0

    #t0 = ballspeedx = a0
    add t0, t0, a0

    #t1 = ballcenter[0]
    lw t1, 0(a1)

    #t1 = t1 + t0 ballcenter[0]+speedx
    add t1, t1, t0

    #a0 = t1
    mv a0, t1
