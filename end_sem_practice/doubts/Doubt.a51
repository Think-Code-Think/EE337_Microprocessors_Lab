ORG 0H
LJMP MAIN
ORG 100H
MAIN:
MOV TMOD , #01H
MOV TH0 , #00H
MOV TL0 , #0FEH
SETB TR0
READT0:
MOV A , TH0
MOV R0 , TL0
CJNE A , TH0 , READT0
CHECK:
JNB TF0 ,CHECK
CLR TR0
CLR TF0
END