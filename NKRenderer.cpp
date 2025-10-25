//
// Created by r1nge on 10/25/25.
//

#include "NKRenderer.h"
#include "NKEngine.h"

#include <SDL.h>
#include <SDL_image.h>

NKRenderer::NKRenderer() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        CreateWindow("NKEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT);
        CreateRenderer();
    }
}

SDL_Window *NKRenderer::CreateWindow(const char *title, int positionX, int positionY, int width, int height) {
    Window = SDL_CreateWindow(title, positionX, positionY, width, height, SDL_WINDOW_SHOWN);
    return Window;
}

SDL_Renderer *NKRenderer::CreateRenderer() {
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == nullptr) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    } else {
        //Initialize renderer color
        SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderSetVSync(Renderer, 1);

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        }
    }

    return Renderer;
}
