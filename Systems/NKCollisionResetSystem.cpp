//
// Created by r1nge on 10/27/25.
//

#include "NKCollisionResetSystem.h"
#include "../NKEngine.h"
#include "../Components/NKCollisionTag.h"

void NKCollisionResetSystem::Update() {
    for (const auto &entityPair: engine->_components) {
        auto *collisionTag = engine->getComponent<NKCollisionTag>(entityPair.first);
        if (collisionTag != nullptr) {
            engine->RemoveComponent<NKCollisionTag>(entityPair.first);
        }
    }
}
