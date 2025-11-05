//
// Created by r1nge on 10/27/25.
//

#include "NKCollisionSystem.h"
#include "../NKEngine.h"
#include "../Components/NKColliderComponent.h"
#include "../Components/NKCollisionTag.h"

void NKCollisionSystem::Update(double deltaTime) {
    for (const auto &entityPair: engine->_components) {
        auto *colliderComponent = engine->GetComponent<NKColliderComponent>(entityPair.first);
        if (colliderComponent != nullptr) {
            for (const auto &entityPair2: engine->_components) {
                auto *otherColliderComponent = engine->GetComponent<NKColliderComponent>(entityPair2.first);
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

                    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
                        continue; // No collision
                    }

                    int depthX = std::min(rightA - leftB, rightB - leftA);
                    int depthY = std::min(bottomA - topB, bottomB - topA);

                    auto *rigidBodyComponent = engine->GetComponent<NKRigidBodyComponent>(entityPair.first);
                    if (rigidBodyComponent != nullptr) {
                        if (rigidBodyComponent->isKinematic == false) {
                            auto *position = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
                            if (position != nullptr) {
                                // Determine the axis of least penetration
                                if (depthX < depthY) {
                                    // Resolve along the X axis
                                    if (depthX > 5) {
                                        if (leftA < leftB) {
                                            // Push A to the left
                                            position->position->X->Move(engine->GetTick(), -depthX);
                                            rigidBodyComponent->velocity->X->currentValue = 0;
                                        } else {
                                            // Push A to the right
                                            position->position->X->Move(engine->GetTick(), depthX);
                                            rigidBodyComponent->velocity->X->currentValue = 0;
                                        }
                                    }
                                } else {
                                    // Resolve along the Y axis
                                    if (depthY > 5) {
                                        if (topA < topB) {
                                            // Push A up
                                            position->position->Y->Move(engine->GetTick(), -depthY);
                                            rigidBodyComponent->velocity->Y->currentValue = 0;
                                        } else {
                                            // Push A down
                                            position->position->Y->Move(engine->GetTick(), depthY);
                                            rigidBodyComponent->velocity->Y->currentValue = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }


                    engine->AddComponent(entityPair.first, std::make_unique<NKCollisionTag>());
                    engine->AddComponent(entityPair2.first, std::make_unique<NKCollisionTag>());
                    //std::cout << "Collided" << "\n";
                }
            }
        }
    }
}
