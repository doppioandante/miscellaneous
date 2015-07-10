.text
.global _start
_start:
    ldr sp, =STACK
    ldr r0, =V
    stmfd sp!, {r0}
    ldr r0, =W
    stmfd sp!, {r0}
    mov r0, #10
    stmfd sp!, {r0}
    ldr r0, =R
    stmfd sp!, {r0}
    ldr r0, =O
    stmfd sp!, {r0}
    bl PRO
    add sp, sp, #20

LOOP: b LOOP

.data
V: .short 1, -2, 5, 4, 3, -6, 1, 2, 3, 10
   .align 4
W: .short 1, -2, 5, 4, 3, -6, 0, 0, 0, 0
   .align 4

.bss
O: .space 2
   .align 4
R: .space 4

   .space 4096
STACK: .space 4
