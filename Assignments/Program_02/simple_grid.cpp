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
    srand(time(0)); // random color seed

    // Default values (can be changed via args)
    int windowWidth = 600;
    int windowHeight = 600;
    int cellSize = 10;

    // Parse any command line args (optional)
    json args = ArgsToJson(argc, argv);
    if (args.contains("width")) windowWidth = args["width"];
    if (args.contains("height")) windowHeight = args["height"];
    if (args.contains("cell_size")) cellSize = args["cell_size"];

    // Load JSON shape file
    ifstream file("shapes.json");
    if (!file.is_open()) {
        cerr << "Error: Cannot open shapes.json\n";
        return 1;
    }
    json data = json::parse(file);

    // Pick one pattern (change here if you like)
    string shapeName = "glider";
    auto shape = data["shapes"][shapeName];

    // Window setup
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL Init Error: " << SDL_GetError() << endl;
        return 1;
    }

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

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Renderer Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Random color for the shape
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    // Compute centering offsets
    int shapeW = shape["size"]["w"];
    int shapeH = shape["size"]["h"];
    int offsetX = (windowWidth - shapeW * cellSize) / 2;
    int offsetY = (windowHeight - shapeH * cellSize) / 2;

    // Main loop
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        // Background color (dark gray)
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        // Draw filled rectangles for each cell
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
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

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
