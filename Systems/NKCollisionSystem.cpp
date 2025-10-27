//
// Created by r1nge on 10/27/25.
//

#include "NKCollisionSystem.h"
#include "../NKEngine.h"
#include "../Components/NKCollisionComponent.h"
#include "../Components/NKCollisionTag.h"

void NKCollisionSystem::Update() {
    for (const auto &entityPair: engine->_components) {
        auto *colliderComponent = engine->getComponent<NKCollisionComponent>(entityPair.first);
        if (colliderComponent != nullptr) {
            for (const auto &entityPair2: engine->_components) {
                auto *otherColliderComponent = engine->getComponent<NKCollisionComponent>(entityPair2.first);
                if (otherColliderComponent != nullptr) {
                    //Skip self
                    if (colliderComponent == otherColliderComponent) {
                        //std::cout << "\n Skipping self";
                        continue;
                    }

                    //Calculate the sides of rect A
                    int leftA = colliderComponent->boundingBox->x;
                    int rightA = colliderComponent->boundingBox->x + colliderComponent->boundingBox->w;
                    int topA = colliderComponent->boundingBox->y;
                    int bottomA = colliderComponent->boundingBox->y + colliderComponent->boundingBox->h;

                    //Calculate the sides of rect B
                    int leftB = otherColliderComponent->boundingBox->x;
                    int rightB = otherColliderComponent->boundingBox->x + otherColliderComponent->boundingBox->w;
                    int topB = otherColliderComponent->boundingBox->y;
                    int bottomB = otherColliderComponent->boundingBox->y + otherColliderComponent->boundingBox->h;

                    if (bottomA <= topB) {
                        continue;
                    }

                    if (topA >= bottomB) {
                        continue;
                    }

                    if (rightA <= leftB) {
                        continue;
                    }

                    if (leftA >= rightB) {
                        continue;
                    }

                    engine->AddComponent(entityPair.first, std::make_unique<NKCollisionTag>());
                    engine->AddComponent(entityPair2.first, std::make_unique<NKCollisionTag>());
                    //std::cout << "Collided" << "\n";
                }
            }
        }
    }
}
