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
    for (const auto &entityPair: engine->_components) {
        auto *playerTag = engine->GetComponent<GamePlayerTag>(entityPair.first);
        if (playerTag != nullptr) {
            auto *movementComponent = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
            if (movementComponent != nullptr) {
                auto *inputComponent = engine->GetComponent<NKInputComponent>(entityPair.first);
                if (inputComponent != nullptr) {
                    auto tick = engine->GetTick();
                    auto horizontal = static_cast<double>(inputComponent->HorizontalAxis) * deltaTime;
                    auto vertical = static_cast<double>(inputComponent->VerticalAxis) * deltaTime;

                    auto diagonalFactor = 1 / SDL_sqrt(2);

                    if (horizontal != 0 || vertical != 0) {
                        horizontal *= diagonalFactor;
                        vertical *= diagonalFactor;
                        movementComponent->position->X->deltas.emplace(tick, horizontal);
                        movementComponent->position->X->currentValue += horizontal;
                        movementComponent->position->Y->deltas.emplace(tick, vertical);
                        movementComponent->position->Y->currentValue += vertical;
                    } else {
                        movementComponent->position->X->deltas.emplace(tick, horizontal);
                        movementComponent->position->X->currentValue += horizontal;
                        movementComponent->position->Y->deltas.emplace(tick, vertical);
                        movementComponent->position->Y->currentValue += vertical;
                    }

                    //std::cout << "Horizontal: " << horizontal << " Vertical: " << vertical << "\n";
                }
            }
        }
    }
}
