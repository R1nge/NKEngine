//
// Created by r1nge on 11/5/25.
//

#include "NKTransformRigidBodySyncSystem.h"
#include "../NKEngine.h"
#include "../Components/NKReversiblePositionComponent.h"
#include "../Components/NKRigidBodyComponent.h"

void NKTransformRigidBodySyncSystem::Init() {
    NKSystem::Init();
    filter = new NKFilter(engine);
    filter->With<NKReversiblePositionComponent>()->With<NKRigidBodyComponent>();
    filter->Build();
}

void NKTransformRigidBodySyncSystem::Update(double deltaTime) {
    if (engine->IsRewinding() == true) {
        filter->Build();
        for (const auto &entity: filter->_entities) {
            auto *rigidbodyComponent = engine->GetComponent<NKRigidBodyComponent>(entity);
            engine->debug_renderer.camera_pos = b2Vec2(rigidbodyComponent->rigidBody->GetPosition().x,
                                                       rigidbodyComponent->rigidBody->GetPosition().y);
        }
        return;
    }
    filter->Build();
    for (const auto &entity: filter->_entities) {
        auto *positionComponent = engine->GetComponent<NKReversiblePositionComponent>(entity);
        auto *rigidbodyComponent = engine->GetComponent<NKRigidBodyComponent>(entity);
        engine->debug_renderer.camera_pos = b2Vec2(rigidbodyComponent->rigidBody->GetPosition().x,
                                                   rigidbodyComponent->rigidBody->GetPosition().y);

        positionComponent->position->X->previousValue = positionComponent->position->X->currentValue;
        positionComponent->position->Y->previousValue = positionComponent->position->Y->currentValue;


        positionComponent->position->X->currentValue = rigidbodyComponent->rigidBody->GetPosition().x;
        positionComponent->position->Y->currentValue = -rigidbodyComponent->rigidBody->GetPosition().y;

        auto tick = engine->GetTick();
        //Global Delta = current - start
        //Frame Delta = prev - current
        positionComponent->position->X->deltas[tick] =
                positionComponent->position->X->previousValue - positionComponent->position->X->currentValue;
        positionComponent->position->Y->deltas[tick] =
                positionComponent->position->Y->previousValue - positionComponent->position->Y->currentValue;
    }
}
