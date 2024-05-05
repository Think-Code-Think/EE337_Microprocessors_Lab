ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:
ACALL ADD16
HERE: SJMP HERE
ORG 130H
// *****************
ADD16:
MOV 74H ,#0H
MOV R0 , 71H
MOV R1 , 70H
MOV R2 , 73H
MOV R3 , 72H
MOV A  , R0
ADD A  , R2
MOV 76H , A
MOV A  , R1
ADDC A  , R3
JNC NOCARRY
INC 74H
NOCARRY:
MOV 75H , A
RET
END
// The first number x is stored at locations 70H and 71H, with its most significant
// byte (MSB) in 70H and the least significant byte in 71H.
// The second number y is similarly stored at locations 72H (MSB) and 73H (LSB).
// Since the result z = x + y can be 17 bits long, store the result in memory
//locations 74H, 75H, 76H.
// For z = z16z15z14 . . . z3z2z1z0 where z0 is the least significant bit (LSB) and
//z16 is the most significant bit (MSB), the memory location 74H should have
// 0000000z16, the memory location 75H should have the bits z15z14 . . . z8, and the
// memory location 76H should have the bits z7z6 . . . z0.
