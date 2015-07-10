.text
.global ISSIM
ISSIM:
    stmfd sp!, {fp, lr}
    mov fp, sp
    stmfd sp!, {r1-r7} @ save registers

    bic r0, r0, #0xFF
    ldr r1, [fp, #8] @ unsigned int N (matrix size)
    ldr r2, [fp, #12] @ int* M
    mov r3, #0 @ row index: int i

RIGA:
    cmp r3, r1
    beq SIM
    add r4, r3, #1 @ int j = i+1;
    cmp r4, r1
    beq SIM

COLONNA:
    mul r5, r3, r1
    add r5, r5, r4
    ldr r6, [r2, r5, ASL #2]
    mul r5, r4, r1
    add r5, r5, r3
    ldr r7, [r2, r5, ASL #2]
    cmp r6, r7
    bne NOSIM
SUCC:
    add r4, r4, #1
    cmp r4, r1
    blt COLONNA
    add r3, r3, #1
    b   RIGA

SIM:
    orr r0, r0, #1
NOSIM:
    ldmfd sp!, {r1-r7}
    ldmfd sp!, {fp, pc}
