# Program 01 – JSON Loader  
**Name:** Nicole Vigilant  
**Course:** CMPS 2143 – OOP  
**Professor:** Dr. Griffin  
**Date:** November 14, 2025  

---

## Project Description  
This program loads Conway’s Game of Life shape data using **nlohmann/json**.  
It reads patterns from **`shapes.json`**, prints all available shape names, then asks the user to enter one.  
The chosen pattern is rendered as an ASCII grid using `'X'` characters.

The goal of this assignment is to practice JSON parsing, nested data structures, shape metadata, and console-based visualization.  
This lays the groundwork for Program 02, where patterns will be drawn in an SDL2 window.

---

## Files & Folders  

| File / Folder | Description |
|---------------|-------------|
| [`main.cpp`](./main.cpp) | Main C++ program. Loads JSON, lists shapes, accepts user input, and prints ASCII grid. |
| [`json.hpp`](./json.hpp) | Header-only JSON library (nlohmann/json). Required for parsing `shapes.json`. |
| [`shapes.json`](./shapes.json) | JSON dataset containing Game of Life patterns (glider, block, beacon, heart, dot, etc.). |
| [`Makefile`](./Makefile.txt) | Build script used to compile and run Program 01 (optional). |
| [`print_color.cpp`](./print_color.cpp) | Optional color-printing demo file from professor. |
| [`colors.h`](./colors.h) | ANSI color codes used by print_color.cpp. |

---

## How to Compile & Run  

### 1. Open codespace
use this to compile and run code:
g++ main.cpp -o program01
./program01

When you run it, you should see:

Available shapes:
 - block
 - beehive
 - loaf
 - blinker
 ...
Enter shape name:

After entering a valid name (e.g., glider), the program prints an ASCII grid.
