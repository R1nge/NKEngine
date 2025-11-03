//
// Created by r1nge on 10/27/25.
//

#include "GameRewindTriggerSystem.h"
#include "../../NKEngine.h"
#include "../../Components/NKInputComponent.h"

void GameRewindTriggerSystem::Update(double deltaTime) {
    for (const auto &entityPair: engine->_components) {
        auto *inputComponent = engine->GetComponent<NKInputComponent>(entityPair.first);
        if (inputComponent != nullptr) {
            if (inputComponent->LastKey == SDL_SCANCODE_R) {
                engine->Rewind();
            }
        }
    }
}