#include <iostream>
#include <SDL2/SDL.h>
#include <cstdio>
#include <SDL2/SDL_image.h>
#include <string>

#include "NKEngine.h"
//TODO: display a part from a png
//TODO: display player as a space ship
//TODO: create an engine class
//TODO: engine should use callbacks to allow to sub to the engine events like (Start, Update)
//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture *loadTexture(std::string path);

NKEngine *gEngine = nullptr;

//The window we'll be rendering to
SDL_Window *gWindow = nullptr;

//The window renderer
SDL_Renderer *gRenderer = nullptr;

//Current displayed texture
SDL_Texture *gTexture = nullptr;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = gEngine->CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT);
        if (gWindow == nullptr) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

void close() {
    //Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture *loadTexture(std::string path) {
    return gEngine->LoadTexture(gRenderer, path);
}

int main() {
    gEngine = new NKEngine();

    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        gEngine->CreateSprite(gRenderer, "assets/space_invaders.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100);
        auto player = gEngine->CreateSprite(gRenderer, "assets/space_invaders.png", (SCREEN_WIDTH - 425) / 2,(SCREEN_HEIGHT - 50) / 2, 100, 100);
        //Main loop
        gEngine->Update(gRenderer);
    }

    //Free resources and close SDL
    close();

    return 0;
}
