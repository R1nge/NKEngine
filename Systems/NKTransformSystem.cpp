//
// Created by r1nge on 10/26/25.
//

#include "NKTransformSystem.h"

#include <iostream>

#include "../NKEngine.h"


void NKTransformSystem::Update(double deltaTime) {
    if (engine->IsRewinding()) {
        Rewind(engine->GetTick());
    }
}

void NKTransformSystem::Move(int tick, int deltaX, int deltaY) {
    for (const auto &entityPair: engine->_components) {
        auto *positionComponent = engine->getComponent<NKReversiblePositionComponent>(entityPair.first);
        if (positionComponent != nullptr) {
            positionComponent->position->X->deltas.emplace(tick, deltaX);
            positionComponent->position->Y->deltas.emplace(tick, deltaY);
            positionComponent->position->X->currentValue += deltaX;
            positionComponent->position->Y->currentValue += deltaY;
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
