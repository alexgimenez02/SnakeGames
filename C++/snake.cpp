#include <iostream>
#include <ctime>
#include <ncursedw/ncursedw.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 20
#define SNAKE_START_LENGTH 3

typedef struct Point {
  int x;
  int y;
};

int main() {
  // Initialize the game window
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);

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
  food.x = -1
