ORG 0H
LJMP MAIN
ORG 100H
MAIN:
LCALL SQUARE_PULSE
LCALL SQUARE_PULSE
LCALL SQUARE_PULSE
HERE: SJMP HERE


SQUARE_PULSE:
CLR P1.0
LCALL delay_1_5ms
SETB P1.0
LCALL delay_1_5ms
RET



delay_1_5ms:
push 00h
mov r0, #6
h2: acall delay_250us
djnz r0, h2
pop 00h
ret

delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret



END