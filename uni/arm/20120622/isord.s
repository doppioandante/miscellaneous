.data
.text
.global ISORD
ISORD:
    stmfd sp!, {fp, lr} @ save FP and return address
    mov fp, sp
    stmfd sp!, {r0-r2, r4} @ save registers
    ldr r1, [fp, #12] @ unsigned int M; int r1 = M
    ldr r0, [fp, #8] @ char* V = r0
    mov r3, #0 @ int result = r3
    ldrsb r2, [r0], #1 @ char r2 = *v++;
    sub r1, r1, #1 @ decrement r1 counter

NEXT:
    ldrsb r4, [r0], #1 @ char r4 = *V++
    cmp  r2, r4
    bgt DISORD @ if (r2 > r4) goto DISORD
    mov r2, r4 @ save current element
    subs r1, r1, #1 @ decrement counter
    bne NEXT
    mov r3, #1 @ result = 1

DISORD:
    ldmfd sp!, {r0-r2, r4} @ reload saved registers except result
    ldmfd sp!, {fp, pc}


