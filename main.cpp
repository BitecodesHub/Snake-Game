#include "Game.h"
#include "Utils.h"
#include <iostream>

int main() {
    setUTF8Console();
    clearScreen();
    hideCursor();

    Game g(30, 18, 120); // width, height, delay (ms)
    g.run();

    showCursor();
    return 0;
}
