//
// Created by r1nge on 10/27/25.
//

#include "NKColliderTransformSyncSystem.h"
#include "../NKEngine.h"
#include "../Components/NKReversiblePositionComponent.h"
#include "../Components/NKColliderComponent.h"

void NKColliderTransformSyncSystem::Update(double deltaTime) {
    for (const auto &entityPair: engine->_components) {
        auto *positionComponent = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
        if (positionComponent != nullptr) {
            auto *collisionComponent = engine->GetComponent<NKColliderComponent>(entityPair.first);
            if (collisionComponent != nullptr) {
                auto *renderComponent = engine->GetComponent<NKRenderComponent>(entityPair.first);
                if (renderComponent != nullptr) {
                    collisionComponent->boundingBox->x =
                            positionComponent->position->X->currentValue - static_cast<double>(renderComponent->
                                spriteRect->w) / static_cast<double>(2);
                    collisionComponent->boundingBox->y =
                            positionComponent->position->Y->currentValue - static_cast<double>(renderComponent->
                                spriteRect->h) / static_cast<double>(2);
                } else {
                    collisionComponent->boundingBox->x = positionComponent->position->X->currentValue;
                    collisionComponent->boundingBox->y = positionComponent->position->Y->currentValue;
                }
            }
        }
    }
}
