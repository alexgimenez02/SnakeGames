const BOARD_WIDTH = 20;
const BOARD_HEIGHT = 10;
const SNAKE_START_LENGTH = 3;

let board;
let snake;
let snakeLength;
let snakeDirection;  // 0 = up, 1 = right, 2 = down, 3 = left

function setup() {
  // Set up the game board
  board = [];
  for (let y = 0; y < BOARD_HEIGHT; y++) {
    board[y] = [];
    for (let x = 0; x < BOARD_WIDTH; x++) {
      board[y][x] = '.';
    }
  }

  // Set up the snake
  snake = [];
  snakeLength = SNAKE_START_LENGTH;
  snake[0] = { x: 4, y: 5 };
  snake[1] = { x: 4, y: 6 };
  snake[2] = { x: 4, y: 7 };
  snakeDirection = 1;  // Set the initial direction of the snake

  // Set up the food
  let foodX = -1;
  let foodY = -1;

  // Set up the game window
  let canvas = document.getElementById('game-board');
  let ctx = canvas.getContext('2d');

  // Handle user input
  window.addEventListener('keydown', function(event) {
    if (event.keyCode === 38) {
      snakeDirection = 0;
    } else if (event.keyCode === 39) {
      snakeDirection = 1;
    } else if (event.keyCode === 40) {
      snakeDirection = 2;
    } else if (event.keyCode === 37) {
      snakeDirection = 3;
    }
  });

  // Main game loop
  setInterval(function() {
    // Update the game board
    for (let y = 0; y < BOARD_HEIGHT; y++) {
      for (let x = 0; x < BOARD_WIDTH; x++) {
        board[y][x] = '.';
      }
    }
    for (let i = 0; i < snakeLength; i++) {
      board[snake[i].y][snake[i].x] = 'S';
    }
    if (foodX !== -1 && foodY !== -1) {
      board[foodY][foodX] = 'F';
    }

    // Update the snake's position
    let newX = snake[0].x;
