#include <string.h>
#include <menu.h>
#include <curses.h>
#include <stdlib.h>

#define GET_CUR_POS int x, y; getyx(stdscr, y, x)

static void finish(int sig);
static void autocomplete();

int main() {
  (void) initscr(); // Initalizes variables needed
  (void) cbreak(); // Disables buffering and allows single character capture
  (void) noecho(); // Disables automatic echoing
  refresh(); // Clears screen entirely
  keypad(stdscr, TRUE); // Captures special keystrokes

  char *word = calloc(500, 1);
  int i = 0;
  char c;
  for(;;) {
	// Capturing user input and displaying it
    c = getch();
	switch(c) {
	// If user input a period then we look to autocomplete
		case '.':
	  		addch(c);
		  	refresh();
		  	autocomplete();
		  	addch(' ');
		  	refresh();
		  	continue; // No need to go through rest of loop
			break; 

		default:	
			addch(c);	
			refresh();
	}
   word[i] = c;
   i++;
  }
}

static void autocomplete() {
  GET_CUR_POS; 
  ITEM **i = (ITEM **)calloc(2, sizeof(ITEM*));
  i[0] = new_item("Name", "Desc");
  MENU *m = new_menu((ITEM**)i);
  set_menu_sub(m, derwin(stdscr, 0, 0, y, x));
  post_menu(m);
  refresh();
  move(y, x+1);
}

static void finish(int sig) {
  endwin();
  exit(0);
}
