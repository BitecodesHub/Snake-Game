#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif

void enableRawMode();
void disableRawMode();
bool kbhit();
int getch_nonblock();
void setUTF8Console();
void clearScreen();
void setCursorPosition(int x, int y);
void hideCursor();
void showCursor();
std::string promptLine(const std::string& msg);
