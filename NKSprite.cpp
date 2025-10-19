//
// Created by r1nge on 10/19/25.
//

#include "NKSprite.h"

NKSprite::NKSprite(int width, int height) {
    dimensions = new SDL_Rect();
    dimensions->w = width;
    dimensions->h = height;
}
