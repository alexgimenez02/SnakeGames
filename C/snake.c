#include <ncurses.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 20
#define SNAKE_START_LENGTH 3

typedef struct {
  int x;
  int y;
} Point;

int main() {
	initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
}
