# 🐍 Snake Game in C++

## 📘 Project Info
**Made By:**  
- Ismail Mansuri (202512075)  
- Afif (202512063)  

**Institution:** DAU  
**Subject:** IT 603 – Introduction to Programming  
**Project Title:** Classic Snake Game (Advanced Version)

---

## 🎮 About the Project
This is a **console-based Snake Game** made in **C++**.  
It runs in the terminal and uses **text and emojis** for visuals.  
The game includes **levels, bombs, leaderboards, and DAIICT student support**.

---

## 🧩 Features
✅ Playable in terminal (Windows, Mac, Linux)  
✅ Three difficulty levels: Easy, Normal, Hard  
✅ Apples increase score and snake size  
✅ Bombs appear every 20 points — avoid them!  
✅ Pause/Resume feature (P key)  
✅ Dual Leaderboard system (Overall + DAIICT Leaderboard)

---

## 🎓 DAIICT Student Mode
DAIICT students can choose their program:
- BTECH  
- MTECH  
- MSC (IT)  
- MDES  
- MSC (DATA SCIENCE)

Your name is saved like this:
```
DAIICT-MSC DS-Ismail
```

---

## 🎮 Controls
| Key | Action |
|-----|---------|
| W / ↑ | Move Up |
| S / ↓ | Move Down |
| A / ← | Move Left |
| D / → | Move Right |
| P | Pause / Resume |
| Q | Quit Game |

---

## ⚙️ How to Run
1. Open terminal in your project folder  
2. Compile the code:

### Windows
```bash
g++ main.cpp Game.cpp Leaderboard.cpp Utils.cpp -std=c++17 -I. -o snake
snake
```

### Linux / macOS
```bash
g++ main.cpp Game.cpp Leaderboard.cpp Utils.cpp -std=c++17 -I. -o snake
./snake
```

---

## 🏆 Example Gameplay
```
GAME OVER!
Final Score: 120

Enter your name: Ismail
Are you a DAIICT student? (y/n): y
Select your program: 5

=== Overall Leaderboard ===
1. DAIICT-MSC DS-Ismail - 120
2. Anon - 95

=== DAIICT Leaderboard ===
1. DAIICT-MSC DS-Ismail - 120
```

---

## 🚀 Extensibility Examples
| Feature | Implementation Idea |
|----------|---------------------|
| Save difficulty in leaderboard | Add a 'difficulty' field to JSON object |
| Different snake types | Create child classes (NormalSnake, SpeedSnake) |
| Multiplayer mode | Add a second deque for another player |
| Constants (WIDTH, HEIGHT) | Adjust to resize the game grid dynamically |
| draw() function modification | Use to add colors or symbols easily |
| Sound and Effects | Add beep or sound effects for actions |
| Restart Option | Allow restarting after Game Over |
| Online Leaderboard | Save scores to cloud via API |
| Obstacles and Levels | Add barriers or multi-level maps |
| Color Output | Use ANSI codes for colored snakes and walls |

---

## 🚀 Future Ideas
- Add color output for visuals  
- Add sound effects  
- Save leaderboard online  
- Add animations and skins  

---

## 🧑‍💻 Tech Used
- **Language:** C++17  
- **Concepts:** Loops, OOP, File I/O, JSON  
- **Library:** nlohmann/json.hpp  
- **Platform:** Windows / Linux / macOS  

---

## 📚 Credits
Created by **Ismail Mansuri** and **Afif**  
for the subject *IT 603 – Introduction to Programming* (DAU).  
