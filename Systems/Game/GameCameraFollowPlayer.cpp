//
// Created by r1nge on 10/29/25.
//

#include "GameCameraFollowPlayer.h"
#include "../../NKEngine.h"
#include "../../Components/NKCameraTag.h"
#include "../../Components/NKReversiblePositionComponent.h"
#include "../../Components/Game/GamePlayerTag.h"

void GameCameraFollowPlayer::Update() {
    NKSystem::Update();


    for (const auto &entityPair: engine->_components) {
        auto *cameraTag = engine->getComponent<NKCameraTag>(entityPair.first);
        if (cameraTag != nullptr) {
            auto *cameraTransform = engine->getComponent<NKReversiblePositionComponent>(entityPair.first);
            //cameraTransform->position->Y->currentValue -= 10;
            for (const auto &entityPair2: engine->_components) {
                auto *playerTag = engine->getComponent<GamePlayerTag>(entityPair2.first);
                if (playerTag != nullptr) {
                    auto *playerTransform = engine->getComponent<NKReversiblePositionComponent>(entityPair2.first);
                    cameraTransform->position->X->currentValue =
                            playerTransform->position->X->currentValue - SCREEN_WIDTH / 2;
                    cameraTransform->position->Y->currentValue =
                            playerTransform->position->Y->currentValue - SCREEN_HEIGHT / 2;
                }
            }
        }
    }
}
