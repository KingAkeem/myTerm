#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


#define GET_CUR_POS int x, y; getyx(stdscr, y, x)
#define MAX_WORD_SIZE 500

void exit_editor(int);
static void auto_complete();
static int scroll_menu(MENU*, int, int);

int main(int argc, const char* argv[]) {
	signal(SIGINT, exit_editor);
	(void) initscr(); // Initalizes variables needed
	(void) noecho(); // Disables automatic echoing
	(void) cbreak(); // Allowws single character buffering
	refresh(); // Clears screen entirely
	keypad(stdscr, TRUE); // Captures special keystrokes

	char *word = calloc(MAX_WORD_SIZE, 1);
	int i = 0;
	char c;
	for(;;) {
		// Capturing user input and displaying it
		c = getch();
		switch(c) {
		// If user input a period then we look to autocomplete
		case '.':
			addch(c);
			auto_complete();
			refresh();
			continue; // No need to go through rest of loop break;
		default:
			addch(c);
			refresh();
		}
		if (sizeof(word) == MAX_WORD_SIZE) {
			word = calloc(MAX_WORD_SIZE, 1);
		}
		word[i] = c;
		i++;
	}
}

void exit_editor(int signo) {
	if (signo == SIGINT) {
		endwin();
		exit(0);
	}
}

static int scroll_menu(MENU *menu, int choice, int length) {
	int count = 0;
	for(;;) {
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
				return choice;
		}
		choice = getch();
	}
}

static void auto_complete() {
	GET_CUR_POS;
	ITEM **items = (ITEM **)calloc(2, sizeof(ITEM*));
	items[0] = new_item("first item", "Desc");
	items[1] = new_item("second item", "Desc");
	MENU *auto_menu = new_menu(items);
	WINDOW *menu_window = derwin(stdscr, 0, 0, y, x);
	set_menu_sub(auto_menu, menu_window);
	post_menu(auto_menu);
	refresh();
	char next_char = getch();
	int choice;
	if (next_char=='\t') {
		choice = scroll_menu(auto_menu, next_char, 2);
		addch(choice);
		refresh();
	}
	refresh();
	for (int j = 0; j < sizeof(items)/sizeof(items[0]); j++) {
		free_item(items[j]);
	}
	free_menu(auto_menu);
	free(items);
	delwin(menu_window);
	unpost_menu(auto_menu);
}
