.text
.global _start
.extern ISORD
_start:
    ldr sp, =STACK
    mov r0, #10
    stmfd sp!, {r0}
    ldr r0, =VEC
    stmfd sp!, {r0}
    bl ISORD
    ldr r8, =OUT
    strb r3, [r8]

LOOP:
    B LOOP

.data
VEC: .byte 3, 2, 3, 4, 5, 6, 7, 8, 9, 10
     .align 4

.bss
OUT: .space 1
     .align 4

     .space 4096
STACK: .space 4



