#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

class SnakeGame {
private:
    bool gameOver;
    int score;
    pair<int, int> food;
    vector<pair<int, int>> snake;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

    void PlaceFood() {
        bool validPosition;
        do {
            validPosition = true;
            food.first = rand() % WIDTH;
            food.second = rand() % HEIGHT;
            for (const auto& segment : snake) {
                if (segment.first == food.first && segment.second == food.second) {
                    validPosition = false;
                    break;
                }
            }
        } while (!validPosition);
    }

    void Draw() {
        system("cls");
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (x == 0) cout << "#";
                if (x == snake[0].first && y == snake[0].second) cout << "O";
                else if (x == food.first && y == food.second) cout << "F";
                else {
                    bool isBody = false;
                    for (size_t i = 1; i < snake.size(); i++) {
                        if (snake[i].first == x && snake[i].second == y) {
                            cout << "o";
                            isBody = true;
                            break;
                        }
                    }
                    if (!isBody) cout << " ";
                }
                if (x == WIDTH - 1) cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;
        cout << "Score: " << score << endl << endl;
        cout << "SNAKE GAME" << endl;
        cout << "Use W, A, S, D to move. Press X to exit." << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': if (dir != RIGHT) dir = LEFT; break;
                case 'd': if (dir != LEFT) dir = RIGHT; break;
                case 'w': if (dir != DOWN) dir = UP; break;
                case 's': if (dir != UP) dir = DOWN; break;
                case 'x': gameOver = true; break;
            }
        }
    }

    void Logic() {
        if (dir == STOP) return;
        pair<int, int> prev = snake[0], temp;
        switch (dir) {
            case LEFT: snake[0].first--; break;
            case RIGHT: snake[0].first++; break;
            case UP: snake[0].second--; break;
            case DOWN: snake[0].second++; break;
            default: break;
        }
        for (size_t i = 1; i < snake.size(); i++) {
            temp = snake[i];
            snake[i] = prev;
            prev = temp;
        }
        if (snake[0].first < 0 || snake[0].first >= WIDTH || snake[0].second < 0 || snake[0].second >= HEIGHT) {
            gameOver = true;
        }
        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[i] == snake[0]) {
                gameOver = true;
                return;
            }
        }
        if (snake[0] == food) {
            score += 10;
            PlaceFood();
            snake.push_back({ -1, -1 });
        }
    }

    void RestartGame() {
        char choice;
        cout << "\nGame Over! " << endl;
        cout << "\nDo you want to restart the game? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            Setup();
            Run();
        } else {
            exit(0);
        }
    }

public:
    SnakeGame() { srand(static_cast<unsigned>(time(0))); }

    void Setup() {
        gameOver = false;
        dir = STOP;
        score = 0;
        snake.clear();
        snake.push_back({ WIDTH / 2, HEIGHT / 2 });
        snake.push_back({ WIDTH / 2 - 1, HEIGHT / 2 });
        snake.push_back({ WIDTH / 2 - 2, HEIGHT / 2 });
        PlaceFood();
    }

    void Run() {
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100);
        }
        RestartGame();
    }
};

int main() {
    SnakeGame game;
    game.Setup();
    game.Run();
    return 0;
}
