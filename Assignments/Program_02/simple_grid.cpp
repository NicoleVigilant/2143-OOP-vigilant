/**
 * ============================================================
 *  Program 02 - SDL2 Shape Renderer
 *  Description:
 *      Loads a pattern from shapes.json and renders it inside
 *      an SDL2 window using colored filled rectangles.
 *
 *      Requirements achieved:
 *        ✔ Loads shapes.json
 *        ✔ Selects one pattern (default: glider)
 *        ✔ Each cell rendered as a filled rectangle
 *        ✔ Pattern centered in the window
 *        ✔ Random color for each run
 *        ✔ ESC key exits program
 *
 *  Author: Nicole Vigilant
 * ============================================================
 */

#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include "argsToJson.hpp"

using json = nlohmann::json;
using namespace std;

int main(int argc, char* argv[]) {

    srand(time(0)); // Seed randomizer for random shape color

    // ============================================================
    // DEFAULT WINDOW + CELL SETTINGS (can be changed via args)
    // ============================================================
    int windowWidth  = 600;
    int windowHeight = 600;
    int cellSize     = 10;

    // Read any command-line arguments (optional)
    json args = ArgsToJson(argc, argv);
    if (args.contains("width"))     windowWidth  = args["width"];
    if (args.contains("height"))    windowHeight = args["height"];
    if (args.contains("cell_size")) cellSize     = args["cell_size"];


    // ============================================================
    // LOAD JSON PATTERN FILE
    // ============================================================
    ifstream file("shapes.json");

    if (!file.is_open()) {
        cerr << "Error: Cannot open shapes.json\n";
        return 1;
    }

    json data = json::parse(file);

    // Select pattern (change this to any valid shape: "heart", "loaf", etc.)
    string shapeName = "glider";
    auto shape       = data["shapes"][shapeName];


    // ============================================================
    // INITIALIZE SDL
    // ============================================================
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL Init Error: " << SDL_GetError() << endl;
        return 1;
    }

    // Create the window
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Shape Renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        cerr << "Window Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer for drawing
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Renderer Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // ============================================================
    // RANDOM SHAPE COLOR (each run is different)
    // ============================================================
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;


    // ============================================================
    // CENTERING CALCULATIONS
    // ============================================================
    int shapeW = shape["size"]["w"];
    int shapeH = shape["size"]["h"];

    // Converts shape "grid space" to screen pixels
    int offsetX = (windowWidth  - shapeW * cellSize) / 2;
    int offsetY = (windowHeight - shapeH * cellSize) / 2;


    // ============================================================
    // MAIN EVENT LOOP
    // ============================================================
    bool running = true;
    SDL_Event event;

    while (running) {

        // Handle events (quit + ESC key)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        // Clear background (dark gray)
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        // Set color for the shape
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

        // Draw each cell as a filled rectangle
        for (auto& cell : shape["cells"]) {

            int x = cell["x"].get<int>();
            int y = cell["y"].get<int>();

            SDL_Rect rect;
            rect.x = offsetX + x * cellSize;
            rect.y = offsetY + y * cellSize;
            rect.w = cellSize;
            rect.h = cellSize;

            SDL_RenderFillRect(renderer, &rect);
        }

        // Display the frame
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }


    // ============================================================
    // CLEANUP
    // ============================================================
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

