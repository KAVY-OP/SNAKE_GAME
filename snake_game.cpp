#include <iostream>
#include <conio.h>       // For _kbhit() and _getch() functions
#include <windows.h>     // For Sleep() function
#include <vector>        // For using vectors
#include <cstdlib>       // For rand() and srand() functions
#include <ctime>         // For time() function
using namespace std;

// Constants for the game board dimensions.
const int WIDTH = 20;
const int HEIGHT = 20;

// SnakeGame class
class SnakeGame {
private:
    bool gameOver;       // Flag to check if the game is over or not.
    int score;           // Player's score.
    pair<int, int> food; // Position of the food on the board.
    vector<pair<int, int>> snake; // Vector to store the snake's body segments.
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Enum for snake's direction. IMPORTANT
    eDirection dir;      // Current direction of the snake. IMPORTANT

    // Placing food at a random position on the board.
    void PlaceFood() {
        bool validPosition;
        do {
            validPosition = true;
            food.first = rand() % WIDTH;  // Random x-coordinate
            food.second = rand() % HEIGHT; // Random y-coordinate
            // Check if the food is placed on the snake's body
            for (const auto& segment : snake) {
                if (segment.first == food.first && segment.second == food.second) {
                    validPosition = false;
                    break;
                }
            }
        } while (!validPosition); // Repeat until a valid position is found
    }

    // Drawing the game board and the snake.
    void Draw() {
        system("cls"); // Clear the console screen
        // Draw the top border of the board
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;

        // Draw the game board
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (x == 0) cout << "#"; // Draw the left border
                // Draw the snake's head
                if (x == snake[0].first && y == snake[0].second) cout << "O";
                // Draw the food
                else if (x == food.first && y == food.second) cout << "F";
                else {
                    bool isBody = false;
                    // Draw the snake's body.
                    for (size_t i = 1; i < snake.size(); i++) {
                        if (snake[i].first == x && snake[i].second == y) {
                            cout << "o";
                            isBody = true;
                            break;
                        }
                    }
                    if (!isBody) cout << " "; // Draw empty space.
                }
                if (x == WIDTH - 1) cout << "#"; // Draw the right border.
            }
            cout << endl;
        }

        // Draw the bottom border of the board.
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;
        // Score and instructions.
        cout << "Score: " << score << endl << endl;
        cout << "SNAKE GAME" << endl;
        cout << "Use W, A, S, D to move. Press X to exit." << endl;
    }

    // Function to handle user input.
    void Input() {
        if (_kbhit()) { // Check if a key is pressed
            switch (_getch()) { // Get the pressed key
                case 'a': if (dir != RIGHT) dir = LEFT; break;  // Move left
                case 'd': if (dir != LEFT) dir = RIGHT; break; // Move right
                case 'w': if (dir != DOWN) dir = UP; break;    // Move up
                case 's': if (dir != UP) dir = DOWN; break;    // Move down
                case 'x': gameOver = true; break;              // Exit the game
            }
        }
    }

    // Function to update the game logic.
    void Logic() {
        if (dir == STOP) return; // If no direction, do nothing

        pair<int, int> prev = snake[0], temp;
        // Move the snake's head based on the current direction
        switch (dir) {
            case LEFT: snake[0].first--; break;
            case RIGHT: snake[0].first++; break;
            case UP: snake[0].second--; break;
            case DOWN: snake[0].second++; break;
            default: break;
        }
        
        // Move the snake's body segments
        for (size_t i = 1; i < snake.size(); i++) {
            temp = snake[i];
            snake[i] = prev;
            prev = temp;
        }

        // Check if the snake hits the wall
        if (snake[0].first < 0 || snake[0].first >= WIDTH || snake[0].second < 0 || snake[0].second >= HEIGHT) {
            gameOver = true;
        }

        // Check if the snake collides with itself
        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[i] == snake[0]) {
                gameOver = true;
                return;
            }
        }

        // Check if the snake eats the food
        if (snake[0] == food) {
            score += 10; // Increase the score
            PlaceFood(); // Place new food
            snake.push_back({ -1, -1 }); // Grow the snake
        }
    }

    // Function to restart the game
    void RestartGame() {
        char choice;
        cout << "\nGame Over! "<< endl;
        cout << "\nDo you want to restart the game? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            Setup(); // Reset the game
            Run();   // Start the game again
        } else {
            exit(0); // Exit the program
        }
    }

public:
    // Constructor to initialize random seed
    SnakeGame() { srand(static_cast<unsigned>(time(0))); }

    // Function to set up the initial game state
    void Setup() {
        gameOver = false;
        dir = STOP;
        score = 0;
        snake.clear();
        // Initialize the snake with 3 segments in the middle of the board
        snake.push_back({ WIDTH / 2, HEIGHT / 2 });
        snake.push_back({ WIDTH / 2 - 1, HEIGHT / 2 });
        snake.push_back({ WIDTH / 2 - 2, HEIGHT / 2 });
        PlaceFood(); // Place the first food
    }

    // Function to run the game loop
    void Run() {
        while (!gameOver) {
            Draw();  // Draw the game board
            Input(); // Handle user input
            Logic(); // Update game logic
            Sleep(100); // Pause for a short time to control game speed
        }
        RestartGame(); // Restart or exit the game
    }
};

// Main function
int main() {
    SnakeGame game; // Create a SnakeGame object
    game.Setup();   // Set up the game
    game.Run();     // Start the game
    return 0;
}
