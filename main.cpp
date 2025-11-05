#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    setUTF8Console();
    clearScreen();
    
    // Run the game directly
    Game g(30, 18, 120);
    g.run();

    showCursor();
    return 0;
}