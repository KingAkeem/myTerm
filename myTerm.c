#include <string.h>
#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>


#define GET_CUR_POS int x, y; getyx(stdscr, y, x)
#define MAX_WORD_SIZE 500

static void auto_cmpl();
static void scroll_menu(MENU*, char);

int main(int argc, const char* argv[]) {

	(void) initscr(); // Initalizes variables needed
	(void) noecho(); // Disables automatic echoing
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
			refresh();
			auto_cmpl();
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

static void scroll_menu(MENU *menu, char c) {
	do {
		switch (c) {
			case '\t':
				menu_driver(menu, REQ_DOWN_ITEM);	
				refresh();
				c = getch();
				break;
		} 
	} while (c == '\t');
}

static void auto_cmpl() {
	GET_CUR_POS;
	ITEM **items = (ITEM **)calloc(2, sizeof(ITEM*));
	items[0] = new_item("first item", "Desc");
	items[1] = new_item("second item", "Desc");
	MENU *auto_menu = new_menu((ITEM**)items);
	set_menu_sub(auto_menu, derwin(stdscr, 0, 0, y, x));
	post_menu(auto_menu);
	refresh();
	char c  = getch();
	if (c=='\t') {
		scroll_menu(auto_menu, c);
	}
	for (int j = 0; j < sizeof(items)/sizeof(items[0]); j++) {
		free_item(items[j]);
	}
	free_menu(auto_menu);
	unpost_menu(auto_menu);
}
