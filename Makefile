myTerm : myTerm.c
	cc myTerm.c -lcurses -lmenu
debug : a.out
	gdb a.out 
a.out : myTerm.c
	cc -g myTerm.c -lcurses -lmenu
