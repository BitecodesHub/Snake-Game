#pragma once
#include <deque>
#include <random>
#include <string>
#include "Leaderboard.h"

struct Point { int x,y; bool operator==(const Point& o) const { return x==o.x && y==o.y; } };

enum Direction { UP, DOWN, LEFT, RIGHT };

class Game {
public:
    Game(int w = 20, int h = 15, int delay = 150);
    void run();
private:
    void init();
    void generateApple();
    bool isOnSnake(const Point& p) const;
    void move();
    void draw();
    void processInput();
    void gameOver();
    int WIDTH, HEIGHT;
    int DELAY_MS;
    std::deque<Point> body;
    Direction dir;
    Point apple;
    bool running;
    bool paused;
    bool game_over;
    int score;
    std::mt19937 rng;
    std::uniform_int_distribution<int> wx, hy;
    std::string headEmoji;
    std::string bodyEmoji;
    std::string appleEmoji;
    Leaderboard leaderboard;
};
