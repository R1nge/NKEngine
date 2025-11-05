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
                if (rigidbodyComponent->isKinematic == false) {
                    positionComponent->position->X->Move(engine->GetTick(),
                                                         rigidbodyComponent->velocity->X->currentValue);
                    positionComponent->position->Y->Move(engine->GetTick(),
                                                         rigidbodyComponent->velocity->Y->currentValue);
                }
            }
        }
    }
}
