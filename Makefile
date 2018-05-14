UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	DEBUGGER = gdb
endif
ifeq ($(UNAME_S),Darwin)
	DEBUGGER = lldb
endif

myTerm : myTerm.c
	cc myTerm.c -lcurses -lmenu
debug : a.out
	$(DEBUGGER) a.out
a.out : myTerm.c
	cc -g myTerm.c -lcurses -lmenu
