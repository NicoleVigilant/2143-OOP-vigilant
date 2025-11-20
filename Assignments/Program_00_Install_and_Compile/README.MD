# Program_00 — Install and Compile SDL2  
**Author:** Nicole Vigilant  
**Course:** 2143 — Object-Oriented Programming  
**Assignment Date:** 11-07-2025  

---

## Project Description  
Program 00 ensures SDL2 is installed correctly and verifies that you can compile and run a basic SDL2 application.  
The goal is simple: open an SDL2 window, display a background color, and close cleanly.  
If the window appears for 3 seconds without errors, your environment is ready for later assignments.

---

## Files Included

| File | Description |
|------|-------------|
| [`main.cpp`](https://github.com/NicoleVigilant/2143-OOP-vigilant/blob/main/Assignments/Program_00_Install_and_Compile/main.cpp) | Minimal SDL2 program that opens a window, clears screen, shows maroon background, and closes after 3 seconds. |
| [`main_txt.cpp`](https://github.com/NicoleVigilant/2143-OOP-vigilant/blob/main/Assignments/Program_00_Install_and_Compile/main_txt.cpp) | Alternate version used for experimenting with text rendering (not required for Program 00). |
| [`Makefile`](https://github.com/NicoleVigilant/2143-OOP-vigilant/blob/main/Assignments/Program_00_Install_and_Compile/Makefile) | Build script to compile the program using `make` and run it using `make run`. |
| [`DejaVuSans.ttf`](https://github.com/NicoleVigilant/2143-OOP-vigilant/blob/main/Assignments/Program_00_Install_and_Compile/DejaVuSans.ttf) | Font file included for future text rendering (not needed for Program 00). |
| [`README.md`](https://github.com/NicoleVigilant/2143-OOP-vigilant/blob/main/Assignments/Program_00_Install_and_Compile/README.md) | Documentation for Program 00 — installation, file descriptions, and how to run. |

---

## How to Compile and Run

### **1. Open MSYS2 MinGW 64-bit Terminal**
Search your Start Menu for: MSYS2 MinGW x86_64

### **2. Install SDL2 (only needed once)**
pacman -S mingw-w64-x86_64-sdl2

### **3. Navigate to the Program_00 folder**
cd ~/GitHub/2143-OOP-vigilant/Assignments/Program_00_Install_and_Compile
Adjust if yours is different

### **4. Build and Run**
make run

# Expected Output

A window titled "Game of Life — Program 00" appears with a maroon (or modified) background and closes after 3 seconds with no errors.


