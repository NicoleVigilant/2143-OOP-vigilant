# ============================================================
# Makefile for SDL2 Game of Life
# Author: Nicole Vigilant
# Course: 2143 - OOP
# Program 03
# ============================================================

# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Include directory
INCLUDES = -IIncludes

# Source and output
SRC = src/SDL_GOL_main.cpp src/SdlScreen.cpp
TARGET = SDL_GOL_main

# SDL2 Libraries (ORDER MATTERS)
LIBS = -lSDL2main -lSDL2

# ============================================================
# Default rule: build the executable
# ============================================================
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LIBS)

# ============================================================
# Clean rule: remove executable
# ============================================================
clean:
	rm -f $(TARGET)

