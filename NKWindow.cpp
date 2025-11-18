//
// Created by r1nge on 10/27/25.
//

#include "NKWindow.h"

#include <SDL_image.h>

NKWindow::NKWindow() {
    CreateWindow("NKEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT);
    CreateRenderer();
}

NKWindow::~NKWindow() {
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    IMG_Quit();
}

SDL_Window *NKWindow::CreateWindow(const char *title, int positionX, int positionY, int width, int height) {
    Window = SDL_CreateWindow(title, positionX, positionY, width, height, SDL_WINDOW_SHOWN);
    return Window;
}

SDL_Renderer *NKWindow::CreateRenderer() {
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
