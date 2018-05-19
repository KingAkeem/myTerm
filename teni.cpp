#include <curses.h>
#include <signal.h>

#include "console.cpp"
#include "menu.cpp"
#include <vector>
#include <string>

static void exit_editor(int);

int main() {
	signal(SIGINT, exit_editor);
	Console main_console = Console();

	int key_input;
	for (;;) {
		key_input = getch();
		switch (key_input) {
			case '.':
				addch(key_input);	
				std::vector<std::string> item_names = ["func1", "func2"];
				std::vector<std::string> item_desc = ["desc1", "desc2"];
				Menu menu = Menu(item_names, item_desc);
				menu.make_selection();	
				continue;	
				break;
			case 127:
			case 8:
			case KEY_BACKSPACE:
				main_console.delete_char();
				break;
		}
	}
}

static void exit_editor(Console& win, int signal) {
	if (signal == SIGINT) {
		endwin();
		exit(0);
	}
}
