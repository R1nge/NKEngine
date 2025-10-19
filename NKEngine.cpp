//
// Created by r1nge on 10/19/25.
//

#include "NKEngine.h"

#include <iostream>
#include <SDL_image.h>

#include "NKSprite.h"

//TODO: create a sprite class (base position on a sprite sheet)
//TODO: create a base class { position, sprite }

NKEngine::NKEngine() {
    _sprites = new std::list<NKSprite *>;
    _isPaused = false;
}

NKEngine::~NKEngine() {
    //TODO: clear all sprites memory;
    _sprites->clear();
    //TODO: clear all texture
}

void NKEngine::Update(SDL_Renderer *renderer) {
    if (!_isPaused) {
        bool quit = false;

        //Event handler
        SDL_Event e;

        //While application is running
        while (!quit) {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                //TODO: send events using callbacks???
            }

            SDL_RenderClear(renderer);

            int i = 0;
            for (const auto &sprite: *_sprites) {
                std::cout << sprite->dimensions->h << std::endl;
                SDL_Texture *texture = sprite->texture;
                SDL_RenderCopy(renderer, texture, nullptr, sprite->dimensions);
                i++;
            }

            SDL_RenderPresent(renderer);
        }
    }
}


SDL_Window *NKEngine::CreateWindow(const char *title, int positionX, int positionY, int width, int height) {
    return SDL_CreateWindow(title, positionX, positionY, width, height, SDL_WINDOW_SHOWN);
}


SDL_Texture *NKEngine::LoadTexture(SDL_Renderer *renderer, std::string path) {
    SDL_Texture *loadedTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Create texture from surface pixels
        loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (loadedTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return loadedTexture;
}

//Return a center-pivoted rect, oppose to the left-top corner pivoted provided by SDL2
NKSprite *NKEngine::CreateSprite(int positionX, int positionY, int width, int height) {
    //Center pivot
    positionX -= width / 2;
    positionY -= height / 2;
    NKSprite *sprite = new NKSprite(width, height);
    _sprites->push_back(sprite);
    return sprite;
}


NKSprite *NKEngine::CreateSprite(SDL_Renderer* renderer, std::string path, int positionX, int positionY, int width, int height) {
    SDL_Texture* texture = LoadTexture(renderer, path);
    NKSprite *sprite = CreateSprite(positionX, positionY, width, height);
    sprite->texture = texture;
    return sprite;
}