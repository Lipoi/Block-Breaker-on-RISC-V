.section .text
.globl subpaddlespeedy
.type subpaddlespeedy, @function
subpaddlespeedy:
		# YOUR CODE HERE

    # Add
    # opposite
    # score

    # a0 is oppositescore
    # t0 0

    lw t0,0(a0)
    lw t1,4(a0)
    addi t4,x0,2
    addi t5,x0,-1
    add a0,t0,x0
    div t2,t1,t4
    mul t2,t2,t5
    add a1,t1,x0
    add a1,a1,t2 # a1 ok
    add a2,a0,x0 # a2 ok
    add a3,t1,x0
    sub a3,a3,t2
    add a4,a4,x0
    jal LCD_DrawLine
