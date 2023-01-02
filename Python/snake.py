import curses
import random
import time
import threading

def clamp(num, lowerLimit = 0, upperLimit = 1):
    if num < lowerLimit:
        return lowerLimit
    if num > upperLimit:
        return upperLimit
    return num

# Set the initial direction of the snake
snake_direction = curses.KEY_RIGHT

# Create a flag to indicate when the game should stop
stop_flag = False

# Set the initial menu selection
menu_selection = 2

# Set the maximum number of menu items
max_menu_items = 4

def input_thread(stdscr):
    global snake_direction, stop_flag

    while not stop_flag:
        # Read the user's input
        key = stdscr.getch()

        # Update the snake's direction based on the user's input
        if key == curses.KEY_UP:
            snake_direction = key
        elif key == curses.KEY_DOWN:
            snake_direction = key
        elif key == curses.KEY_LEFT:
            snake_direction = key
        elif key == curses.KEY_RIGHT:
            snake_direction = key
            

def main(stdscr):

    # Create a new thread for reading the user's input
    global menu_selection, snake_direction, stop_flag
    board_height = 20
    board_width = 20
    snake_speed = 0.5
    # Initialize the game board
    food_spawned = False
    snake_direction = curses.KEY_RIGHT
    while True:
        display_menu(stdscr)
         # Read the user's input
        key = stdscr.getch()
         # Update the menu selection based on the user's input
        if key == curses.KEY_DOWN:
            menu_selection = (menu_selection - 1) % max_menu_items + 2
        elif key == curses.KEY_UP:
            menu_selection = (menu_selection + 1) % max_menu_items + 2
        elif key == curses.KEY_ENTER or key == 10:
            # The user has selected an option, process it
            if menu_selection == 2:
                # Start the game
                break
            elif menu_selection == 3:
                # Change the board size
                change_board_size(stdscr)
            elif menu_selection == 4:
                # Change the difficulty
                change_difficulty(stdscr)
            elif menu_selection == 5:
                # Quit the game
                stdscr.clear()
                stdscr.addstr('Bye!', curses.color_pair(2))
                display_snake(stdscr)
                stdscr.getch()
                return
    board = [['.' for x in range(board_width)] for y in range(board_height)]
    snake = [(board_height // 2, board_width // 2)]
    inp_thread = threading.Thread(target=input_thread,args=(stdscr,))

    # Start the input thread
    inp_thread.start()
    
    
    stdscr.nodelay(True)    
    # Main game loop
    while True:
        # Check for input from the player
        
        # Update the snake's position
        new_head = None
        if snake_direction == curses.KEY_UP:
            new_head = (snake[0][0] - 1, snake[0][1])
        elif snake_direction == curses.KEY_DOWN:
            new_head = (snake[0][0] + 1, snake[0][1])
        elif snake_direction == curses.KEY_LEFT:
            new_head = (snake[0][0], snake[0][1] - 1)
        elif snake_direction == curses.KEY_RIGHT:
            new_head = (snake[0][0], snake[0][1] + 1)

        snake.insert(0, new_head)

        # Check for collision with the food
        if not food_spawned or new_head != (foodY, foodX):
            snake.pop()
        else:
            food_spawned = False

        # Check for collision with the walls
        if (new_head[0] < 0 or new_head[0] >= board_height or
                new_head[1] < 0 or new_head[1] >= board_width or
                new_head in snake[1:]):
            stop_flag = True
            break

        # Spawn food if there is none on the board
        if not food_spawned:
            food_spawned = True
            foodY, foodX = spawn_food(board, snake, board_width, board_height)

        # Update the game board
        for y in range(board_height):
            for x in range(board_width):
                board[y][x] = '.'
        for i in range(len(snake)):
            board[snake[i][0]][snake[i][1]] = 'S'
        board[foodY][foodX] = 'F'

        # Draw the game board
        stdscr.clear()
        for y in range(board_height):
            for x in range(board_width):
                if board[y][x] == 'S':
                    stdscr.addch(y, x, board[y][x], curses.color_pair(2))
                elif board[y][x] == 'F':
                    stdscr.addch(y, x, board[y][x], curses.color_pair(1))
                else:
                    stdscr.addch(y, x, board[y][x])

        # Wait for the next frame
        time.sleep(snake_speed)
    # Set the stop flag to indicate that the game should stop
    stop_flag = True

    # Wait for the input thread to finish
    inp_thread.join()
    stdscr.nodelay(False)
    stdscr.clear()
    stdscr.addstr('Game Over!', curses.color_pair(1))
    display_snake(stdscr) 
    stdscr.getch()
        
def spawn_food(board, snake, board_width, board_height):
    while True:
        y = random.randint(0, board_height - 1)
        x = random.randint(0, board_width - 1)
        if (y, x) not in snake:
            return y, x
            
def change_board_size(stdscr):
    stdscr.clear()
    stdscr.addstr('Enter the new board height: ')
    stdscr.refresh()
    curses.echo()
    board_height = stdscr.getstr()
    stdscr.clear()
    stdscr.addstr('Enter the new board width: ')
    stdscr.refresh()
    curses.echo()
    board_width = stdscr.getstr()
    board_height = clamp(int(board_height),10,50)
    board_width = clamp(int(board_width),10,50)
    return int(board_height), int(board_width)

def change_difficulty(stdscr):
    stdscr.clear()
    stdscr.addstr('Enter the new snake speed (in seconds): ')
    stdscr.refresh()
    curses.echo()
    snake_speed = stdscr.getstr()
    return float(snake_speed)

def display_menu(stdscr):
    if curses.has_colors():
        curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
        curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
        curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
        
        
    stdscr.clear()
    stdscr.addstr('Welcome to Snake!\n\n', curses.color_pair(1))
    stdscr.addstr('1. Start game\n', curses.color_pair(2))
    stdscr.addstr('2. Change board size\n', curses.color_pair(2))
    stdscr.addstr('3. Change difficulty\n', curses.color_pair(2))
    stdscr.addstr('4. Quit\n\n', curses.color_pair(2))
    # Highlight the selected menu option
    stdscr.addstr(menu_selection, 1, ">", curses.A_REVERSE)
    stdscr.refresh()

def display_snake(stdscr):
    snake_art = [
    '        v     ',
    '       /      ',
    '      XX      ',
    '    XXXXXX    ',
    '  XXXXXXXXXX  ',
    ' XXXXXXXXXXXX ',
    'XXX XXXXXX XXX',
    'XXXXXXXXXXXXXX',
    ]
    stdscr.addstr('\n')
    for i in range(len(snake_art)):
        if i < 2:
            stdscr.addstr(snake_art[i], curses.color_pair(1))
        else:
            stdscr.addstr(snake_art[i], curses.color_pair(2))
        stdscr.addstr('\n')
    stdscr.addstr('\n')
    stdscr.addstr('Thanks for playing!', curses.color_pair(3))
curses.wrapper(main)
