//
// Created by r1nge on 10/26/25.
//

#include "NKTransformSystem.h"

#include <iostream>

#include "../NKEngine.h"
#include "../NKFilter.h"


void NKTransformSystem::Init() {
    NKSystem::Init();
    filter = new NKFilter(engine);
    filter->With<NKReversiblePositionComponent>()->With<NKRigidBodyComponent>();
    filter->Build();
}

void NKTransformSystem::Update(double deltaTime) {
    Rewind(engine->GetTick(), engine->IsRewinding());
}

void NKTransformSystem::Rewind(int tick, bool rewinding) {
    filter->Build();

    for (const auto &entity: filter->_entities) {
        auto *rigidBody = engine->GetComponent<NKRigidBodyComponent>(entity);
        if (rewinding) {
            rigidBody->rigidBody->Disable();
        } else {
            rigidBody->rigidBody->Enable();
        }
    }
    if (rewinding == true) {
        for (const auto &entity: filter->_entities) {
            auto *component = engine->GetComponent<NKReversiblePositionComponent>(entity);
            component->position->X->Rewind(tick);
            component->position->Y->Rewind(tick);
        }
    }
}
