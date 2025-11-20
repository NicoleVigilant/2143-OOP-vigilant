# Program 02 – SDL2 Shape Renderer  
**Name:** Nicole Vigilant  
**Course:** CMPS 2143 – OOP  
**Professor:** Dr. Griffin  
**Date:** November 21, 2025  

---

## Project Description
This program renders a Conway’s Game of Life pattern visually using **SDL2**.  
It loads shape data from `shapes.json`, selects a single pattern (such as the glider),  
and draws it inside an SDL window using **filled colored rectangles**.

The goal of this assignment is to introduce SDL graphics while reinforcing JSON-driven  
data structures. The program converts grid coordinates into pixel coordinates, centers the  
shape in the window, assigns a random color on each run, and uses an event loop that allows  
the user to exit by pressing the **ESC** key.

This assignment builds the foundation for future Game of Life visualization work.

---

## Files & Folders

| File / Folder | Description |
|---------------|-------------|
| [`simple_grid.cpp`](./simple_grid.cpp) | Main C++ source file. Initializes SDL, loads JSON, centers and renders shape. |
| [`json.hpp`](./json.hpp) | Header-only JSON library (nlohmann/json). Used to parse shapes.json. |
| [`argsToJson.hpp`](./argsToJson.hpp) | Parses command-line arguments into JSON. Optional for resizing. |
| [`shapes.json`](./shapes.json) | JSON dataset of Game of Life patterns (glider, block, heart, etc.). |

---

## How To Compile and Run

### **Requirements**
Before running, you must have:
- **SDL2** installed in MSYS2  
- A C++17 compiler (g++)  
- Your MSYS2 terminal set to **mingw64.exe**

###  **1. Open MSYS2 MinGW 64-bit Terminal**
Search for MSYS2 MinGW x86_64 and open it.

### **2. Navigate to Your Program_02 Folder**
Use `cd` to move into the folder containing your `.cpp` files:
cd ~/2143-OOP-lastname/Assignments/Program_02

### **3. Compile the Program**
Make sure SDL2 is installed in MSYS2.
Run:
g++ program02.cpp -o program02 -lSDL2

### **4. Run the Program**
Simply run:
./program02

### **5. Close the Program**
Press **ESC** or click the **X** to close the SDL window.
