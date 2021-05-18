.section .text
.globl PadbcenterPadlengthCheckUp
.type PadbcenterPadlengthCheckUp, @function
PadbcenterPadlengthCheckUp:

#a0 is padbcenter
#a1 is padlength

#t0 = padbcenter[1]
lw t0,4(a0)

#t1 = 0
add t1,x0,x0

#t1 = 2
addi t1,t1,2

#a1 = a1/2
div a1,a1,t1

#a0 = a0 + a1
add a0,a0,a1;

#a0 output is t1
