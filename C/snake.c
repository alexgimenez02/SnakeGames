#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 30
#define SNAKE_START_LENGTH 3

typedef enum DIRECTIONS {
	UP,
	DOWN,
	LEFT,
	RIGHT,
}Direction;

typedef struct Snake{
	int x;
	int y;
	struct Snake* next;
}Snake;

typedef struct {
	int x;
	int y;
}Food;

void freeSnake(Snake** snake){
	Snake* current = *snake;
	while (current != NULL){
		Snake* tmp = current;
		current = current->next;
		free(tmp);
		tmp = NULL;
	}
}

void initGame(Snake** snake, Food* food, Direction* direction){
	*snake = (Snake*) malloc(sizeof(Snake));
	(*snake)->x = BOARD_WIDTH / 2;
	(*snake)->y = BOARD_HEIGHT / 2;
	(*snake)->next = NULL;
	
	srand(time(NULL));
	food->x = rand() % (BOARD_WIDTH) + 1;
	food->y = rand() % (BOARD_HEIGHT) + 1;
	
	*direction = RIGHT;
}

void drawGame(Snake* snake, Food food){
	
	clear();
	for(int i = 1; i < BOARD_WIDTH + 1; i++){
		for(int j = 1; j < BOARD_HEIGHT + 1; j++){
			mvprintw(j,i,".");
		}
	}
	attron(COLOR_PAIR(1));
	mvprintw(food.y,food.x,"O");
	attroff(COLOR_PAIR(1));
	Snake* current = snake;
	while (current != NULL){
		attron(COLOR_PAIR(2));
		mvprintw(current->y, current->x, "S");
		attroff(COLOR_PAIR(2));
		current = current->next;
	}
	
	refresh();
}

int checkColision(Snake* snake){
	
	if(snake->x < 1 || snake->x > BOARD_WIDTH || snake->y < 1 || snake->y > BOARD_HEIGHT) return 1;
	
	Snake* current = snake->next;
	int posx = snake->x;
	int posy = snake->y;
	while (current != NULL){
		if(current->x == posx && current->y == posy) return 1;
		current = current->next;
	}
	
	return 0;
}

void updateGame(Snake** snake, Food* food, Direction* direction) {
	int posx = (*snake)->x;
	
	if(food->x == (*snake)->x && food->y == (*snake)->y){
		Snake* newHead = (Snake*) malloc(sizeof(Snake));
		switch(*direction){
            case UP:
                food->y--;
                break;
            case DOWN:
                food->y++;
                break;
            case LEFT:
                food->x--;
                break;
            case RIGHT:
                food->x++;
                break;
        }
		newHead->x = food->x;
		newHead->y = food->y;
		srand(time(NULL));
		Snake* current = newHead;
		food->x = rand() % (BOARD_WIDTH) + 1;
		food->y = rand() % (BOARD_HEIGHT) + 1;
		newHead->next = *snake;
		*snake = newHead;
		int foodOnSnake = 0;
		while(current != NULL){
			if(current->x == food->x && current->y == food->y) {
				foodOnSnake = 1;
			}
			current = current->next;
		}
		while(foodOnSnake == 1){
			current = newHead;
			food->x = rand() % (BOARD_WIDTH) + 1;
			food->y = rand() % (BOARD_HEIGHT) + 1;
			while(current != NULL){
				if(current->x == food->x && current->y == food->y) {
					foodOnSnake = 1;
				}
				current = current->next;
			}
		}		
		
		
	}else {
		int posx = (*snake)->x;
		int posy = (*snake)->y;
		switch(*direction){
            case UP:
                (*snake)->y--;
                break;
            case DOWN:
                (*snake)->y++;
                break;
            case LEFT:
                (*snake)->x--;
                break;
            case RIGHT:
                (*snake)->x++;
                break;
        }
		
		if((*snake)->next != NULL){			
			Snake* current = (*snake)->next;
			while (current != NULL) {
				int tmpPosX = current->x;
				int tmpPosY = current->y;
				current->x = posx;
				current->y = posy;
				posx = tmpPosX;
				posy = tmpPosY;
				current = current->next;
			}
		}
	}
}

int main() {
	initscr();			/* Start curses mode 		  */
	refresh();			/* Print it on to the real screen */
	Snake* snake;
	Food food;
	Direction direction;
	int gameOver = 0;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	initGame(&snake,&food,&direction);
	while (gameOver != 1){
		
		keypad(stdscr, TRUE);
		int key = getch();			/* Wait for user input */
		// Check if the input was an arrow key
		if (key == KEY_UP) {
		// The up arrow key was pressed
			direction = UP;
		} else if (key == KEY_DOWN) {
		// The down arrow key was pressed
			direction = DOWN;
		} else if (key == KEY_LEFT) {
		// The left arrow key was pressed
			direction = LEFT;
		} else if (key == KEY_RIGHT) {
		// The right arrow key was pressed
			direction = RIGHT;
		} else if (key == KEY_BACKSPACE) {
			break;
		}
		updateGame(&snake,&food,&direction);
		gameOver = checkColision(snake);
		drawGame(snake,food);
	}
	freeSnake(&snake);
	char* snake_art[] = {
    "        v     ",
    "       /      ",
    "      XX      ",
    "    XXXXXX    ",
    "  XXXXXXXXXX  ",
    " XXXXXXXXXXXX ",
    "XXXOXXXXXXOXXX",
    "XXXXXXXXXXXXXX",
    };
	attron(COLOR_PAIR(1));
	attroff(COLOR_PAIR(1));
	clear();
	printw("Game Over!\n\n");
	for(int i = 0; i < sizeof(snake_art)/sizeof(snake_art[0]); i++){
		if(i < 2){
			attron(COLOR_PAIR(1));
			printw("%s\n",snake_art[i]);
			attroff(COLOR_PAIR(1));
		}
		else {
			if(i == 6){
				for(int j = 0; j < 14; j++){
					if(snake_art[i][j] == 'O'){
						
						attron(COLOR_PAIR(3));
						printw("%c", snake_art[i][j]);
						attroff(COLOR_PAIR(3));
					}else {
						attron(COLOR_PAIR(2));
						printw("%c", snake_art[i][j]);
						attroff(COLOR_PAIR(2));
					}
				}
				printw("\n");
			}else {
				attron(COLOR_PAIR(2));
				printw("%s\n",snake_art[i]);
				attroff(COLOR_PAIR(2));
			}
		}
	}
	refresh();
	getch();
	endwin();			/* End curses mode		  */
}
