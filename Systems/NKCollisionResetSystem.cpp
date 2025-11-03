//
// Created by r1nge on 10/27/25.
//

#include "NKCollisionResetSystem.h"
#include "../NKEngine.h"
#include "../Components/NKCollisionTag.h"

void NKCollisionResetSystem::Update(double deltaTime) {
    for (const auto &entityPair: engine->_components) {
        auto *collisionTag = engine->GetComponent<NKCollisionTag>(entityPair.first);
        if (collisionTag != nullptr) {
            engine->RemoveComponent<NKCollisionTag>(entityPair.first);
        }
    }
}