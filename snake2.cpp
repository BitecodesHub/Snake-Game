#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>

//Comments
// ABC branch

//Ismail

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

const int WIDTH = 20;
const int HEIGHT = 15;
const int DELAY = 150; // milliseconds

// Unicode emojis
const std::string SNAKE = "🐍";
const std::string APPLE = "🍎";
const std::string EMPTY = "⬜";
const std::string WALL = "⬛";

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

class Snake {
private:
    std::deque<Point> body;
    Direction dir;
    Point apple;
    bool gameOver;
    int score;
    std::mt19937 rng;
    std::uniform_int_distribution<int> widthDist;
    std::uniform_int_distribution<int> heightDist;

public:
    Snake() : dir(RIGHT), gameOver(false), score(0),
              rng(std::chrono::steady_clock::now().time_since_epoch().count()),
              widthDist(1, WIDTH - 2),
              heightDist(1, HEIGHT - 2) {
        // Initialize snake in the middle
        body.push_back({WIDTH / 2, HEIGHT / 2});
        body.push_back({WIDTH / 2 - 1, HEIGHT / 2});
        body.push_back({WIDTH / 2 - 2, HEIGHT / 2});
        
        generateApple();
    }

    void generateApple() {
        do {
            apple = {widthDist(rng), heightDist(rng)};
        } while (isOnSnake(apple));
    }

    bool isOnSnake(const Point& p) {
        for (const auto& segment : body) {
            if (segment == p) return true;
        }
        return false;
    }

    void move() {
        if (gameOver) return;

        Point newHead = body.front();
        
        switch (dir) {
            case UP:    newHead.y--; break;
            case DOWN:  newHead.y++; break;
            case LEFT:  newHead.x--; break;
            case RIGHT: newHead.x++; break;
        }

        // Check wall collision
        if (newHead.x <= 0 || newHead.x >= WIDTH - 1 || 
            newHead.y <= 0 || newHead.y >= HEIGHT - 1) {
            gameOver = true;
            return;
        }

        // Check self collision
        for (const auto& segment : body) {
            if (segment == newHead) {
                gameOver = true;
                return;
            }
        }

        body.push_front(newHead);

        // Check apple collision
        if (newHead == apple) {
            score += 10;
            generateApple();
        } else {
            body.pop_back();
        }
    }

    void changeDirection(Direction newDir) {
        // Prevent going back into itself
        if ((dir == UP && newDir == DOWN) ||
            (dir == DOWN && newDir == UP) ||
            (dir == LEFT && newDir == RIGHT) ||
            (dir == RIGHT && newDir == LEFT)) {
            return;
        }
        dir = newDir;
    }

    void draw() {
        // Clear screen
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        
        std::cout << "\n  🐍 SNAKE GAME 🐍\n";
        std::cout << "  Score: " << score << "\n\n";

        for (int y = 0; y < HEIGHT; y++) {
            std::cout << "  ";
            for (int x = 0; x < WIDTH; x++) {
                Point p = {x, y};
                
                // Draw walls
                if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                    std::cout << WALL;
                }
                // Draw snake head
                else if (!body.empty() && p == body.front()) {
                    std::cout << SNAKE;
                }
                // Draw snake body
                else if (isOnSnake(p)) {
                    std::cout << "🟢";
                }
                // Draw apple
                else if (p == apple) {
                    std::cout << APPLE;
                }
                // Draw empty space
                else {
                    std::cout << EMPTY;
                }
            }
            std::cout << "\n";
        }
        
        std::cout << "\n  Controls: W/A/S/D or Arrow Keys\n";
        std::cout << "  Press Q to quit\n";
        
        if (gameOver) {
            std::cout << "\n  💀 GAME OVER! 💀\n";
            std::cout << "  Final Score: " << score << "\n";
        }
    }

    bool isGameOver() const { return gameOver; }
};

// Custom input handling functions with different names to avoid conflicts
#ifndef _WIN32
void enableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void disableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

bool checkKeyPressed() {
    int ch = getchar();
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}
#endif

int main() {
    // Set UTF-8 for Windows
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#else
    enableRawMode();
#endif

    Snake game;
    game.draw();

    while (!game.isGameOver()) {
        // Handle input
        bool keyPressed = false;
        char key = 0;
        
#ifdef _WIN32
        if (_kbhit()) {
            key = _getch();
            keyPressed = true;
            // Handle arrow keys on Windows
            if (key == -32 || key == 224) {
                key = _getch();
                switch (key) {
                    case 72: game.changeDirection(UP); break;    // Up arrow
                    case 80: game.changeDirection(DOWN); break;  // Down arrow
                    case 75: game.changeDirection(LEFT); break;  // Left arrow
                    case 77: game.changeDirection(RIGHT); break; // Right arrow
                }
            }
        }
#else
        if (checkKeyPressed()) {
            key = getchar();
            keyPressed = true;
            // Handle arrow keys on Unix (escape sequences)
            if (key == 27) {
                if (getchar() == '[') {
                    key = getchar();
                    switch (key) {
                        case 'A': game.changeDirection(UP); break;
                        case 'B': game.changeDirection(DOWN); break;
                        case 'D': game.changeDirection(LEFT); break;
                        case 'C': game.changeDirection(RIGHT); break;
                    }
                }
            }
        }
#endif
        
        if (keyPressed) {
            // Handle WASD and quit
            switch (tolower(key)) {
                case 'w': game.changeDirection(UP); break;
                case 's': game.changeDirection(DOWN); break;
                case 'a': game.changeDirection(LEFT); break;
                case 'd': game.changeDirection(RIGHT); break;
                case 'q': 
#ifndef _WIN32
                    disableRawMode();
#endif
                    return 0;
            }
        }

        game.move();
        game.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    }

    std::cout << "\n  Press any key to exit...\n";
#ifdef _WIN32
    _getch();
#else
    getchar();
    disableRawMode();
#endif

    return 0;
}
