//
// Created by r1nge on 10/26/25.
//

#include "NKTransformSystem.h"

void NKTransformSystem::Move(int tick, int deltaX, int deltaY) {
/*
    position->X->deltas.emplace(tick, deltaX);
    position->Y->deltas.emplace(tick, deltaY);
    position->X->currentValue += deltaX;
    position->Y->currentValue += deltaY;
    */
}

void NKTransformSystem::Rewind(int tick) {
    /*
    if (position->X->deltas.contains(tick)) {
        auto deltaX = position->X->deltas.at(tick);
        position->X->currentValue -= deltaX;
        position->X->deltas.erase(tick);
    }

    if (position->Y->deltas.contains(tick)) {
        auto deltaY = position->Y->deltas.at(tick);
        position->Y->currentValue -= deltaY;
        position->Y->deltas.erase(tick);
    }
    */
}
