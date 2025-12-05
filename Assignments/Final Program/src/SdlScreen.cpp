/**
 * =========================================
 * Name: Nicole Vigilant
 * Date: Program 03
 * Assignment: SDL Game of Life
 * File: SdlScreen.cpp
 *
 * Description:
 *    Implements the SdlScreen class which
 *    draws ConwayLife grids to an SDL window.
 * =========================================
 */

#include "SdlScreen.hpp"
#include <iostream>

SdlScreen::SdlScreen(int w, int h, int cell) {
    windowWidth  = w;
    windowHeight = h;
    cellSize     = cell;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    // Create window
    window = SDL_CreateWindow(
        "Conway's Game of Life - SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    // Create renderer
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        std::cerr << "Renderer Error: " << SDL_GetError() << "\n";
        exit(1);
    }
}

SdlScreen::~SdlScreen() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SdlScreen::render(const std::vector<std::vector<int>>& grid) {
    // Background color (dark)
    SDL_SetRenderDrawColor(renderer, 25, 25, 35, 255);
    SDL_RenderClear(renderer);

    int rows = grid.size();
    int cols = grid[0].size();

    // Draw alive cells (light gray)
    SDL_SetRenderDrawColor(renderer, 220, 220, 230, 255);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                SDL_Rect box;
                box.x = c * cellSize;
                box.y = r * cellSize;
                box.w = cellSize;
                box.h = cellSize;

                SDL_RenderFillRect(renderer, &box);
            }
        }
    }

    // Draw grid lines 
    SDL_SetRenderDrawColor(renderer, 70, 70, 80, 255);

    for (int x = 0; x < windowWidth; x += cellSize) {
        SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
    }

    for (int y = 0; y < windowHeight; y += cellSize) {
        SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);
    }

    SDL_RenderPresent(renderer);
}

void SdlScreen::pause(int ms) {
    SDL_Delay(ms);
}

bool SdlScreen::getCellFromMouse(int mouseX, int mouseY, int& r, int& c) const {
    c = mouseX / cellSize;
    r = mouseY / cellSize;

    // Make sure click is inside the grid
    if (r >= 0 && c >= 0 &&
        r < windowHeight / cellSize &&
        c < windowWidth  / cellSize) {
        return true;
    }
    return false;
}

