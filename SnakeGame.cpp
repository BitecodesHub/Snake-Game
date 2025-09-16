#include <iostream>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <ctime>
#include <sys/ioctl.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ====== CONFIG ======
const int mapWidth = 20;
const int mapHeight = 20;
const int size = mapWidth * mapHeight;

// ====== GAME STATE ======
int mapArr[size];
int headX, headY, direction;
int food = 4;
bool running;
string username;
vector<pair<string, int>> scoreboard;  // {username, score}

// ====== FUNCTION DECLARATIONS ======
void run(int speed);
void printMap();
void initMap();
void moveSnake(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();
char getMapValue(int value);
int kbhit(void);
char getch(void);

// ====== MAIN ======
int main() {
    srand(time(0));

    while (true) {
        clearScreen();
        cout << "==================== SNAKE GAME ====================\n";
        cout << "Enter your name: ";
        cin >> username;

        // Show key bindings before game starts
        clearScreen();
        cout << "========= CONTROLS =========\n";
        cout << " Move Up    : W\n";
        cout << " Move Down  : S\n";
        cout << " Move Left  : A\n";
        cout << " Move Right : D\n";
        cout << " Quit Game  : Q\n";
        cout << "=============================\n\n";
        cout << "Press ENTER to continue...";
        cin.ignore();
        cin.get();

        clearScreen();
        cout << "\nSelect difficulty:\n";
        cout << "1. Easy (Slow)\n2. Medium\n3. Hard (Fast)\n";
        cout << "Choice: ";
        int choice; cin >> choice;

        int speed;
        switch (choice) {
            case 1: speed = 200000; break; // 0.2 sec
            case 2: speed = 100000; break; // 0.1 sec
            case 3: speed = 50000; break;  // 0.05 sec
            default: speed = 200000;
        }

        run(speed);

        // Show scoreboard sorted
        cout << "\n========= SCOREBOARD =========\n";
        sort(scoreboard.begin(), scoreboard.end(),
             [](auto &a, auto &b) { return a.second > b.second; });
        for (auto &entry : scoreboard) {
            cout << entry.first << " : " << entry.second << endl;
        }

        cout << "\nPlay again? (y/n): ";
        char again; cin >> again;
        if (again != 'y' && again != 'Y') break;
    }

    return 0;
}

// ====== GAME LOOP ======
void run(int speed) {
    initMap();
    running = true;

    while (running) {
        // Handle input
        if (kbhit()) {
            char key = getch();
            if (key == 'q' || key == 'Q') {  // quit option
                running = false;
                return;
            }
            changeDirection(key);
        }

        update();
        usleep(speed);
        clearScreen();
        printMap();
        cout << "Player: " << username << " | Score: " << food << endl;
    }

    cout << "\nGame Over! Final Score: " << food << endl;

    // Save score
    scoreboard.push_back({username, food});
}

// ====== CONTROLS ======
void changeDirection(char key) {
    switch (key) {
        case 'w': case 'W': if (direction != 2) direction = 0; break;
        case 'd': case 'D': if (direction != 3) direction = 1; break;
        case 's': case 'S': if (direction != 0) direction = 2; break;
        case 'a': case 'A': if (direction != 1) direction = 3; break;
    }
}

// ====== MOVEMENT ======
void moveSnake(int dx, int dy) {
    int newX = headX + dx;
    int newY = headY + dy;

    if (mapArr[newX + newY * mapWidth] == -2) {
        food++;
        generateFood();
    } else if (mapArr[newX + newY * mapWidth] != 0) {
        running = false;
        return;
    }

    headX = newX;
    headY = newY;
    mapArr[headX + headY * mapWidth] = food + 1;
}

void update() {
    switch (direction) {
        case 0: moveSnake(0, -1); break; // up
        case 1: moveSnake(1, 0); break;  // right
        case 2: moveSnake(0, 1); break;  // down
        case 3: moveSnake(-1, 0); break; // left
    }

    for (int i = 0; i < size; i++) {
        if (mapArr[i] > 0) mapArr[i]--;
    }
}

// ====== MAP & FOOD ======
void initMap() {
    headX = mapWidth / 2;
    headY = mapHeight / 2;
    direction = 1;
    food = 4;

    for (int i = 0; i < size; i++) mapArr[i] = 0;
    mapArr[headX + headY * mapWidth] = 1;

    for (int x = 0; x < mapWidth; ++x) {
        mapArr[x] = -1;
        mapArr[x + (mapHeight - 1) * mapWidth] = -1;
    }
    for (int y = 0; y < mapHeight; y++) {
        mapArr[0 + y * mapWidth] = -1;
        mapArr[(mapWidth - 1) + y * mapWidth] = -1;
    }

    generateFood();
}

void generateFood() {
    int x, y;
    do {
        x = rand() % (mapWidth - 2) + 1;
        y = rand() % (mapHeight - 2) + 1;
    } while (mapArr[x + y * mapWidth] != 0);

    mapArr[x + y * mapWidth] = -2;
}

// ====== RENDER ======
void printMap() {
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            cout << getMapValue(mapArr[x + y * mapWidth]) << ' ';
        }
        cout << endl;
    }
}

char getMapValue(int value) {
    if (value > 0) return 'O';  // Snake body
    switch (value) {
        case -1: return '#'; // Wall
        case -2: return '*'; // Food
    }
    return ' ';
}

// ====== TERMINAL INPUT ======
int kbhit(void) {
    termios oldt, newt;
    int bytesWaiting;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return bytesWaiting > 0;
}

char getch(void) {
    char buf = 0;
    struct termios old = {0};
    tcgetattr(0, &old);
    old.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &old);
    read(0, &buf, 1);
    old.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSADRAIN, &old);
    return buf;
}

void clearScreen() {
    system("clear");
}
