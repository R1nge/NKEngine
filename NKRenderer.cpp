//
// Created by r1nge on 10/25/25.
//

#include "NKRenderer.h"
#include "NKEngine.h"

#include <SDL.h>
#include <SDL_image.h>

NKRenderer::NKRenderer(NKUuidGenerator *generator) : _uuidGenerator(generator) {
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

void NKRenderer::Render() {
    SDL_RenderClear(Renderer);

    int i = 0;
    for (const auto &pair: Sprites) {
        SDL_Texture *texture = pair.second->texture;
        SDL_RenderCopy(Renderer, texture, pair.second->inputTextureRect, pair.second->spriteRect);
        i++;
    }

    SDL_RenderPresent(Renderer);
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

SDL_Texture *NKRenderer::LoadTexture(SDL_Renderer *renderer, std::string path) {
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
std::shared_ptr<NKSprite> NKRenderer::CreateSprite(NKSpriteData *data) {
    //Center pivot
    data->positionX -= data->spriteWidth / 2;
    data->positionY -= data->spriteHeight / 2;
    std::shared_ptr<NKSprite> sprite = std::make_shared<NKSprite>(data->spriteWidth, data->spriteHeight,
                                                                  data->textureWidth, data->textureHeight,
                                                                  data->texturePositionX, data->texturePositionY,
                                                                  data->positionX, data->positionY);
    Sprites.emplace(_uuidGenerator->Generate(), sprite);
    return sprite;
}


std::shared_ptr<NKSprite> NKRenderer::CreateSprite(std::string path, NKSpriteData *data) {
    SDL_Texture *texture = LoadTexture(Renderer, path);
    std::shared_ptr<NKSprite> sprite = CreateSprite(data);
    SDL_SetTextureColorMod(texture, data->colorR, data->colorG, data->colorB);
    sprite->texture = texture;
    return sprite;
}
