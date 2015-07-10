.text
NIL = 0
LIST1:
    stmfd sp!, {r0, r1, r3}
    ldr r3, =0xFFFF0000
    bic r1, r1, r3
    bic r2, r2, #0xFF
CERCA:
    ldr r0, [r0]
    cmp r0, #NIL
    beq FINE

    ldrh r3, [r0, #4]
    cmp r3, r1
    bne CERCA

    ldr r3, [r0, #8]
    addmis r3, r3, #1
    blo FINE

    ldrsh r3, [r0, #6]
    add r3, r3, #1
    strh r3, [r0, #6]
    orr r2, r2, #255
FINE:
    ldmfd sp!, {r0, r1, r3}
    mov pc, lr



