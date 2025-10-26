//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKSPRITE_H
#define NKENGINE_NKSPRITE_H
#include <SDL_render.h>
#include <memory>

#include "NKReversibleInt.h"


class NKSprite {
public:
    NKSprite(int spriteWidth, int spriteHeight, int textureWidth, int textureHeight, int textureX, int textureY,int positionX, int positionY);
    SDL_Texture *texture;
    //TODO: instead of adjusting sprite rect directly make it repat after transform
    NKReversibleInt *position_x;
    NKReversibleInt *position_y;
    SDL_Rect *spriteRect;
    SDL_Rect *inputTextureRect;

    void Move(int tick, int deltaX, int deltaY);

    void Rewind(int tick);
};


#endif //NKENGINE_NKSPRITE_H
