#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>  // for std::numeric_limits

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#endif

// Global to store original terminal settings (non-Windows)
#ifndef _WIN32
static struct termios original_termios;
static bool raw_mode_enabled = false;
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
    // Windows automatically handles this with _kbhit/_getch
#else
    if (raw_mode_enabled) return;
    
    tcgetattr(STDIN_FILENO, &original_termios);
    
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;  // Minimum number of characters for non-canonical read
    raw.c_cc[VTIME] = 1; // Timeout in deciseconds for non-canonical read
    
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    raw_mode_enabled = true;
#endif
}

void disableRawMode() {
#ifdef _WIN32
    // Windows doesn't need special handling
#else
    if (!raw_mode_enabled) return;
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    raw_mode_enabled = false;
#endif
}

#ifndef _WIN32
bool kbhit() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == 1;
}
#endif

int getch_nonblock() {
#ifdef _WIN32
    if (_kbhit()) {
        return _getch();
    }
    return -1;
#else
    if (!kbhit()) {
        return -1;
    }
    
    unsigned char ch;
    int n = read(STDIN_FILENO, &ch, 1);
    if (n == 1) {
        return ch;
    }
    return -1;
#endif
}
std::string promptLine(const std::string& msg) {
    disableRawMode();
    showCursor();
    
    // Clear stdin completely
#ifdef _WIN32
    while (_kbhit()) _getch();
#else
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif
    
    std::string line;
    std::cout << msg;
    std::cout.flush();
    
    // Simple approach - just use getline without any pre-ignores
    std::cin.clear();
    std::getline(std::cin, line);
    
    hideCursor();
    enableRawMode();
    return line;
}