//
// Created by r1nge on 11/3/25.
//

#include "NKGravitySystem.h"
#include "../NKEngine.h"
#include "../Components/NKCollisionTag.h"
#include "../Components/NKRigidBodyComponent.h"
#include "../Components/NKReversiblePositionComponent.h"

void NKGravitySystem::Update(double deltaTime) {
    if (engine->IsRewinding() == false) {
        for (const auto &entityPair: engine->_components) {
            auto *positionComponent = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
            if (positionComponent != nullptr) {
                auto *rigidbodyComponent = engine->GetComponent<NKRigidBodyComponent>(entityPair.first);
                if (rigidbodyComponent != nullptr) {
                    if (rigidbodyComponent->isKinematic == false) {
                        auto *collisionTag = engine->GetComponent<NKCollisionTag>(entityPair.first);
                        //std::cout << "Engine tick " << engine->GetTick() << "\n";
                        if (collisionTag == nullptr) {
                            positionComponent->position->Y->Move(engine->GetTick(),
                                                                 rigidbodyComponent->mass * static_cast<double>(9.81));
                        }
                    }
                }
            }
        }
    }
}
