//
// Created by r1nge on 10/27/25.
//

#include "NKCollisionTransformSyncSystem.h"
#include "../NKEngine.h"
#include "../Components/NKReversiblePositionComponent.h"
#include "../Components/NKCollisionComponent.h"

void NKCollisionTransformSyncSystem::Update(double deltaTime) {
    for (const auto &entityPair: engine->_components) {
        auto *positionComponent = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
        if (positionComponent != nullptr) {
            auto *collisionComponent = engine->GetComponent<NKCollisionComponent>(entityPair.first);
            if (collisionComponent != nullptr) {
                collisionComponent->boundingBox->x = positionComponent->position->X->currentValue;
                collisionComponent->boundingBox->y = positionComponent->position->Y->currentValue;
            }
        }
    }
}
