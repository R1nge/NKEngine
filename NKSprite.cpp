//
// Created by r1nge on 10/19/25.
//

#include "NKSprite.h"

NKSprite::NKSprite(int spriteWidth, int spriteHeight, int textureWidth, int textureHeight, int textureX, int textureY,
                   int positionX, int positionY) {
    spriteRect = new SDL_Rect(positionX, positionY, spriteWidth, spriteHeight);
    inputTextureRect = new SDL_Rect(textureX, textureY, textureWidth, textureHeight);
    transform = new NKReversiblePositionComponent(positionX, positionY);
}

//TODO: make movable tranform component
void NKSprite::Move(int tick, int deltaX, int deltaY) {
    //transform->Move(tick, deltaX, deltaY);
    spriteRect->x = transform->position->X->currentValue;
    spriteRect->y = transform->position->Y->currentValue;
}

void NKSprite::Rewind(int tick) {
    if (transform->position->X->deltas.contains(tick)) {
        auto deltaX = transform->position->X->deltas.at(tick);
        transform->position->X->currentValue -= deltaX;
        spriteRect->x = transform->position->X->currentValue;
        transform->position->X->deltas.erase(tick);
    }

    if (transform->position->Y->deltas.contains(tick)) {
        auto deltaY = transform->position->Y->deltas.at(tick);
        transform->position->Y->currentValue -= deltaY;
        spriteRect->y = transform->position->Y->currentValue;
        transform->position->Y->deltas.erase(tick);
    }
}
