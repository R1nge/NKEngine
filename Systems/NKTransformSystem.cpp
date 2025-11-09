//
// Created by r1nge on 10/26/25.
//

#include "NKTransformSystem.h"

#include <iostream>

#include "../NKEngine.h"


void NKTransformSystem::Init() {
    NKSystem::Init();
}

void NKTransformSystem::Update(double deltaTime) {
    if (engine->IsRewinding()) {
        Rewind(engine->GetTick());
    }
}

void NKTransformSystem::Rewind(int tick) {
    for (const auto &entityPair: engine->_components) {
        //TODO: f = engine->Filter->With<NKReversible>().Build;
        //TODO: for auto comp : f.Build()
        //TODO: comp.pos.x.rewind
        auto *component = engine->GetComponent<NKReversiblePositionComponent>(entityPair.first);
        if (component != nullptr) {
            component->position->X->Rewind(tick);
            component->position->Y->Rewind(tick);
        }
    }
}