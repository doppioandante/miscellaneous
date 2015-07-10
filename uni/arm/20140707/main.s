.text
_start:
    ldr sp, =STACK
    ldr r2, =EMPTY
    ldrb r3, [r2]
    
TEST:
    cmp r3, #1
    bne TEST

NEXTAREA:
    bl GETAREA
    bl PUTQUE
    adds r1, r0, #1
    beq TEST
    cmp r3, #1
    bne NEXTAREA
    mov r3, #0
    strb r3, [r2]
    bl GETQUE
    ldr r1, [r0], #4
    stmfd sp!, {r1}
    stmfd sp!, {r0}
    bl STARTDMA
    b NEXTAREA

.data
XIN: .short 0
XOUT: .short 0
EMPTY: .byte 1
       .align

.bss
QUE: .space 2048

    .space 4096
STACK: .space 4

