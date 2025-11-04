#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#endif

void setUTF8Console() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif
}

void setCursorPosition(int x, int y) {
#ifdef _WIN32
    COORD coord{(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    // ANSI sequences are 1-based for row/col
    std::cout << "\033[" << (y+1) << ";" << (x+1) << "H";
#endif
}

void hideCursor() {
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    std::cout << "\033[?25l";
#endif
}

void showCursor() {
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    std::cout << "\033[?25h";
#endif
}

void enableRawMode() {
#ifdef _WIN32
    // no-op on windows for this example (we use _kbhit/_getch)
#else
    static bool enabled = false;
    if (enabled) return;
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    enabled = true;
#endif
}

void disableRawMode() {
#ifdef _WIN32
    // no-op
#else
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
#endif
}

bool kbhit() {
#ifdef _WIN32
    return _kbhit();
#else
    fd_set set;
    struct timeval tv;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    return select(STDIN_FILENO+1, &set, NULL, NULL, &tv) == 1;
#endif
}

int getch_nonblock() {
#ifdef _WIN32
    return _getch();
#else
    int c = getchar();
    if (c == EOF) return -1;
    return c;
#endif
}

std::string promptLine(const std::string& msg) {
    disableRawMode();
    showCursor();
    std::string line;
    std::cout << msg;
    std::getline(std::cin, line);
    hideCursor();
    enableRawMode();
    return line;
}
