.section .text
.globl SubPadBcenter
.type SubPadBcenter, @function
SubPadBcenter:
	# YOUR CODE HERE

    # sub
    # padb
    # center

    # a0 is padbcenter

    #t0 = padbcenter[1]
    lw t0, 4(a0)

    #t0 ++
    addi t0, t0, -1

    #a0 = t0
    mv a0, t0