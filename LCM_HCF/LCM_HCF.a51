ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:
MOV 50H , #0FH
MOV 51H , #0CH
ACALL ABC
ACALL HERE
ORG 180H
HERE : SJMP HERE

ORG 130H
ABC:
MOV A , 50H
MOV B , 51H
MUL AB
MOV R4 , A
ACALL XYZ
MOV B , 52H
MOV A , R4
DIV AB
MOV 53H , A
RET

XYZ:
MOV A , 50H
MOV B , 51H
S: SUBB A , B
JC HERE1
JZ HERE2
MOV R2 , B 
CJNE R2 , #00H , S
JMP ENDING
HERE1:
CPL A
INC A
HERE2:
XRL A , B
XRL B , A
XRL A , B
MOV R2 , B
CJNE R2 , #00H , S
JMP ENDING
ENDING:
MOV 52H , A
RET

END

