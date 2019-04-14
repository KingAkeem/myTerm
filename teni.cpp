#include <curses.h>
#include <signal.h>

#include "console.cpp"
#include "menu.cpp"
#include <vector>
#include <string>

static void exit_editor(int);

using namespace std;

Console main_console = Console();
int main() {
	signal(SIGINT, exit_editor);

	int key_input;
	for (;;) {
		key_input = getch();
		switch (key_input) {
			case '.':
                {
                    addch(key_input);	
                    vector<string> item_names;
                    item_names.push_back("func1");
                    item_names.push_back("func2");
                    vector<string> item_desc;
                    item_desc.push_back("desc1");
                    item_desc.push_back("desc2");
                    Menu menu = Menu(item_names, item_desc);
                    menu.make_selection();	
                }
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

static void exit_editor(int signal) {
	if (signal == SIGINT) {
        main_console.~Console();
		exit(0);
	}
}
