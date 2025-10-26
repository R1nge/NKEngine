//
// Created by r1nge on 10/19/25.
//

#include "NKSprite.h"

NKSprite::NKSprite(int spriteWidth, int spriteHeight, int textureWidth, int textureHeight, int textureX, int textureY,
                   int positionX, int positionY) {
    spriteRect = new SDL_Rect(positionX, positionY, spriteWidth, spriteHeight);
    inputTextureRect = new SDL_Rect(textureX, textureY, textureWidth, textureHeight);
    position = new NKReversibleVector2Int(positionX, positionY);
}

void NKSprite::Move(int tick, int deltaX, int deltaY) {
    position->X->deltas.emplace(tick, deltaX);
    position->Y->deltas.emplace(tick, deltaY);
    position->X->currentValue += deltaX;
    position->Y->currentValue += deltaY;
    spriteRect->x = position->X->currentValue;
    spriteRect->y = position->Y->currentValue;
}

void NKSprite::Rewind(int tick) {
    if (position->X->deltas.contains(tick)) {
        auto deltaX = position->X->deltas.at(tick);
        position->X->currentValue -= deltaX;
        spriteRect->x = position->X->currentValue;
        position->X->deltas.erase(tick);
    }

    if (position->Y->deltas.contains(tick)) {
        auto deltaY = position->Y->deltas.at(tick);
        position->Y->currentValue -= deltaY;
        spriteRect->y = position->Y->currentValue;
        position->Y->deltas.erase(tick);
    }
}
