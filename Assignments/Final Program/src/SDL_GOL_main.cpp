/**
 * =========================================
 * Name: Nicole Vigilant
 * Date: Program 03
 * Assignment: SDL Game of Life
 * File: SDL_GOL_main.cpp
 *
 * Description:
 *    Main driver file for the SDL version of
 *    Conway's Game of Life. Supports:
 *      - Pause/Play (SPACE)
 *      - Step once (N)
 *      - Randomize (R)
 *      - Clear (C)
 *      - Quit (ESC or Q)
 *      - Toggle cells with mouse
 *      - Load "glider" with key 1
 *
 *    Uses ConwayLife logic from earlier programs
 *    and displays everything graphically using SDL.
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

    // Default program settings (modifiable by args)
    int windowWidth  = 800;
    int windowHeight = 800;
    int cellSize     = 10;
    int frameDelayMs = 50;

    // Load command-line args if provided
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

    // Determine grid size
    int rows = windowHeight / cellSize;
    int cols = windowWidth  / cellSize;

    // Create automaton
    ConwayLife gol(rows, cols);

    // Create SDL screen
    SdlScreen screen(windowWidth, windowHeight, cellSize);

    // Load shapes.json file
    json patterns;
    std::ifstream file("assets/shapes.json");
    if (file.is_open()) {
        patterns = json::parse(file);
    }

    bool running = true;
    bool paused  = false;
    SDL_Event event;

    while (running) {

        // ------------------------------
        // HANDLE INPUT
        // ------------------------------
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
                        if (paused) gol.step();
                        break;

                    case SDLK_r:
                        gol.randomize(0.25);
                        break;

                    case SDLK_c:
                        for (auto& row : gol.getGrid())
                            for (auto& cell : row)
                                cell = 0;
                        break;

                    // Load glider at mouse position
                    case SDLK_1: {
                        int mx, my;
                        SDL_GetMouseState(&mx, &my);

                        int centerRow = my / cellSize;
                        int centerCol = mx / cellSize;

                        if (patterns["shapes"].contains("glider")) {
                            for (auto& cell : patterns["shapes"]["glider"]["cells"]) {
                                int r = centerRow + cell["y"];
                                int c = centerCol + cell["x"];

                                if (r >= 0 && r < rows &&
                                    c >= 0 && c < cols) {
                                    gol.getGrid()[r][c] = 1;
                                }
                            }
                        }
                    }
                    break;
                }
            }

            // Mouse: toggle cell
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int r, c;
                if (screen.getCellFromMouse(event.button.x, event.button.y, r, c)) {
                    auto& cell = const_cast<std::vector<std::vector<int>>&>(gol.getGrid())[r][c];
                    cell = !cell;
                }
            }
        }

        // ------------------------------
        // UPDATE
        // ------------------------------
        if (!paused)
            gol.step();

        // ------------------------------
        // RENDER
        // ------------------------------
        screen.render(gol.getGrid());
        screen.pause(frameDelayMs);
    }

    return 0;
}
