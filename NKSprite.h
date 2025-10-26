//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKSPRITE_H
#define NKENGINE_NKSPRITE_H
#include <SDL_render.h>
#include "NKReversibleVector2Int.h"


class NKSprite {
public:
    NKSprite(int spriteWidth, int spriteHeight, int textureWidth, int textureHeight, int textureX, int textureY,
             int positionX, int positionY);

    SDL_Texture *texture;
    NKReversibleVector2Int *position;
    SDL_Rect *spriteRect;
    SDL_Rect *inputTextureRect;

    void Move(int tick, int deltaX, int deltaY);

    void Rewind(int tick);
};


#endif //NKENGINE_NKSPRITE_H
