//
// Created by r1nge on 10/29/25.
//

#include "GameCameraFollowPlayer.h"
#include "../../NKEngine.h"
#include "../../Components/NKCameraTag.h"
#include "../../Components/NKReversiblePositionComponent.h"
#include "../../Components/Game/GamePlayerTag.h"

void GameCameraFollowPlayer::Update(double deltaTime) {
    for (const auto &entityPair: engine->_components) {
        auto *cameraTag = engine->GetComponent<NKCameraTag>(entityPair.first);
        if (cameraTag != nullptr) {
            auto *cameraTransform = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
            //cameraTransform->position->Y->currentValue -= 10;
            for (const auto &entityPair2: engine->_components) {
                auto *playerTag = engine->GetComponent<GamePlayerTag>(entityPair2.first);
                if (playerTag != nullptr) {
                    auto *playerTransform = engine->GetComponent<NKReversiblePositionComponent>(entityPair2.first);
                    cameraTransform->position->X->currentValue =
                            playerTransform->position->X->currentValue;
                    cameraTransform->position->Y->currentValue =
                            playerTransform->position->Y->currentValue;
                }
            }
        }
    }
}
