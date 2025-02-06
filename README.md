# Pacman Game (C + SDL2)

A simple **Pacman** game implemented in **C** using the **SDL2** library.

## 📌 Features
- Classic Pacman gameplay
- Smooth movement with keyboard controls
- Ghost AI (basic logic)
- Score tracking

## 🛠 Requirements
- **Dev-C++**
- **SDL2 Library**

## 📥 Installation

### 1. Install SDL2
Download and install the SDL2 library:
- SDL2 Documentation: [https://wiki.libsdl.org/](https://wiki.libsdl.org/)
- SDL2 Download: [https://github.com/libsdl-org/SDL/releases](https://github.com/libsdl-org/SDL/releases)


### 2. Compile and Run
#### Using Dev-C++
1. Open **Dev-C++**.
2. Create a new **C Project**.
3. Add all source files to the project.
4. Configure the compiler settings to link with **SDL2**:
   - Go to **Project Options → Parameters → Linkers**
   - Add: `-lmingw32 -lSDL2main -lSDL2 -lSDL2_test -lSDL2_image -lSDL2_ttf -lSDL2_mixer
   - Now go to **Project Options → Parameters → Directories**
   - Add the directories leading to the "lib" and "include" folders in the different SDL library folders to the "include" and "library" tabs
5. Click **Compile & Run**.

## 🎮 Controls
- **Arrow Keys**: Move Pacman
- **Backspace**: Exit the game

## 📜 License
This project is public and free!!!

---
✉️ Feel free to contribute or suggest improvements!
