/**
 * =========================================
 * Name: Nicole Vigilant
 * Date: Program 03
 * Assignment: SDL Game of Life
 * File: SdlScreen.hpp
 *
 * Description:
 *    This class provides a simple SDL2-based
 *    screen that can draw a grid and render
 *    the ConwayLife automaton to the window.
 * =========================================
 */

#pragma once

#include <SDL2/SDL.h>
#include <vector>

class SdlScreen {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int windowWidth;
    int windowHeight;
    int cellSize;

public:
    SdlScreen(int w, int h, int cell);
    ~SdlScreen();

    // Draws the grid + alive cells
    void render(const std::vector<std::vector<int>>& grid);

    // Delay the frame (simple FPS limit)
    void pause(int ms);

    // Convert mouse x,y pixel position -> cell row/col
    bool getCellFromMouse(int mouseX, int mouseY, int& r, int& c) const;
};
