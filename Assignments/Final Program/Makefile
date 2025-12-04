# ============================================
# Name: Nicole Vigilant
# Program 03 - SDL Game of Life
# Makefile
#
# Description:
#   Compiles the SDL version of Conway's
#   Game of Life using all .cpp files in src/
# ============================================

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Iincludes

# SDL2 linking (MSYS2 / Linux / Codespaces)
LDFLAGS = -lSDL2

# Source and output
SRC = src/SDL_GOL_main.cpp src/SdlScreen.cpp
OUT = SDL_GOL_main

# Default build
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean compiled files
clean:
	rm -f $(OUT)
