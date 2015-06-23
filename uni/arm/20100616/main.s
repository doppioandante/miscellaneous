.data
NUMEL: .long 16
STR: .ascii "ABCdEfGHhgfzDcba"

.bss
.align 4
TOTC: .word

.align 4
.space 1024
stack: .space 4

.text
.global _start
.extern COUP
_start:
  ldr sp, =stack
  ldr r0, =STR
  stmfd sp!, {r0}
  ldr r0, =NUMEL
  ldr r0, [r0] @ r0 = NUMEL
  stmfd sp!, {r0}
  ldr r0, =TOTC
  stmfd sp!, {r0}
  bl COUP
  add sp, sp, #12
  ldr r0, =TOTC
  ldr r0, [r0]

FINE: b FINE

COUP:
  stmfd sp!, {fp, lr}
  mov fp, sp
  sub sp, #24
  stmdb fp, {r1-r6}
  ldr r1, [FP, #16] @ V
  ldr r3, [FP, #12] @ SIZ
  add r2, r1, r3
  sub r2, r2, #1 @ r2 = V + SIZ - 1, last character
  mov r3, r3, LSR #1 @ r3 = SIZ/2 = k
  mov r4, #0 @ TOTC = 0

LOOP:
  ldrb r5, [r1], #4 @ V[i++] = r5
  ldrb r6, [r2], #-4 @ ...
  sub r6, r6, #0x20 @ to uppercase
  cmp r5, r6
  addeq r4, r4, #1
  sub r3, r3, #1
  bne LOOP

  ldr r2, [FP, #8]
  strh r4, [r2]
  ldmia fp, {r1-r6}
  mov sp, fp
  ldmfd sp!, {fp, pc}
