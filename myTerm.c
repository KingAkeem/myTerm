#include <string.h>
#include <menu.h>
#include <curses.h>
#include <stdlib.h>

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
    char c = getch();
	refresh();
    addch(c);
	// If user input a period then we look to autocomplete
    if (c == '.') {
	  int x, y;
  	  getyx(stdscr, y, x);	  
      autocomplete(x, y);
	  addch(' ');
      continue; // No need to go through rest of loop
    }
   word[i] = c;
   i++;
  }
}

static void autocomplete(const size_t x, const size_t y) {
  ITEM **i = (ITEM **)calloc(2, sizeof(ITEM*));
  i[0] = new_item("Name", "Desc");
  MENU *m = new_menu((ITEM**)i);
  WINDOW *men_win = derwin(stdscr, 0, 0, x, y);
  set_menu_sub(m, men_win);
  post_menu(m);
  refresh();
  free_item(i[0]);
  free_menu(m); 
  unpost_menu(m);
  delwin(men_win);
}

static void finish(int sig) {
  endwin();
  exit(0);
}
