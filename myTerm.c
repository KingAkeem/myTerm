#include <string.h>
#include <menu.h>
#include <curses.h>
#include <stdlib.h>

#define GET_CUR_POS int x, y; getyx(stdscr, y, x)

static void auto_cmpl();
static void scroll_menu(MENU*, char);
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
		  	auto_cmpl();
		  	addch(' ');
		  	refresh();
		  	continue; // No need to go through rest of loop break; 
		default:	
			addch(c);	
			refresh();
	}
   word[i] = c;
   i++;
  }
}

static void scroll_menu(MENU *m, char c) {
	if (c == '\t') {
		menu_driver(m, REQ_DOWN_ITEM);	
		refresh();
		getch();
	}
}

static void auto_cmpl() {
  GET_CUR_POS; 
  ITEM **i = (ITEM **)calloc(2, sizeof(ITEM*));
  i[0] = new_item("first item", "Desc");
  i[1] = new_item("second item", "Desc");
  MENU *m = new_menu((ITEM**)i);
  set_menu_sub(m, derwin(stdscr, 0, 0, y, x));
  post_menu(m);
  refresh();
  char c = getch();
  if (c=='\t') {
	  scroll_menu(m, c);
  } 
  unpost_menu(m);
  free_item(i[0]);
  free_menu(m);
  move(y, x+1);
}

