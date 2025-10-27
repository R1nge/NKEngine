//
// Created by r1nge on 10/27/25.
//

#include "NKSpriteCreator.h"

NKSpriteCreator::NKSpriteCreator(SDL_Renderer *renderer) {
    _renderer = renderer;
}

SDL_Texture *NKSpriteCreator::LoadTexture(std::string path) {
    SDL_Texture *loadedTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Create texture from surface pixels
        loadedTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
        if (loadedTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return loadedTexture;
}
