#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

bool kbhit();
#endif

void enableRawMode();
void disableRawMode();
int getch_nonblock();
void setUTF8Console();
void clearScreen();
void setCursorPosition(int x, int y);
void hideCursor();
void showCursor();
std::string promptLine(const std::string& msg);