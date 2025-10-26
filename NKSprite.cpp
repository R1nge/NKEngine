//
// Created by r1nge on 10/19/25.
//

#include "NKSprite.h"

NKSprite::NKSprite(int spriteWidth, int spriteHeight, int textureWidth, int textureHeight, int textureX, int textureY,
                   int positionX, int positionY) {
    spriteRect = new SDL_Rect(positionX, positionY, spriteWidth, spriteHeight);
    inputTextureRect = new SDL_Rect(textureX, textureY, textureWidth, textureHeight);
    position_x = new NKReversibleInt();
    position_x->startValue = positionX;
    position_x->currentValue = positionX;
    position_y = new NKReversibleInt();
    position_y->startValue = positionY;
    position_y->currentValue = positionY;
}

void NKSprite::Move(int tick, int deltaX, int deltaY) {
    position_x->deltas.emplace(tick, deltaX);
    position_y->deltas.emplace(tick, deltaY);
    position_x->currentValue += deltaX;
    position_y->currentValue += deltaY;
    spriteRect->x = position_x->currentValue;
    spriteRect->y = position_y->currentValue;
}

void NKSprite::Rewind(int tick) {
    if (position_x->deltas.contains(tick)) {
        auto deltaX = position_x->deltas.at(tick);
        position_x->currentValue -= deltaX;
        spriteRect->x = position_x->currentValue;
        //TODO: reset
    }

    if (position_y->deltas.contains(tick)) {
        auto deltaY = position_y->deltas.at(tick);
        position_y->currentValue -= deltaY;
        spriteRect->y = position_y->currentValue;
        //TODO: reset
    }
}
