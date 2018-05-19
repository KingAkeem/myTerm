#include <curses.h>
#include <menu.h>

class Console {
	int x;
	int y;
	public:
		WINDOW *main_window;
		Console() {
			(void) initscr(); // Initalizes needed variables
			(void) noecho(); // Disables automatic echoing of typed characters
			(void) cbreak(); // Allows single character buffering
			main_window = stdscr;		
			keypad(main_window, TRUE);
			refresh();
		}	

		~Console() {
			endwin();
		}

		void delete_char() {
			if (this->row() == 0) {
				deleteln();
				move(this->y-1, this->x);	
			} else {
				mvdelch(this->y, this->x-1);	
			}	
			refresh();
		}
		
		constexpr int column() {
			getyx(this->main_window, y, x);	
			return y;
		}

		constexpr int row() {
			getyx(this->main_window, y, x);
			return x;	
		}

};
