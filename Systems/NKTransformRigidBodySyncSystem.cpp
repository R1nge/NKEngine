//
// Created by r1nge on 11/5/25.
//

#include "NKTransformRigidBodySyncSystem.h"
#include "../NKEngine.h"

void NKTransformRigidBodySyncSystem::Init() {
    NKSystem::Init();
    filter = new NKFilter(engine);
    filter->With<NKReversiblePositionComponent>()->With<NKRigidBodyComponent>();
    filter->Build();
}

void NKTransformRigidBodySyncSystem::Update(double deltaTime) {
    for (const auto &entity: filter->_entities) {
        auto *positionComponent = engine->GetComponent<NKReversiblePositionComponent>(entity);
        auto *rigidbodyComponent = engine->GetComponent<NKRigidBodyComponent>(entity);
        engine->debug_renderer.camera_pos = b2Vec2(rigidbodyComponent->rigidBody->GetPosition().x,
                                                   rigidbodyComponent->rigidBody->GetPosition().y);
        positionComponent->position->X->currentValue = rigidbodyComponent->rigidBody->GetPosition().x;
        positionComponent->position->Y->currentValue = -rigidbodyComponent->rigidBody->GetPosition().y;
    }
}
