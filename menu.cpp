#include <menu.h> 
#include <curses.h>
#include <vector>
#include <string>
#include <stdio.h>

class Menu {
	int selection;
	ITEM **items;
	std::vector<std::string> *names;
	int item_count;
 	MENU *menu;	
	WINDOW *menu_win;
	public:
		Menu(std::vector<std::string>& item_names, std::vector<std::string>& item_desc) {
			if (item_names.size() != item_desc.size()) {
				perror("Item names and item descriptions are not equal");		
			}	
			names = &item_names;
			item_count = item_names.size();
			items = (ITEM **)calloc(item_names.size(), sizeof(ITEM*));
			for (int i=0; i < item_names.size(); i++) {
				items[i] = new_item(item_names[i].c_str(), item_desc[i].c_str());	
			}
			menu = new_menu(items);
		}

		~Menu(){
			for (int j = 0; j < sizeof(items)/sizeof(items[0]); j++) {
				free_item(items[j]);
			}
			free_menu(menu);
		}

		void show(const char *marker, int y, int x) {
			menu_win = derwin(stdscr, 0, 0, y, x);	
			set_menu_mark(menu, marker);	
			set_menu_sub(menu, menu_win);
			post_menu(menu);
			refresh();
		}

		void make_selection(int y, int x) {
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
						mvprintw(y, x, "%s", names[selection]); 
						return;
				}	
			} while(true); 

		}
};
