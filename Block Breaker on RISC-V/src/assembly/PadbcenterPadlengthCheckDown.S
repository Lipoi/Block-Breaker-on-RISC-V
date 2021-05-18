.section .text
.globl PadbcenterPadlengthCheckDown
.type PadbcenterPadlengthCheckDown, @function
PadbcenterPadlengthCheckDown:

#a0 is padbcenter
#a1 is padlength

#t0 = padbcenter[1]
lw t0, 4(a0) 

#t1 = 0
mv t1,x0

#t1 = t1 + a1
add t1,t1,a1;

#a0 output is t1
mv a0, t1