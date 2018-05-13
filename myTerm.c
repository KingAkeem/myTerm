#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


static void finish(int sig);
static void translate(const char*);

int main() {
  (void) initscr();
  (void) cbreak(); // Disables buffering and allows single character capture
  (void) noecho(); // Disables automatic echoing
  refresh();
  keypad(stdscr, TRUE); // Captures special keystrokes
  char buf[500];
  int i = 0;
  for(;;) {
    char c = getch();
    addch(c);
    if (c == ' ') {
      translate(buf);
      i = 0;
      continue;
    }
    buf[i] = c;
    i++;
  }
  finish(0);
}
static void translate(const char* word) {
  int ret = strcmp(word, "Hello");
  if (ret) {
    addstr("Bonjour");
    refresh();
  }
}
static void finish(int sig) {
  endwin();
  exit(0);
}
