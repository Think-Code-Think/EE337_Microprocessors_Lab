// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
ACALL MAC
HERE: SJMP HERE
ORG 130H
// *****************
MAC:
MOV A , 70H
MOV B , 73H
MUL AB
MOV R0 , A
MOV R1 , B
MOV A , 71H
MOV B , 74H
MUL AB
MOV R2 , A
MOV R3 , B
MOV 50H ,#0H
ACALL ADD16
MOV A , 72H
MOV B , 75H
MUL AB
MOV R2 , A
MOV R3 , B
ACALL ADD16
MOV 52H , R0
MOV 51H , R1
RET

ADD16:
MOV A  , R0
ADD A  , R2
MOV R0 , A
MOV A  , R1
ADDC A  , R3
JNC NOCARRY
INC 50H
NOCARRY:
MOV R1 , A
RET
END
	
//[8 points] Multiply and Accumulate (MAC) operation is used extensively in digital
//signal processing and machine learning.
//Consider the inputs to be a1, a2, a3 and the corresponding weights/coefficients to be
//b1, b2, b3. The result after the MAC operation will be
//x = a1b1 + a2b2 + a3b3.
//Write an assembly language program to generate the result x, when a1, a2, a3 are
//three inputs present in the memory locations 70H to 72H and b1, b2, b3 are 8-bit
//weights/coefficients present in the memory locations 73H to 75H.
//Since the result x can be 18 bits long, store the result in memory locations 50H,
//51H, 52H. For x = x17x16x15 . . . x3x2x1x0, the memory location 50H should have
//000000x17x16, the memory location 51H should have the bits x15x14 . . . x8, and the
//memory location 52H should have the bits x7x6 . . . x0.
//Use the following program as a starting point. Use the ADD16 subroutine written in
//the previous question to implement the MAC operation.