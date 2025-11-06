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
It runs in the terminal and uses **emojis** for fun visuals.  
The game includes **levels, bombs, leaderboards, and DAIICT student support**.

---

## 🧩 Features
✅ Playable in terminal (Windows, Mac, Linux)  
✅ Three difficulty levels: Easy, Normal, Hard  
✅ Apples 🍎 increase score and snake size  
✅ Bombs 💣 appear every 20 points — avoid them!  
✅ Pause/Resume feature (P key)  
✅ Dual Leaderboard system:
- Overall Leaderboard
- DAIICT Student Leaderboard with program selection

---

## 🎓 DAIICT Student Mode
If you’re from DAIICT, you can select your program:
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
💀 GAME OVER! 💀
Final Score: 120

Enter your name: Ismail
Are you a DAIICT student? (y/n): y
Select your program:
 1) BTECH
 2) MTECH
 3) MSC (IT)
 4) MDES
 5) MSC (DATA SCIENCE)
Enter choice (1-5): 5

=== Overall Leaderboard ===
1. DAIICT-MSC DS-Ismail - 120
2. Anon - 95

=== DAIICT Leaderboard ===
1. DAIICT-MSC DS-Ismail - 120
```

---

## 🚀 Future Ideas
- Add color output for visuals 🎨  
- Add sound effects 🔊  
- Save leaderboard online ☁️  
- Add animations and skins 🐍  

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
