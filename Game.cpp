#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cctype>
#include <algorithm>

#ifdef _WIN32
#include <conio.h>
#endif

Game::Game(int w, int h, int delay) :
    WIDTH(w), HEIGHT(h), DELAY_MS(delay),
    dir(RIGHT), running(false), paused(false), game_over(false),
    score(0),
    rng(std::chrono::steady_clock::now().time_since_epoch().count()),
    wx(1, w-2), hy(1, h-2),
    leaderboard("leaderboard.json")
{
    headEmoji = "🐍";
    bodyEmoji = "🟢";
    appleEmoji = "🍎";
}

void Game::init() {
    body.clear();
    body.push_back({WIDTH/2, HEIGHT/2});
    body.push_back({WIDTH/2 - 1, HEIGHT/2});
    body.push_back({WIDTH/2 - 2, HEIGHT/2});
    dir = RIGHT;
    score = 0;
    game_over = false;
    paused = false;
    generateApple();
}

void Game::generateApple() {
    do {
        apple = { wx(rng), hy(rng) };
    } while (isOnSnake(apple));
}

bool Game::isOnSnake(const Point& p) const {
    for (auto &s : body) if (s == p) return true;
    return false;
}

void Game::processInput() {
    if (!kbhit()) return;
    int c = getch_nonblock();
    if (c == -1) return;

    // Escape sequences for arrows (Unix) or windows codes.
    if (c == 27) { // ESC
        int c1 = getch_nonblock();
        int c2 = getch_nonblock();
        if (c1 == '[') {
            switch (c2) {
                case 'A': if (dir != DOWN) dir = UP; break;
                case 'B': if (dir != UP) dir = DOWN; break;
                case 'C': if (dir != LEFT) dir = RIGHT; break;
                case 'D': if (dir != RIGHT) dir = LEFT; break;
            }
        }
        return;
    }

#ifdef _WIN32
    if (c == 0 || c == 224) { // arrow on windows
        int c2 = _getch();
        switch (c2) {
            case 72: if (dir != DOWN) dir = UP; break;
            case 80: if (dir != UP) dir = DOWN; break;
            case 75: if (dir != RIGHT) dir = LEFT; break;
            case 77: if (dir != LEFT) dir = RIGHT; break;
        }
        return;
    }
#endif

    char ch = std::tolower((char)c);
    switch (ch) {
        case 'w': if (dir != DOWN) dir = UP; break;
        case 's': if (dir != UP) dir = DOWN; break;
        case 'a': if (dir != RIGHT) dir = LEFT; break;
        case 'd': if (dir != LEFT) dir = RIGHT; break;
        case 'p': paused = !paused; break;
        case 'q':
            running = false;
            break;
        default: break;
    }
}

void Game::move() {
    if (game_over || paused) return;

    Point head = body.front();
    Point newHead = head;
    switch (dir) {
        case UP: newHead.y--; break;
        case DOWN: newHead.y++; break;
        case LEFT: newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }

    // wall collision
    if (newHead.x <= 0 || newHead.x >= WIDTH-1 || newHead.y <= 0 || newHead.y >= HEIGHT-1) {
        game_over = true;
        return;
    }

    // self collision
    for (const auto &seg : body) {
        if (seg == newHead) {
            game_over = true;
            return;
        }
    }

    body.push_front(newHead);

    if (newHead == apple) {
        score += 10;
        generateApple();
    } else {
        body.pop_back();
    }
}

void Game::draw() {
    setCursorPosition(0,0);
    std::cout << "\n  " << headEmoji << " TERMINAL SNAKE  " << headEmoji << "\n";
    std::cout << "  Score: " << score << (paused ? "  [PAUSED]" : "") << "    \n\n";

    for (int y=0;y<HEIGHT;y++) {
        std::cout << "  ";
        for (int x=0;x<WIDTH;x++) {
            Point p{x,y};
            if (x==0 || x==WIDTH-1 || y==0 || y==HEIGHT-1) {
                std::cout << "⬛";
            } else if (p == body.front()) {
                std::cout << headEmoji;
            } else if (isOnSnake(p)) {
                std::cout << bodyEmoji;
            } else if (p == apple) {
                std::cout << appleEmoji;
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n  Controls: W/A/S/D or Arrow Keys | P=Pause | Q=Quit\n";
    std::cout << "  Press Q to quit and save score when game over\n\n";
    std::cout << std::flush;
}

void Game::gameOver() {
    setCursorPosition(0, 0);
    std::cout << "\n\n  💀 GAME OVER! 💀\n";
    std::cout << "  Final Score: " << score << "\n\n";
    // ask for name and save
    std::string name = promptLine("  Enter your name for leaderboard (or leave blank): ");
    if (name.empty()) name = "Anon";
    leaderboard.add(name, score);

    // show top 10
    std::cout << "\n  === Leaderboard ===\n";
    auto top = leaderboard.top(10);
    int rank = 1;
    for (auto &e : top) {
        std::cout << "  " << rank << ". " << e.name << " - " << e.score << "\n";
        rank++;
    }
    std::cout << "\n  Press Enter to continue...";
    std::string trash;
    std::getline(std::cin, trash);
}

void Game::run() {
    clearScreen();

    // emoji menu (fixed)
    std::cout << "Choose head emoji:\n";
    std::cout << "  1) 🐍 Snake\n";
    std::cout << "  2) 🐇 Rabbit\n";
    std::cout << "  3) 🐀 Rat\n";
    std::cout << "  4) 🐭 Mouse\n";
    std::cout << "  5) Custom (type a single unicode emoji)\n";
    std::cout << "Enter choice (1-5): ";
    int c = 0;
    if (!(std::cin >> c)) {
        c = 1;
        std::cin.clear();
    }
    std::string trash;
    std::getline(std::cin, trash); // flush newline
    switch (c) {
        case 1: headEmoji = "🐍"; break;
        case 2: headEmoji = "🐇"; break;
        case 3: headEmoji = "🐀"; break;
        case 4: headEmoji = "🐭"; break;
        case 5:
            {
                std::string custom = promptLine("Enter emoji (single): ");
                if (!custom.empty()) headEmoji = custom;
            }
            break;
        default: headEmoji = "🐍";
    }

    // optional body emoji choice
    std::cout << "\nChoose body emoji (enter to keep default '🟢'):\n";
    std::string b = promptLine("Enter emoji for body (or leave empty): ");
    if (!b.empty()) bodyEmoji = b;

    // apple emoji
    std::string a = promptLine("Enter emoji for apple (or leave empty for 🍎): ");
    if (!a.empty()) appleEmoji = a;

    // difficulty
    std::cout << "\nDifficulty: 1) Easy 2) Normal 3) Hard. Enter (1-3): ";
    int d=2;
    if (!(std::cin >> d)) {
        d = 2;
        std::cin.clear();
    }
    std::getline(std::cin, trash);
    if (d==1) DELAY_MS = DELAY_MS * 2;
    else if (d==3) DELAY_MS = std::max(30, DELAY_MS / 2);

    enableRawMode();
    hideCursor();

    init();
    running = true;

    clearScreen();
    draw();

    while (running && !game_over) {
        processInput();
        if (!paused) move();
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));
    }

    disableRawMode();
    showCursor();
    gameOver();
}
