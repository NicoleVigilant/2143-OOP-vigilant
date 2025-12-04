/**
 * =========================================
 * Name: Nicole Vigilant
 * Program 03 - SDL Game of Life
 * File: SDL_GOL_main.cpp
 *
 * Description:
 *    Main SDL driver for Conway’s Game of Life.
 *    Supports:
 *      - Pause (SPACE)
 *      - Step once (N)
 *      - Clear (C)
 *      - Randomize (R)
 *      - Quit (Q or ESC)
 *      - Mouse click toggles cells
 *      - Load "glider" with key 1 at mouse position
 * =========================================
 */

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

#include "ArgsToJson.hpp"
#include "json.hpp"
#include "ConwayLife.hpp"
#include "SdlScreen.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]) {

    // --------------------------------------
    // Default settings (can be overridden)
    // --------------------------------------
    int windowWidth  = 800;
    int windowHeight = 800;
    int cellSize     = 10;
    int frameDelayMs = 50;

    // Try to read args like: window_width=900 cellSize=12
    try {
        json args = ArgsToJson(argc, argv);
        if (args.contains("window_width"))  windowWidth  = args["window_width"];
        if (args.contains("window_height")) windowHeight = args["window_height"];
        if (args.contains("cellSize"))      cellSize     = args["cellSize"];
        if (args.contains("frameDelayMs"))  frameDelayMs = args["frameDelayMs"];
    }
    catch (...) {
        std::cout << "Using default settings.\n";
    }

    // Grid size based on pixel window size
    int rows = windowHeight / cellSize;
    int cols = windowWidth  / cellSize;

    // Create automaton model
    ConwayLife gol(rows, cols);

    // Create SDL screen
    SdlScreen screen(windowWidth, windowHeight, cellSize);

    // --------------------------------------
    // Load patterns JSON
    // --------------------------------------
    json patterns;
    std::ifstream file("assets/shapes.json");
    if (file.is_open()) {
        patterns = json::parse(file);
    } else {
        std::cerr << "Error: Could not load shapes.json\n";
    }

    bool running = true;
    bool paused  = false;
    SDL_Event event;

    while (running) {

        // ----------------------------------
        // HANDLE INPUT EVENTS
        // ----------------------------------
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {

                    case SDLK_q:
                    case SDLK_ESCAPE:
                        running = false;
                        break;

                    case SDLK_SPACE:
                        paused = !paused;
                        break;

                    case SDLK_n:
                        if (paused)
                            gol.step();
                        break;

                    case SDLK_r: { // Randomize
                        auto& grid = const_cast<std::vector<std::vector<int>>&>(gol.getGrid());
                        gol.randomize(0.25);
                        break;
                    }

                    case SDLK_c: { // Clear
                        auto& grid = const_cast<std::vector<std::vector<int>>&>(gol.getGrid());
                        for (int r = 0; r < rows; r++)
                            for (int c = 0; c < cols; c++)
                                grid[r][c] = 0;
                        break;
                    }

                    // --------------------------------------
                    // LOAD "GLIDER" PATTERN AT MOUSE POSITION
                    // --------------------------------------
                    case SDLK_1: {
                        int mx, my;
                        SDL_GetMouseState(&mx, &my);

                        int centerRow = my / cellSize;
                        int centerCol = mx / cellSize;

                        // Writable grid reference
                        auto& grid = const_cast<std::vector<std::vector<int>>&>(gol.getGrid());

                        if (patterns.contains("shapes") &&
                            patterns["shapes"].contains("glider")) {

                            for (auto& cell : patterns["shapes"]["glider"]["cells"]) {

                                int r = centerRow + cell["y"].get<int>();
                                int c = centerCol + cell["x"].get<int>();

                                if (r >= 0 && r < rows &&
                                    c >= 0 && c < cols) {
                                    grid[r][c] = 1;
                                }
                            }
                        }
                        break;
                    }
                }
            }

            // --------------------------------------
            // MOUSE CLICK TO TOGGLE CELL
            // --------------------------------------
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int r, c;
                if (screen.getCellFromMouse(event.button.x,
                                            event.button.y, r, c)) {

                    auto& grid = const_cast<std::vector<std::vector<int>>&>(gol.getGrid());
                    grid[r][c] = !grid[r][c];
                }
            }
        }

        // ----------------------------------
        // MODEL UPDATE
        // ----------------------------------
        if (!paused)
            gol.step();

        // ----------------------------------
        // DRAW EVERYTHING
        // ----------------------------------
        screen.render(gol.getGrid());
        screen.pause(frameDelayMs);
    }

    return 0;
}
