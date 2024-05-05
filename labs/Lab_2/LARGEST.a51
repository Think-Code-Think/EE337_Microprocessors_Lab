// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL MAX
HERE: SJMP HERE
ORG 130H
// *****************
MAX:
MOV R0 , #60H
MOV R1 , #07H
MOV B , @R0
LOOP: 
INC R0
MOV A , B
SUBB A , @R0
JNC SETMAX
MOV B , @R0
SETMAX:
DJNZ R1 , LOOP
MOV 70H , B
RET
END
//• The input numbers must be stored in memory locations 60H to 67H.
//• The result (largest value) must be stored in memory location 70H.
//• To reduce the effort involved in adding multiple items in memory locations, you
//can use the command window in Keil.
//– Start a Keil debugging session.
//– Enter the following command in the Keil command window to load an array of 8 numbers represented in decimal format. The I:60h refers to indirect
// addressing of location 60H. To inspect the memory, you should enter I:0x60
// in the Keil memory window.
// E char I:60h = 14h,69h,26h,5bh,7fh,1ah,00h,0c5