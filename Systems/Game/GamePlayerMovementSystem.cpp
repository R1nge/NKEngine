//
// Created by r1nge on 10/27/25.
//

#include "GamePlayerMovementSystem.h"
#include "../../NKEngine.h"
#include "../../Components/NKInputComponent.h"
#include "../../Components/NKReversiblePositionComponent.h"
#include "../../Components/Game/GamePlayerTag.h"

void GamePlayerMovementSystem::Update(double deltaTime) {
    for (const auto &entityPair: engine->_components) {
        auto *playerTag = engine->getComponent<GamePlayerTag>(entityPair.first);
        if (playerTag != nullptr) {
            auto *movementComponent = engine->getComponent<NKReversiblePositionComponent>(entityPair.first);
            if (movementComponent != nullptr) {
                auto *inputComponent = engine->getComponent<NKInputComponent>(entityPair.first);
                auto tick = engine->GetTick();
                auto horizontal = static_cast<double>(inputComponent->HorizontalAxis) * static_cast<double>(4) *
                                  deltaTime;
                movementComponent->position->X->deltas.emplace(tick, horizontal);
                movementComponent->position->X->currentValue += horizontal;
            }
        }
    }
}
