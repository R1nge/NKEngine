//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKRENDERCOMPONENT_H
#define NKENGINE_NKRENDERCOMPONENT_H
#include <SDL_render.h>

#include "NKComponent.h"
#include "../NKSpriteData.h"


struct NKRenderComponent : NKComponent {
    NKRenderComponent(SDL_Texture *Texture, SDL_Rect *SpriteRect, SDL_Rect *TextureRect, NKSpriteData *data);

    SDL_Texture *texture;
    SDL_Rect *spriteRect;
    SDL_Rect *textureRect;
    NKSpriteData *data;
};


#endif //NKENGINE_NKRENDERCOMPONENT_H
