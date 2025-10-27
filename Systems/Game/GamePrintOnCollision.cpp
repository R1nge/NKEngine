//
// Created by r1nge on 10/28/25.
//

#include "GamePrintOnCollision.h"
#include "../../NKEngine.h"
#include "../../Components/NKCollisionTag.h"

void GamePrintOnCollision::Update() {
    for (const auto &entityPair: engine->_components) {
        auto *collisionTag = engine->getComponent<NKCollisionTag>(entityPair.first);
        if (collisionTag != nullptr) {
            std::cout << "\n Printing";
        }
    }
}
