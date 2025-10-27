//
// Created by r1nge on 10/26/25.
//

#include "NKTransformSystem.h"

#include <iostream>

#include "../NKEngine.h"


void NKTransformSystem::Update() {
    NKSystem::Update();
    if (engine->IsRewinding()) {
        Rewind(engine->GetTick());
    } else {
        Move(engine->GetTick(), 1, 1);
    }

    if (engine->GetLastKeyInput() == SDLK_r) {
        engine->Rewind();
    }
}

void NKTransformSystem::Move(int tick, int deltaX, int deltaY) {
    for (const auto &entityPair: engine->_components) {
        NKReversiblePositionComponent *component = engine->getComponent<
            NKReversiblePositionComponent>(entityPair.first);
        if (component != nullptr) {
            component->position->X->deltas.emplace(tick, deltaX);
            component->position->Y->deltas.emplace(tick, deltaY);
            component->position->X->currentValue += deltaX;
            component->position->Y->currentValue += deltaY;
            std::cout << "Move";
        }
    }
}

void NKTransformSystem::Rewind(int tick) {
    for (const auto &entityPair: engine->_components) {
        NKReversiblePositionComponent *component = engine->getComponent<
            NKReversiblePositionComponent>(entityPair.first);
        if (component != nullptr) {
            if (component->position->X->deltas.contains(tick)) {
                auto deltaX = component->position->X->deltas.at(tick);
                component->position->X->currentValue -= deltaX;
                component->position->X->deltas.erase(tick);
            }

            if (component->position->Y->deltas.contains(tick)) {
                auto deltaY = component->position->Y->deltas.at(tick);
                component->position->Y->currentValue -= deltaY;
                component->position->Y->deltas.erase(tick);
            }
        }
    }
}
