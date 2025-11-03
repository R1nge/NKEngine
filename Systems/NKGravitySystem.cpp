//
// Created by r1nge on 11/3/25.
//

#include "NKGravitySystem.h"
#include "../NKEngine.h"
#include "../Components/NKGravityComponent.h"
#include "../Components/NKReversiblePositionComponent.h"

void NKGravitySystem::Update(double deltaTime) {
    if (engine->IsRewinding() == false) {
        for (const auto &entityPair: engine->_components) {
            auto *positionComponent = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
            if (positionComponent != nullptr) {
                auto *gravityComponent = engine->GetComponent<NKGravityComponent>(entityPair.first);
                if (gravityComponent != nullptr) {
                    std::cout << "Engine tick " << engine->GetTick() << "\n";
                    positionComponent->position->Y->deltas[engine->GetTick()] += -gravityComponent->y;
                    positionComponent->position->Y->currentValue -= gravityComponent->y;
                }
            }
        }
    }
}
