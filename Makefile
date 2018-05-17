UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	DEBUGGER = gdb
endif
ifeq ($(UNAME_S),Darwin)
	DEBUGGER = lldb
endif

myTerm : myTerm.c
	cc -o myTerm myTerm.c -lcurses -lmenu
debug : myTerm 
	$(DEBUGGER) myTerm 
a.out : myTerm.c
	cc -o myTerm -g myTerm.c -lcurses -lmenu

