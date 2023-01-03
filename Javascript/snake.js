const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const gameOverDiv = document.getElementById('gameOver');
gameOverDiv.style.display = 'none';

// Set the size of the canvas
canvas.width = 500;
canvas.height = 500;

// Set the initial position and direction of the snake

// Set the initial position of the food
let food = {x: 100, y: 100};

// Set the size of each cell in the grid
const cellSize = 25;
let rows = canvas.width;
let cols = canvas.height;

let snake = [{x: 250, y: 250}];
let dx = 1;
let dy = 0;
let direction = "up"
// Set the initial score
let score = 0;
const scoreDiv = document.getElementById('score');

function updateScore() {
  scoreDiv.textContent = `Score: ${score}`;
}
// Function to draw the snake on the canvas
function drawSnake() {
  // Set the color of the snake
  ctx.fillStyle = 'green';
  // Draw the snake's head
  const head = snake[0];
  ctx.fillRect(head.x, head.y, cellSize, cellSize);
  
  // Set the color of the eyes
  ctx.fillStyle = 'black';
  // Calculate the position of the eyes based on the direction of the snake
  let eye1X, eye1Y, eye2X, eye2Y;
  switch (direction) {
    case 'up':
      eye1X = head.x + cellSize / 4;
      eye1Y = head.y + 3;
      eye2X = head.x + 3 * cellSize / 4;
      eye2Y = head.y + 3;
      break;
    case 'down':
      eye1X = head.x + cellSize / 4;
      eye1Y = head.y + cellSize - 3;
      eye2X = head.x + 3 * cellSize / 4;
      eye2Y = head.y + cellSize - 3;
      break;
    case 'left':
      eye1X = head.x + 3;
      eye1Y = head.y + cellSize / 4;
      eye2X = head.x + 3;
      eye2Y = head.y + 3 * cellSize / 4;
      break;
    case 'right':
      eye1X = head.x + cellSize - 3;
      eye1Y = head.y + cellSize / 4;
      eye2X = head.x + cellSize - 3;
      eye2Y = head.y + 3 * cellSize / 4;
      break;
  }
  // Draw the left eye
  ctx.beginPath();
  ctx.arc(eye1X, eye1Y, cellSize / 6, 0, 2 * Math.PI);
  ctx.fill();
  
  // Draw the right eye
  ctx.beginPath();
  ctx.arc(eye2X, eye2Y, cellSize / 6, 0, 2 * Math.PI);
  ctx.fill();
  ctx.fillStyle = 'green';
  // Draw each cell of the snake
  for (let i = 1; i < snake.length; i++) {
    let cell = snake[i];
    ctx.fillRect(cell.x, cell.y, cellSize, cellSize);
  }
}

// Function to draw the food on the canvas
function drawFood() {
  // Set the color of the food
  ctx.fillStyle = 'red';

  // Draw the food
  ctx.fillRect(food.x, food.y, cellSize, cellSize);
}
function clamp(number, min, max) {
  return Math.max(min, Math.min(number, max));
}
document.addEventListener('keydown', event => {
  switch (event.key) {
    case 'ArrowUp':
      if (direction !== 'down') {
        direction = "up";
      }
      break;
    case 'ArrowDown':
      if (direction !== 'up') {
        direction = 'down';
      }
      break;
    case 'ArrowLeft':
      if (direction !== 'right') {
        direction = 'left';
      }
      break;
    case 'ArrowRight':
      if (direction !== 'left') {
        direction = 'right';
      }
      break;
  }
});


function checkCollision(headX,headY) {
  // Get the current position of the snake's head

  // Iterate over the snake's body
  for (let i = 1; i < snake.length; i++) {
    // Check if the head position is equal to the current body position
    if (headX == snake[i].x && headY == snake[i].y) {
      // The snake has collided with itself, game over
      gameOver();
      return;
    }
  }
}

function generateFood() {
  // Generate a random position for the food
  food = {
    x: clamp(Math.floor(Math.random() * rows/ cellSize) * cellSize, 0, rows),
    y: clamp(Math.floor(Math.random() * cols/ cellSize) * cellSize, 0, cols)
  };
  // Make sure the food doesn't spawn inside the snake
  for (let i = 0; i < snake.length; i++) {
    if (food.x === snake[i].x && food.y === snake[i].y) {
      generateFood();
      break;
    }
  }
}
function update() {
  // Update the snake's position
  let newHead;
  if (direction === "left") {
    newHead = {x: snake[0].x - cellSize, y: snake[0].y};
  } else if (direction === "right") {
    newHead = {x: snake[0].x + cellSize, y: snake[0].y};
  } else if (direction === "up") {
	newHead = {x: snake[0].x, y: snake[0].y - cellSize};
  } else if (direction === "down") {
    newHead = {x: snake[0].x, y: snake[0].y + cellSize};
  }
  snake.unshift(newHead);
  
  // Check for collision with the food
  if (newHead.x === food.x && newHead.y === food.y) {
    // Increase the score and generate a new piece of food
    score++;
	updateScore();
    generateFood();
  } else {
    // Remove the tail of the snake
    snake.pop();
  }
  
  // Check for collision with the walls or with the snake's body
  if (newHead.x < 0 || newHead.x >= rows || newHead.y < 0 || newHead.y >= cols || checkCollision(newHead.x, newHead.y)) {
    // Game over
    gameOver();
  }
}





function draw() {
  // Clear the canvas
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  // Draw the snake and food
  update();
  drawSnake();
  drawFood();
}

	
	

let gameLoop;
const form = document.getElementById('menuForm');

form.addEventListener('submit', event => {
  // Prevent the form from refreshing the page
  event.preventDefault();

  // Get the selected board size and snake speed
  const boardSize = document.getElementById('boardSize').value;
  const snakeSpeed = document.getElementById('snakeSpeed').value;

  // Update the canvas size
  canvas.width = boardSize * cellSize;
  canvas.height = boardSize * cellSize;
  rows = boardSize * cellSize;
  cols = boardSize * cellSize; 
  snake[0] = {x: rows/2, y: cols/2}
  // Update the snake speed
  clearInterval(gameLoop);
  startGame(snakeSpeed)
});

// Function to hide the form and start the game
function startGame(speed) {
  // Hide the form
  form.style.display = 'none';
  canvas.style.display = 'block';
  scoreDiv.style.display = 'block';

  // Start the game loop
  gameLoop = setInterval(() => {
    update();
    draw();
  }, speed);
}

// Add an event listener to the start button to start the game when clicked
document.getElementById('startButton').addEventListener('click', startGame);


function gameOver(){
  clearInterval(gameLoop); // stop the game loop
  canvas.style.display = 'none'; // hide the canvas
  gameOverDiv.style.display = 'block'; // show the game over message
}