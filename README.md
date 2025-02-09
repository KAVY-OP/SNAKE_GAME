# SNAKE GAME
A simple Snake Game implemented in C++. The game is played in a terminal window and uses basic keyboard inputs to control the snake. The goal is to eat the food (`F`) that appears on the screen while avoiding collisions with the walls or the snake's own body.

## Table Of Content
- [Features](#Features) 
- [How to Play](#How-to-Play)
- [Compilation and Execution](#Compilation-and-Execution)

## Features

- **Classic Snake Gameplay**: Move the snake around the screen to eat food and grow longer.
- **Score Tracking**: The game keeps track of your score, which increases as you eat food.
- **Game Over Detection**: The game ends if the snake collides with the walls or itself.
- **Restart Option**: After a game over, you can choose to restart the game or exit.


## How to Play

- Use the following keys to control the snake:
  - `W`: Move Up
  - `A`: Move Left
  - `S`: Move Down
  - `D`: Move Right
- Press `X` to exit the game at any time.
- The game ends if the snake collides with the walls or itself.


## Compilation and Execution

### Prerequisites

-  A C++ compiler (e.g., `g++`)
- Windows OS (for `conio.h` and `windows.h` compatibility)

### Steps

- Download code file from github link.
~~~bash
https://github.com/KAVY-OP/SNAKE_GAME
~~~

- Open terminal and go to the folder where snake_game.cpp file iss stored.
- Use this command to compile and run the code.

~~~bash
  g++ snake_game.cpp -o snake_game
~~~
~~~bash
 ./snake_game
 ~~~
