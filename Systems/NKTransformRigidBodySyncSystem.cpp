//
// Created by r1nge on 11/5/25.
//

#include "NKTransformRigidBodySyncSystem.h"
#include "../NKEngine.h"

void NKTransformRigidBodySyncSystem::Update(double deltaTime) {
    for (const auto &entityPair: engine->_components) {
        auto *positionComponent = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
        if (positionComponent != nullptr) {
            auto *rigidbodyComponent = engine->GetComponent<NKRigidBodyComponent>(entityPair.first);
            if (rigidbodyComponent != nullptr) {
                //TODO: scale to match the box2d
                positionComponent->position->X->currentValue = rigidbodyComponent->rigidBody->GetPosition().x;
                positionComponent->position->Y->currentValue =
                        -rigidbodyComponent->rigidBody->GetPosition().y * 32 - 125;
                std::cout << rigidbodyComponent->rigidBody->GetPosition().y;
            }
        }
    }
}
