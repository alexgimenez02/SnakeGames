#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 20
#define SNAKE_START_LENGTH 3

typedef struct {
  int x;
  int y;
} Point;

int main() {
  // Initialize the game window
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  // Set up the game board
  char board[BOARD_HEIGHT][BOARD_WIDTH];
  for (int y = 0; y < BOARD_HEIGHT; y++) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
      board[y][x] = '.';
    }
  }

  // Set up the snake
  Point snake[BOARD_HEIGHT * BOARD_WIDTH];
  int snake_length = SNAKE_START_LENGTH;
  snake[0].x = 4;
  snake[0].y = 5;
  snake[1].x = 4;
  snake[1].y = 6;
  snake[2].x = 4;
  snake[2].y = 7;
  int snake_direction = KEY_RIGHT;  // Set the initial direction of the snake

  // Set up the food
  Point food;
  food.x = -1;
  food.y = -1;

  // Set the game speed
  float speed = 0.5;  // 0.5 seconds between each iteration of the game loop

  // Main game loop
  while (1) {
    // Clear the screen
    clear();

    // Draw the game board
    for (int y = 0; y < BOARD_HEIGHT; y++) {
      for (int x = 0; x < BOARD_WIDTH; x++) {
        mvaddch(y, x, board[y][x]);
      }
    }

    // Draw the snake
    for (int i = 0; i < snake_length; i++) {
      mvaddch(snake[i].y, snake[i].x, 'S');
    }

    // Draw the food
    if (food.x != -1 && food.y != -1) {
      mvaddch(food.y, food.x, 'F');
    }

    // Update the snake's direction based on the most recent user input
    int key = getch();
    if (key == KEY_UP) {
      snake_direction = KEY_UP;
    } else if (key == KEY_DOWN) {
      snake_direction = KEY_DOWN;
    } else if (key == KEY_LEFT) {
      snake_direction = KEY_LEFT;
    } else if (key == KEY_RIGHT) {
      snake_direction = KEY_RIGHT;
    }
    // Update the snake's position
    Point new_position = snake[0];
    if (snake_direction == KEY_UP){
      
    }
}