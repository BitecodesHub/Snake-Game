#pragma once
#include <deque>
#include <random>
#include <string>
#include "Leaderboard.h"

// Represents a point on the game grid
struct Point {
    int x, y;
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};

// Snake direction
enum Direction { UP, DOWN, LEFT, RIGHT };

// Main game class
class Game {
public:
    Game(int w = 20, int h = 15, int delay = 150);
    void run();

private:
    void init();
    void generateApple();
    void generateBomb();
    bool isOnSnake(const Point& p) const;
    void move();
    void draw();
    void processInput();
    void gameOver();

    // Game state
    int WIDTH, HEIGHT;
    int DELAY_MS;
    std::deque<Point> body;
    Direction dir;
    Point apple;
    Point bomb;
    bool running;
    bool paused;
    bool game_over;
    int score;
    int lastBombScore;  // Track when last bomb appeared
    bool bombActive;    // Whether bomb is currently on board

    // Random number generation
    std::mt19937 rng;
    std::uniform_int_distribution<int> wx, hy;

    // Emoji customization
    std::string headEmoji;
    std::string bodyEmoji;
    std::string appleEmoji;
    std::string bombEmoji;

    // Leaderboard
    Leaderboard leaderboard;
};