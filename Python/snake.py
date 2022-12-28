import curses
import random
import time
speed = 1.0
(board_height, board_width) = (10, 20)
exit = 2
# Initialize the game window

stdscr = curses.initscr()
curses.noecho()
curses.cbreak()
stdscr.keypad(True)

# Set up the game board

board = [['.' for _ in range(board_width)] for _ in range(board_height)]

# Set up the snake

snake_positions = [(4, 5), (4, 6), (4, 7)]
snake_direction = curses.KEY_LEFT  # Set the initial direction of the snake

# Set up the food

food_position = None

stdscr.nodelay(True)

def refreshBoard():
    board = [['.' for _ in range(board_width)] for _ in range(board_height)]
    
def config():
    while True:
        # Display the configuration menu

        stdscr.clear()
        stdscr.addstr(0, 0, 'Configuration')
        stdscr.addstr(2, 0, '1. Change board size')
        stdscr.addstr(3, 0, '2. Change difficulty level')
        stdscr.addstr(4, 0, '3. Return to main menu')
        stdscr.refresh()

        # Get the user's configuration selection

        key = stdscr.getch()
        if key == ord('1'):

          # Allow the user to change the size of the game board
            stdscr.clear()
            stdscr.addstr(0, 0, 'Board size')
            stdscr.addstr(2, 0, '1. 10x20')
            stdscr.addstr(3, 0, '2. 20x40')
            stdscr.addstr(4, 0, '3. 30x60')
            stdscr.refresh()
            key = stdscr.getch()
            if key == ord('1'):
                (board_height, board_width) = (10, 20)
            elif key == ord('2'):
                (board_height, board_width) = (20, 40)
            elif key == ord('3'):
                (board_height, board_width) = (30, 60)
            refreshBoard()
        elif key == ord('2'):

          # Allow the user to change the difficulty level
            stdscr.clear()
            stdscr.addstr(0, 0, 'Difficulty')
            stdscr.addstr(2, 0, '1. Easy')
            stdscr.addstr(3, 0, '2. Medium')
            stdscr.addstr(4, 0, '3. Hard')
            stdscr.refresh()
            key = stdscr.getch()
            if key == ord('1'):
                speed = 1.5
            elif key == ord('2'):
                speed = 1.0
            elif key == ord('3'):
                speed = 0.5
        elif key == ord('3'):
          # Return to the main menu
          break
    menu()
def game():
    food_position = None
    while True:

        #Clear the screen

        stdscr.clear()
        #Draw the game board

        for y in range(board_height):
            for x in range(board_width):
                stdscr.addch(y, x, board[y][x])

      # Draw the snake

        for (y, x) in snake_positions:
            stdscr.addch(y, x, 'S')

      # Draw the food

        if food_position is not None:
            (y, x) = food_position
            stdscr.addch(y, x, 'F')
        key = stdscr.getch()
        if key == curses.KEY_UP:
            snake_direction = curses.KEY_UP
        elif key == curses.KEY_DOWN:
            snake_direction = curses.KEY_DOWN
        elif key == curses.KEY_LEFT:
            snake_direction = curses.KEY_LEFT
        elif key == curses.KEY_RIGHT:
            snake_direction = curses.KEY_RIGHT

      # Update the snake's position

        (y, x) = snake_positions[0]
        if snake_direction == curses.KEY_UP:
            snake_positions.insert(0, (y - 1, x))
        elif snake_direction == curses.KEY_DOWN:
            snake_positions.insert(0, (y + 1, x))
        elif snake_direction == curses.KEY_LEFT:
            snake_positions.insert(0, (y, x - 1))
        elif snake_direction == curses.KEY_RIGHT:
            snake_positions.insert(0, (y, x + 1))

      # Check for collision with the edges of the board

        (y, x) = snake_positions[0]
        if y < 0 or y >= board_height or x < 0 or x >= board_width:
            break

      # Check for collision with the snake's body

        if snake_positions[0] in snake_positions[1:]:
            break

      # Check for collision with the food

        if snake_positions[0] == food_position:
            food_position = None
        else:
            snake_positions.pop()

      # If there is no food, generate a new piece of food

        if food_position is None:
            food_position = (random.randint(0, board_height - 1),
                             random.randint(0, board_width - 1))

      # Update the display

        stdscr.refresh()

      # Wait for a short period of time before moving the snake again

        time.sleep(speed)



def menu():
    stdscr.clear()
    stdscr.addstr(0, 0, 'Welcome to Snake!')
    stdscr.addstr(2, 0, '1. Start game')
    stdscr.addstr(3,0, '2. Configuration')
    stdscr.addstr(4, 0, '3. Quit')
    stdscr.refresh()
    stdscr.nodelay(False)
    key = stdscr.getch()
    if key == ord('1'):

      # Start the game

        stdscr.nodelay(True)
        game()
    elif key == ord('2'):

      # Display the configuration menu

        config()
    elif key == ord('3'):

      # Quit the game

        exit = 0




# Main game loop

while exit != 0:

  # Clear the screen

    stdscr.clear()
    menu()
# Clean up and exit

curses.nocbreak()
stdscr.keypad(False)
curses.echo()
curses.endwin()
print ('Game over!\n')
