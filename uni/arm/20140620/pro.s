.text
.global PRO
PRO:
    stmfd sp!, {fp, lr}
    mov fp, sp
    stmfd sp!, {r0-r7}

    mov r0, #0 @ unsigned short max = 0
    mov r6, #0 @ int o = 0
    ldr r1, [fp, #24] @ unsigned short* V
    ldr r2, [fp, #20] @ unsigned short* W
    ldr r3, [fp, #16] @ unsigned int N
LOOP:
    ldrh r4, [r2], #2 @ r4 = W[i]
    ldrh r5, [r1], #2 @ r5 = V[i]
    mul r7, r4, r5 @ r7 = W[i] * V[i]
    bhi LOWER @ no unsigned overflow ?
    add r6, r6, #1

LOWER:
    cmp r7, r0 @ W[i]*V[i] > MAX ?
    movgt r0, r7
    subs r3, r3, #1
    bne LOOP

    ldr r1, [fp, #8]
    strh r6, [r1] @ *OVER = o

    ldr r1, [fp, #16]
    str r0, [r1]

    ldmfd sp!, {r0-r7}
    ldmfd sp!, {fp, pc}



