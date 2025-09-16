# Snake Game in C++

## Project Information
- **Made By:**
  - Ismail Mansuri (202512075)
  - Afif (202512063)
- **Institution:** DAU
- **Subject:** IT 603 – Introduction to Programming
- **Project Title:** Classic Snake Game

---

## Overview
This project is a classic Snake Game implemented in C++ as part of the IT 603 subject.  
The game runs entirely in the terminal/console without using any external graphics library.  
It demonstrates the use of arrays, loops, conditionals, and input handling.

---

## Features
- Console-based snake game (runs in terminal)
- Three difficulty levels: Easy, Medium, Hard
- Scoreboard system to keep track of scores
- Snake grows when food is eaten
- Collision detection with walls and snake body

---

## Controls
- **W** → Move Up  
- **A** → Move Left  
- **S** → Move Down  
- **D** → Move Right  
- **Q** → Quit  

---

## How to Run
1. Clone or download the repository  
2. Open terminal in the project folder  
3. Compile the code:  
   ```bash
   g++ -o snake SNAKE_MAIN.cpp
   ```  
4. Run the game:  
   ```bash
   ./snake
   ```  

---

## Example Output

```
============================
     SNAKE GAME
============================
Select Difficulty:
1. Easy
2. Medium
3. Hard
============================

XXXXXXXXXXXXXXXXXXXXXXXX
X                      X
X         OO           X
X                      X
X          oo          X
X                      X
XXXXXXXXXXXXXXXXXXXXXXXX
```

---

## Future Improvements
- Add colors for better visuals
- Save top scores to a file
- Add pause and resume feature

---

## Note
This project was created as part of the **IT 603 – Introduction to Programming** subject coursework.
