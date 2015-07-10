.text
ISRDOUT:
    stmfd sp!, {r0, r1, lr}
    bl GETQUE
    adds r1, r0, #1
    beq VUOTO
    ldr r1, [r0], #4
    stmfd sp!, {r1}
    stmfd sp!, {r0}
    bl STARTDMA
EXIT:
    ldmfd sp!, {r0, r1, lr}
    sub pc, lr, #4
VUOTO:
    ldr r0, =EMPTY
    mov r1, #1
    strb r1, [r0]
    b EXIT

