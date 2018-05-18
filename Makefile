UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	DEBUGGER = gdb
endif
ifeq ($(UNAME_S),Darwin)
	DEBUGGER = lldb
endif

teni : teni.c
	cc -o teni teni.c -lcurses -lmenu
debug : teni 
	$(DEBUGGER) teni 
a.out : teni.c
	cc -o teni -g teni.c -lcurses -lmenu

