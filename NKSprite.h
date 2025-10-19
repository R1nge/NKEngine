//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKSPRITE_H
#define NKENGINE_NKSPRITE_H
#include <SDL_render.h>


class NKSprite {
public:
    NKSprite(int width, int height);
    int Width;
    int Height;
    SDL_Texture *texture;
    SDL_Rect *dimensions;
};


#endif //NKENGINE_NKSPRITE_H
