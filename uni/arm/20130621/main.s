.text
.global _start
.extern ISSIM
_start:
    ldr sp, =STACK
    ldr r0, =M
    stmfd sp!, {r0}
    mov r0, #3
    stmfd sp!, {r0}
    bl ISSIM
    add sp, #8
    ldr r8, =OUT
    strb r0, [r8]
LOOP: b LOOP

.data
M: .long 0, 1, 2, 1, 0, 3, 2, 3, 1
   .align

.bss
OUT: .space 1
     .align 4

     .space 4096
STACK: .space 4
