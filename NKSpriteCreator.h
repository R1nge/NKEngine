//
// Created by r1nge on 10/27/25.
//

#ifndef NKENGINE_NKSPRITECREATOR_H
#define NKENGINE_NKSPRITECREATOR_H
#include <memory>
#include <SDL_render.h>
#include <SDL_image.h>

#include "Components/NKRenderComponent.h"


class NKSpriteCreator {
public:
    NKSpriteCreator(SDL_Renderer *renderer);

    SDL_Texture *LoadTexture(std::string path);

    std::unique_ptr<NKRenderComponent> CreateSprite(NKSpriteData *data);

    std::unique_ptr<NKRenderComponent> CreateSprite(std::string path, NKSpriteData *data);

private:
    SDL_Renderer *_renderer;
};


#endif //NKENGINE_NKSPRITECREATOR_H
