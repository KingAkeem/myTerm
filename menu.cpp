#include <menu.h> 
#include <curses.h>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

class Menu {
	ITEM **items;
	vector<string> *names;
	int item_count;
 	MENU *menu;	
	WINDOW *menu_win;
	public:
		int x;
		int y;
		Menu(vector<string>& item_names, vector<string>& item_desc) {
			if (item_names.size() != item_desc.size()) {
				perror("Item names and item descriptions are not equal");		
			}	
			names = &item_names;
			item_count = item_names.size();
			items = (ITEM **) calloc(item_count, sizeof(ITEM*));
			for (size_t i=0; i < item_names.size(); i++) {
				items[i] = new_item(item_names[i].c_str(), item_desc[i].c_str());	
			}
			menu = new_menu(items);
			getyx(stdscr, y, x);
		}

		~Menu(){
			for (size_t j = 0; j < sizeof(items)/sizeof(items[0]); j++) {
				free_item(items[j]);
			}
			free_menu(menu);
		}

		void show(const char *marker) {
			menu_win = derwin(stdscr, 0, 0, y, x);	
			set_menu_mark(menu, marker);	
			set_menu_sub(menu, menu_win);
			post_menu(menu);
			refresh();
		}

		void make_selection() {
			int selection;
			menu_driver(menu, REQ_DOWN_ITEM);
			refresh();
			do {
				switch(getch()) {
					case '\t':
						if (selection < this->item_count) {
							menu_driver(this->menu, REQ_DOWN_ITEM);	
							selection++;
						} else {
							menu_driver(this->menu, REQ_UP_ITEM);	
							selection = 0;
						}	
						refresh();
						break;
					case '\n':
					case KEY_ENTER:
						unpost_menu(menu);	
						mvprintw(this->y, this->x, "%s", names[selection]); 
						return;
				}	
			} while(true); 

		}
};
