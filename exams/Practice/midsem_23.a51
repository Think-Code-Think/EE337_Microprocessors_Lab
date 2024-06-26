ORG 0H
LJMP MAIN
ORG 100H

MAIN:
LCALL PRIVATE_KEY_INIT
LCALL KEY_D
LCALL LED_DISP
LCALL DECRPYT_INIT
LCALL EXPO
LCALL KEY_M
HERE: SJMP HERE


PRIVATE_KEY_INIT:
MOV 73H , #19
MOV 74H , #13
MOV A , 73H
CLR  C
SUBB A , #1
MOV R0 , A
CLR C
MOV A , 74H
SUBB A , #1
MOV R1 , A
CLR C
MOV A , R0
MOV B , R1
MUL AB
MOV 70H , A
MOV 71H , #173
RET

DECRPYT_INIT:
MOV 73H , #19
MOV 74H , #13
MOV A , 73H
MOV B , 74H
MUL AB 
MOV 70H , A
MOV P1 , #0FH
MOV 71H , P1
MOV 71H , #6
RET

KEY_M:
MOV R2 , 69H
MOV R3 , 68H
MOV R1 , #0
DIVIDE_M:	CLR C
        MOV A , R2 
		SUBB A , 70H
		MOV R2 , A
		MOV A , R3
		SUBB A , #0
		MOV R3 , A
		INC R1
		CJNE R3 , #0 , DIVIDE_M
		CJNE R2 , #0 , FORWARD_M
		RET
FORWARD_M:MOV A , R2
		CLR C
		SUBB A , 70H
		JNC DIVIDE_M
		MOV 73H , R2
RET



RET


EXPO:
MOV R0 , 72H; D
MOV R1 , 71H; C
MOV R2 , #0  ; UPPER BYTE
MOV R3 , 71H  ; LOWER BYTE
EXPO_LOOP:MOV A , R1
		  MOV B , R3
		  MUL AB
		  MOV R4 , B
		  MOV R3 , A
		  MOV A , R1
		  MOV B , R2
		  MUL AB
		  ADD A , R4
		  MOV R2 , A
		  DJNZ R0 , EXPO_LOOP
		  MOV 68H , R2 ;upper
		  MOV 69H , R3 ;lower
RET


KEY_D:
MOV R0 , #1
LOOP:	MOV R1 , #0 ; R1 IS MY QUOTIENT
		MOV A , 70H ;
		MOV B , R0
		MUL AB
		ADD A , #1
		MOV R2 , A ; LOWER BYTE
		MOV A , B
		ADDC A , #0
		MOV R3 , A ; UPPER BYTE
DIVIDE:	CLR C
        MOV A , R2 
		SUBB A , 71H
		MOV R2 , A
		MOV A , R3
		SUBB A , #0
		MOV R3 , A
		INC R1
		CJNE R3 , #0 , DIVIDE
		CJNE R2 , #0 , FORWARD
		MOV 72H , R1
		RET
FORWARD:MOV A , R2
		CLR C
		SUBB A , 71H
		JNC DIVIDE
		INC R0
		CJNE R0 , #255 , LOOP 
RET

LED_DISP:
MOV A , 72H
MOV P1 , A 
LCALL DELAY_5s
MOV P1, #00H
LCALL DELAY_1s
RL A
RL A
RL A
RL A
MOV P1 , A 
LCALL DELAY_5s
MOV P1, #00H
LCALL DELAY_1s
RET

DELAY_5s:
push 00h
push 01h
mov r1, #50
h5: mov r0, #100
h6: acall delay_1ms
djnz r0, h6
djnz r1, h5
pop 01h
pop 00h
RET

DELAY_1s:
push 00h
push 01h
mov r1, #10
h3: mov r0, #100
h4: acall delay_1ms
djnz r0, h4
djnz r1, h3
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