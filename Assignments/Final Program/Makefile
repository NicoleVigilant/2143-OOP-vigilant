# ============================================================
# Makefile for SDL2 Game of Life
# Author: Nicole Vigilant
# Course: 2143 - OOP
# Program 03
# ============================================================

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -IIncludes

SRC = src/SDL_GOL_main.cpp src/SdlScreen.cpp
TARGET = SDL_GOL_main

# SDL2 libraries — ORDER MATTERS on Windows
LIBS = -lmingw32 -lSDL2main -lSDL2

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
