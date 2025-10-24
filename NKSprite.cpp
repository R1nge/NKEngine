//
// Created by r1nge on 10/19/25.
//

#include "NKSprite.h"

NKSprite::NKSprite(int spriteWidth, int spriteHeight, int textureWidth, int textureHeight, int textureX, int textureY,int positionX, int positionY) {
    spriteRect = new SDL_Rect(positionX, positionY, spriteWidth, spriteHeight);
    inputTextureRect = new SDL_Rect(textureX, textureY, textureWidth, textureHeight);
}
