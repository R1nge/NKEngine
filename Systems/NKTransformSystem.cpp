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
    filter->With<NKReversiblePositionComponent>();
    filter->Build();
}

void NKTransformSystem::Update(double deltaTime) {
    if (engine->IsRewinding()) {
        Rewind(engine->GetTick());
    }
}

void NKTransformSystem::Rewind(int tick) {
    filter->Build();
    for (const auto &entity: filter->_entities) {
        auto *component = engine->GetComponent<NKReversiblePositionComponent>(entity);
        component->position->X->Rewind(tick);
        component->position->Y->Rewind(tick);
    }
}
