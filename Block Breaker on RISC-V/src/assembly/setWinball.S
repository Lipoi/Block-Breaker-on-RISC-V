.section .text
.globl setWinball
.type setWinball, @function
setWinball:
	# YOUR CODE HERE

    # set
    # your
    # winball

    # a0 is winball

    #t0=0
    add t0,x0,x0

    #t0 = 1
    addi t0, t0, 1

    #a0 = t0
    mv a0, t0
