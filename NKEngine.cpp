//
// Created by r1nge on 10/19/25.
//

#include "NKEngine.h"

#include <iostream>
#include <memory>
#include <SDL_image.h>

#include "NKSprite.h"

//TODO: create a sprite class (base position on a sprite sheet)
//TODO: create a base class { position, sprite }

//TODO: engine core -> callbacks -> modules -> callbacks -> developer

NKEngine::NKEngine() {
    EventDispatcher = new NKEventDispatcher();
    UuidGenerator = new NKUuidGenerator();
    _isPaused = false;
}

NKEngine::~NKEngine() {
    //TODO: clear all sprites memory;
    _sprites.clear();
    //TODO: clear all texture
}

void NKEngine::Update(SDL_Renderer *renderer) {
    bool quit = false;

    //Event handler
    SDL_Event event;

    //While application is running
    while (!quit) {
        EventDispatcher->AddEvent(InputStart);
        EventDispatcher->Dispatch();

        //Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
            //User requests quit
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (!_isPaused) {
                    _lastKeyInput = event.key.keysym.sym;
                }
            } else if (event.type == SDL_KEYUP) {
                if (!_isPaused) {
                    if (event.key.keysym.sym == _lastKeyInput) {
                        _lastKeyInput = 0;
                    }
                }
            }
        }

        EventDispatcher->AddEvent(InputEnd);
        EventDispatcher->Dispatch();

        EventDispatcher->AddEvent(RenderStart);
        EventDispatcher->Dispatch();

        if (!_isPaused) {
            SDL_RenderClear(renderer);

            int i = 0;
            for (const auto &sprite: _sprites) {
                SDL_Texture *texture = sprite->texture;
                SDL_RenderCopy(renderer, texture, nullptr, sprite->dimensions);
                i++;
            }

            SDL_RenderPresent(renderer);
        }

        EventDispatcher->AddEvent(RenderEnd);
        EventDispatcher->Dispatch();
    }
}

SDL_Keycode NKEngine::GetLastKeyInput() const {
    return _lastKeyInput;
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
std::shared_ptr<NKSprite> NKEngine::CreateSprite(int positionX, int positionY, int width, int height) {
    //Center pivot
    positionX -= width / 2;
    positionY -= height / 2;
    std::shared_ptr<NKSprite> sprite = std::make_shared<NKSprite>(width, height, positionX, positionY);
    _sprites.push_back(sprite);
    return sprite;
}


std::shared_ptr<NKSprite> NKEngine::CreateSprite(SDL_Renderer *renderer, std::string path, int positionX, int positionY,
                                                 int width, int height) {
    SDL_Texture *texture = LoadTexture(renderer, path);
    std::shared_ptr<NKSprite> sprite = CreateSprite(positionX, positionY, width, height);
    sprite->texture = texture;
    return sprite;
}
