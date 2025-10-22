//
// Created by r1nge on 10/19/25.
//

#include "NKSprite.h"

NKSprite::NKSprite(int width, int height, int positionX, int positionY) {
    dimensions = new SDL_Rect(positionX, positionY, width, height);
    dimensions->w = width;
    dimensions->h = height;
    dimensions->x = positionX;
    dimensions->y = positionY;
}
