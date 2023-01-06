#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

int BOARD_WIDTH = 30;
int BOARD_HEIGHT = 20;
int score = 0;
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
	food->y = rand() % (BOARD_HEIGHT - 1) + 2;
	
	*direction = RIGHT;
}

void drawGame(Snake* snake, Food food){
	
	clear();
	mvprintw(0,(BOARD_WIDTH + 2) / 2, "Score: %d", score);
	for(int i = 0; i < BOARD_WIDTH + 2; i++){
		for(int j = 1; j < BOARD_HEIGHT + 2; j++){
			if((i == 0 && j >= 1) || (i == BOARD_WIDTH + 1 && j < BOARD_HEIGHT + 2)){
				mvprintw(j,i,"|");				
			}else if((i > 0 && j == 1) || ((i > 0 && i < BOARD_WIDTH) && j == BOARD_HEIGHT + 1)){
				mvprintw(j,i,"-");				
			}
		}
	}
	attron(COLOR_PAIR(1));
	mvprintw(food.y,food.x,"O");
	attroff(COLOR_PAIR(1));
	Snake* current = snake;
	int i = 1;
	while (current != NULL){
		if (i == 1) attron(A_BOLD);
		attron(COLOR_PAIR(2));
		mvprintw(current->y, current->x, "S");
		if(i== 1) attroff(A_BOLD);
		attroff(COLOR_PAIR(2));
		current = current->next;
		i++;
	}
	
	refresh();
}

int checkColision(Snake* snake){
	
	if(snake->x < 1 || snake->x > BOARD_WIDTH || snake->y < 2 || snake->y > BOARD_HEIGHT) return 1;
	
	Snake* current = snake->next;
	int posx = snake->x;
	int posy = snake->y;
	while (current != NULL){
		if(current->x == posx && current->y == posy) return 1;
		current = current->next;
	}
	
	return 0;
}

int saveHighScore(int sc){
	int highScore = 0;
	printw("Final score: ");
	attron(COLOR_PAIR(3));
	printw("%d\n",sc);
	attroff(COLOR_PAIR(3));
	FILE *fptr;
	fptr = fopen("highscore.txt","w+");
	if(fptr == NULL){
		printw("Error reading previous high score file");
		fclose(fptr);
		return 1;
	}
	int ret = fscanf(fptr, "%i", &highScore);
	printw("Number of integers read: %d\n", ret);
	if (ret == 1){		
		if(highScore >= score ){
			printw("Previous high score: ");
			attron(COLOR_PAIR(3));
			printw("%d",highScore);
			attroff(COLOR_PAIR(3));
			printw("\n");
			fprintf(fptr, "%d", highScore);
		}else {
			attron(COLOR_PAIR(4));
			attron(A_BLINK);
			attron(A_UNDERLINE);
			printw("New high score!");
			attroff(A_UNDERLINE);
			attroff(A_BLINK);
			attroff(COLOR_PAIR(4));
			fprintf(fptr, "%d", sc);
		}
	}else {
		printw("Error reading previous high score file");
	}
	fclose(fptr);
	return 0;
}

void updateGame(Snake** snake, Food* food, Direction* direction) {
	int posx = (*snake)->x;
	
	if(food->x == (*snake)->x && food->y == (*snake)->y){
		score++;
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
		food->y = rand() % (BOARD_HEIGHT - 1) + 2;
		newHead->next = *snake;
		*snake = newHead;
		int foodOnSnake = 0;
		while(current != NULL){
			if(current->x == food->x && current->y == food->y) {
				foodOnSnake = 1;
			}
			current = current->next;
		}
		int attemps = 0;
		while(foodOnSnake == 1){
			if(attemps == 10){
				clear();
				printw("You win!");
				saveHighScore(score);
				refresh();
				break;
			}
			current = newHead;
			food->x = rand() % (BOARD_WIDTH) + 1;
			food->y = rand() % (BOARD_HEIGHT - 1) + 2;
			foodOnSnake = 0;
			while(current != NULL){
				if(current->x == food->x && current->y == food->y) {
					foodOnSnake = 1;
				}
				current = current->next;
			}
			attemps++;
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

void changeBoardSize(){
	int selectedItem = 1;
	while (true){
		clear();
		printw("Select the size:\n");
		printw(" 30x20\n");
		printw(" 40x30\n");
		printw(" 50x50\n");
		
		mvprintw(selectedItem, 0, ">");
		int key = getch();
		if (key == KEY_UP) {
		// The up arrow key was pressed
			selectedItem--;
			if (selectedItem < 1) {
			  selectedItem = 3;
			}
		} else if (key == KEY_DOWN) {
		// The down arrow key was pressed
			selectedItem++;
			if (selectedItem > 3) {
			  selectedItem = 1;
			}
		}else if (key == '\n'){
			if(selectedItem == 1){
				BOARD_WIDTH = 30;
				BOARD_HEIGHT = 20;
			}else if (selectedItem == 2){
				BOARD_WIDTH = 40;
				BOARD_HEIGHT = 30;
			}else{
				BOARD_WIDTH = 50;
				BOARD_HEIGHT = 50;			
			}
			break;
		}
		refresh();
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
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	int menu_selection = 1;
	int startGame = 0;
	keypad(stdscr, TRUE);
	system("setterm -cursor off");
	while(startGame == 0){
		clear();
		printw("Welcome to Snake!\n");
		printw(" 1. Start game\n");
		printw(" 2. Change board size\n");
		printw(" 3. Quit\n");
		
		mvprintw(menu_selection, 0, ">");
		int key = getch();
		if (key == KEY_UP) {
		// The up arrow key was pressed
			menu_selection--;
			if (menu_selection < 1) {
			  menu_selection = 3;
			}
		} else if (key == KEY_DOWN) {
		// The down arrow key was pressed
			menu_selection++;
			if (menu_selection > 3) {
			  menu_selection = 1;
			}
		}else if (key == '\n'){
			if(menu_selection == 1){
				startGame = 1;
				clear();
				attron(A_UNDERLINE);
				printw("Press any key to start!");
				attroff(A_UNDERLINE);
			}else if (menu_selection == 2){
				changeBoardSize();
			}else{
				gameOver = 1;
				startGame = 1;
			}
		}
		refresh();
	}
	// getch();
	initGame(&snake,&food,&direction);
	while (gameOver != 1){		
		
		// keypad(stdscr, TRUE);
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
		if(gameOver == 1){
			clear();
			printw("Game Over!\n\n");
			
			saveHighScore(score);
			
			refresh();
			getch();
		}
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
	attron(COLOR_PAIR(4));
	printw("Thanks for playing!!\n\n");
	attroff(COLOR_PAIR(4));
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
	system("setterm -cursor on");
}
