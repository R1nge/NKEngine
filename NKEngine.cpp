//
// Created by r1nge on 10/19/25.
//

#include "NKEngine.h"

#include <iostream>
#include <SDL_image.h>

//TODO: create a renderer
//TODO: store a list of sprites
//TODO: create a render loop and render list of sprites

NKEngine::NKEngine() {
    _sprites = new std::list<SDL_Rect *>;
    _textures = new std::list<SDL_Texture *>;
    _isPaused = false;
}

NKEngine::~NKEngine() {
    //TODO: clear all sprites memory;
    _sprites->clear();
    //TODO: clear all texture
    _textures->clear();
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

            int i = 0;
            for (const auto &sprite: *_sprites) {
                std::cout << sprite->h << std::endl;
                auto it = std::next(_textures->begin(), i);
                if (it == _textures->end()) {
                    std::cerr << "Error: Texture index out of bounds" << std::endl;
                    break;
                }

                SDL_Texture* texture = *it;
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, nullptr, sprite);
                SDL_RenderPresent(renderer);

                i++;
            }
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
    _textures->push_back(loadedTexture);
    return loadedTexture;
}

//Return a center-pivoted rect, oppose to the left-top corner pivoted provided by SDL2
SDL_Rect *NKEngine::CreateSprite(int positionX, int positionY, int width, int height) {
    //Center pivot
    positionX -= width / 2;
    positionY -= height / 2;
    SDL_Rect *sprite = new SDL_Rect(positionX, positionY, width, height);
    _sprites->push_back(sprite);
    return sprite;
}
