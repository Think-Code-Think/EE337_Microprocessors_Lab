// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL XORSWAP
HERE: SJMP HERE
ORG 130H
// *****************
XORSWAP:
CLR A
XRL A , 60H
XRL A , 61H
XRL 61H , A //61h has a
XRL 60H , A //60h has b
RET
END
// The inputs a and b are stored at locations 60H and 61H respectively.
// After the swap operation, location 60H must contain the value of b and location
// 61H must contain the value of a.
