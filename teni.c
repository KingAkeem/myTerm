#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void exit_editor(int);
static void auto_complete(int, int);
static int scroll_menu(MENU*, ITEM**, int);

int main() {
	signal(SIGINT, exit_editor);
	(void) initscr(); // Initalizes variables needed
	(void) noecho(); // Disables automatic echoing
	(void) cbreak(); // Allowws single character buffering
	refresh(); // Clears screen entirely
	keypad(stdscr, TRUE); // Captures special keystrokes


	int c;
	int y;
	int x;
	for(;;) {
		// Capturing user input and displaying it
		c = getch();
		switch(c) {
		// If user input a period then we look to autocomplete
		case '.':
			addch(c);
			getyx(stdscr, y, x);
			auto_complete(y, x);
			continue; // No need to go through rest of loop
		case 127:
		case 8:
		case KEY_BACKSPACE:
			delch();
			getyx(stdscr, y, x);
			if (x == 0) {
				deleteln();
				move(y-1, x);
			} else {
			mvdelch(y, x-1);
			}
			refresh();
			break;
		case 27:
		   endwin();
		   exit(0);
		default:
			addch(c);
			refresh();
		}
	}
}

void exit_editor(int signo) {
	if (signo == SIGINT) {
		endwin();
		exit(0);
	}
}

static int scroll_menu(MENU *menu, ITEM** items, int length) {
	int count = 0;
	int choice = '\t';
	do {
		switch (choice) {
			case '\t':
				if (count < length-1) {
					menu_driver(menu, REQ_DOWN_ITEM);
					count++;
				}
				else {
					menu_driver(menu, REQ_UP_ITEM);
					count = 0;
				}
				refresh();
				break;
			case '\n':
			case KEY_ENTER:
				return count;
		}
		choice = getch();
	} while(true);
}

static void auto_complete(int y, int x) {
	// Creating items
	ITEM **items = (ITEM **)calloc(2, sizeof(ITEM*));
	items[0] = new_item("func1()", "Desc");
	items[1] = new_item("func2()", "Desc");
	const char *item_names[2];
	item_names[0] = "func1()";
	item_names[1] = "func2()";
	// Creating menu
	MENU *auto_menu = new_menu(items);
	// Creating window for menu and accepting special keys
	WINDOW *menu_window = derwin(stdscr, 0, 0, y, x);
	keypad(menu_window, TRUE);
	// Setting up menu and posting menu
	set_menu_mark(auto_menu, "*");
	set_menu_sub(auto_menu, menu_window);
	post_menu(auto_menu);
	refresh();
	int selection;
	if (getch()=='\t') { 
		menu_driver(auto_menu, REQ_DOWN_ITEM);
		refresh();
		selection = scroll_menu(auto_menu, items, 2);
	}
	unpost_menu(auto_menu);
	mvprintw(y, x, "%s", item_names[selection]);
	// Free menu and item memory
	for (int j = 0; j < sizeof(items)/sizeof(items[0]); j++) {
		free_item(items[j]);
	}
	free_menu(auto_menu);
}
