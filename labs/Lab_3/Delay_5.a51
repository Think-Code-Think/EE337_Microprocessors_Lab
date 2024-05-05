// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
MOV P1, #01H
ACALL DELAY_5s
MOV P1, #00H
ACALL DELAY_5s
MOV P1, #01H
ACALL DELAY_5s
MOV P1, #00H
HERE: SJMP HERE
ORG 130H
// *****************
DELAY_5s:
push 00h
push 01h
mov r1, #50
h4: mov r0, #100
h3: acall delay_1ms
djnz r0, h3
djnz r1, h4
pop 01h
pop 00h
RET

delay_1ms:
push 00h
mov r0, #4
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
// • To calculate the delay amount, refer the 8051 Instruction Set to find number
//of cycles each instruction runs for and how correct amount delay is achieved.
//• Port 1.0 is initially set to 1. Then the 5 second delay sub-routine is called and
//then Port 1.0 is set to 0.
//• Use Logic Analyzer to check the delay in Port 1.0. Make sure you change the
//default clock frequency to 24MHz (as it is on the Pt-51 board)