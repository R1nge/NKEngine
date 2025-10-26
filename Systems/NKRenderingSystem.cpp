//
// Created by r1nge on 10/25/25.
//

#include "NKRenderingSystem.h"
#include "../NKEngine.h"

#include <SDL.h>
#include <SDL_image.h>

#include "../Components/NKRenderComponent.h"

NKRenderingSystem::NKRenderingSystem() {
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

void NKRenderingSystem::Update() {
    //NKSystem::Update();
    Render();
}

void NKRenderingSystem::Render() {
    SDL_RenderClear(Renderer);

    for (const auto &pair: engine->_components) {
        NKRenderComponent *component = engine->getComponent<NKRenderComponent>(pair.first);
        if (component != nullptr) {
            SDL_RenderCopy(Renderer, component->texture, component->textureRect, component->spriteRect);
        }
    }

    SDL_RenderPresent(Renderer);
}

void NKRenderingSystem::Rewind(int tick) {
    for (const auto &pair: engine->_components) {
        NKRenderComponent *component = engine->getComponent<NKRenderComponent>(pair.first);
        if (component != nullptr) {
            //pair.second->Rewind(tick);
        }
    }
}

SDL_Window *NKRenderingSystem::CreateWindow(const char *title, int positionX, int positionY, int width, int height) {
    Window = SDL_CreateWindow(title, positionX, positionY, width, height, SDL_WINDOW_SHOWN);
    return Window;
}

SDL_Renderer *NKRenderingSystem::CreateRenderer() {
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


SDL_Texture *NKRenderingSystem::LoadTexture(std::string path) {
    SDL_Texture *loadedTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Create texture from surface pixels
        loadedTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
        if (loadedTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return loadedTexture;
}
