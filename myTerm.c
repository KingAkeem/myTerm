#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <menu.h>

static void finish(int sig);
static void autocomplete();

int main() {
  (void) initscr(); // Initalizes variables needed
  (void) cbreak(); // Disables buffering and allows single character capture
  (void) noecho(); // Disables automatic echoing
  refresh(); // Clears screen entirely
  keypad(stdscr, TRUE); // Captures special keystrokes
  char buf[500];
  int i = 0;
  for(;;) {
    char c = getch();
    addch(c);
    if (c == '.') {
      autocomplete();
      i = 0;
      continue;
    }
    buf[i] = c;
    i++;
  }
  finish(0);
}

static void autocomplete() {
  ITEM **i = (ITEM **)calloc(2, sizeof(ITEM*));
  i[0] = new_item("Name", "Desc");
  MENU *m = new_menu((ITEM**)i);
  post_menu(m);
  refresh();
}
static void finish(int sig) {
  endwin();
  exit(0);
}
