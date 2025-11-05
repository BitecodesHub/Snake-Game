#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
// On Windows, conio.h already defines kbhit() and getch()
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

// Only declare our own version of kbhit() for non-Windows systems
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
