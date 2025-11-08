//
// Created by r1nge on 10/27/25.
//

#include "GamePlayerMovementSystem.h"
#include "../../NKEngine.h"
#include "../../Components/NKCameraTag.h"
#include "../../Components/NKInputComponent.h"
#include "../../Components/NKReversiblePositionComponent.h"
#include "../../Components/Game/GamePlayerTag.h"

void GamePlayerMovementSystem::Update(double deltaTime) {
    if (engine->IsRewinding() == false) {
        for (const auto &entityPair: engine->_components) {
            auto *playerTag = engine->GetComponent<GamePlayerTag>(entityPair.first);
            if (playerTag != nullptr) {
                auto *rigidBodyComponent = engine->GetComponent<NKRigidBodyComponent>(entityPair.first);
                if (rigidBodyComponent != nullptr) {
                    auto *inputComponent = engine->GetComponent<NKInputComponent>(entityPair.first);
                    if (inputComponent != nullptr) {
                        auto horizontal = static_cast<double>(inputComponent->HorizontalAxis) * deltaTime;
                        auto vertical = static_cast<double>(inputComponent->VerticalAxis) * deltaTime;

                        auto diagonalFactor = 1 / SDL_sqrt(2);

                        if (horizontal != 0 || vertical != 0) {
                            horizontal *= diagonalFactor;
                            vertical *= diagonalFactor;
                        }

                        rigidBodyComponent->rigidBody->ApplyForceToCenter(b2Vec2(horizontal * 10, 0), true);
                        rigidBodyComponent->rigidBody->ApplyForceToCenter(b2Vec2(0, vertical * 10), true);
                    }
                }
            }
        }
    }
}
