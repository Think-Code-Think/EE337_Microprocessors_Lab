// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL ADD16
HERE: SJMP HERE
ORG 130H
// *****************
ADD16:
// ADD YOUR CODE HERE
MOV R0, #00H
MOV R1, 70H
MOV R2, 71H
MOV R3, #00H
MOV R4, 72H
MOV R5, 73H
MOV A, R2
ADD A, R5
MOV R2, A
MOV A, R1
JNC NOTCARRY1
ADD A, #01H
JNC NOTCARRY1
MOV R1, A
MOV A, R0
ADD A, #01H
ADD A, R3
MOV R0, A
MOV A, R1
ADD A, R4
MOV R1, A
LJMP EOP
NOTCARRY1: ADD A, R4
MOV R1, A
MOV A, R0
JNC NOTCARRY2
ADD A, #01H
NOTCARRY2: ADD A, R3
MOV R0, A
EOP: MOV 74H, R0
MOV 75H, R1
MOV 76H, R2
RET
END