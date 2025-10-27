#include <algorithm>
#include <iostream>
#include <SDL_image.h>
#include <string>

#include "MyGameEventSubscriber.h"
#include "NKEngine.h"
#include "Components/NKCollisionComponent.h"
#include "Components/NKInputComponent.h"
#include "Components/NKRenderComponent.h"
#include "Components/NKReversiblePositionComponent.h"
#include "Components/Game/GamePlayerTag.h"
#include "Systems/NKCollisionResetSystem.h"
#include "Systems/NKCollisionSystem.h"
#include "Systems/NKCollisionTransformSyncSystem.h"
#include "Systems/NKInputSystem.h"
#include "Systems/NKTransformSystem.h"
#include "Systems/Game/GamePlayerMovementSystem.h"
#include "Systems/Game/RewindTriggerSystem.h"

//TODO: box collision system
//TODO: separate collision rect component, collision system
//TODO: so, they collided, add a tag that have both rects/object, later systems can use that to determine what to do


//TODO: game/scene coordinates (origin)
//TODO: camera

//TODO: target fps + frametime + deltatime (add target fps to the config) https://www.gafferongames.com/post/fix_your_timestep/
//TODO: update loops (fixed, update, lateUpdate) make 3 dicts + methods to add, execute system in separate loops

//TODO: look into that https://en.cppreference.com/w/cpp/language/modules.html

//TODO: save engine settings into ini file  (resolution, reference resolution, scale (width-height 0-1), debug (on/off))

//TODO: engine core -> callbacks -> modules -> callbacks -> developer

//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories


int main() {
    auto nk_engine = std::make_unique<NKEngine>();

    //Entities
    auto testEntity = nk_engine->CreateEntity();

    auto collider = nk_engine->CreateEntity();

    //Components
    nk_engine->AddComponent<NKReversiblePositionComponent>(
        testEntity, std::make_unique<NKReversiblePositionComponent>(10, 550));
    auto spriteComponent = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                  new NKSpriteData(10, 550, 100, 100, 10, 10, 10, 10));
    nk_engine->AddComponent<NKRenderComponent>(testEntity, std::move(spriteComponent));
    nk_engine->AddComponent<NKInputComponent>(testEntity, std::make_unique<NKInputComponent>());
    nk_engine->AddComponent<NKCollisionComponent>(testEntity, std::make_unique<NKCollisionComponent>(new SDL_Rect(50,50,100,100)));
    nk_engine->AddComponent<GamePlayerTag>(testEntity, std::make_unique<GamePlayerTag>());

    nk_engine->AddComponent<NKReversiblePositionComponent>(
        collider, std::make_unique<NKReversiblePositionComponent>(300, 550));
    auto spriteComponent2 = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                   new NKSpriteData(10, 550, 100, 100, 10, 10, 10, 10));
    nk_engine->AddComponent<NKRenderComponent>(collider, std::move(spriteComponent2));
    nk_engine->AddComponent<NKCollisionComponent>(collider, std::make_unique<NKCollisionComponent>(new SDL_Rect(300, 550, 100, 100)));

    //Systems
    nk_engine->AddSystem(0, std::make_unique<GamePlayerMovementSystem>());
    nk_engine->AddSystem(0, std::make_unique<RewindTriggerSystem>());
    nk_engine->AddSystem(0, std::make_unique<NKCollisionTransformSyncSystem>());
    nk_engine->AddSystem(0, std::make_unique<NKCollisionSystem>());
    //TODO: collision something system
    nk_engine->AddSystem(0, std::make_unique<NKCollisionResetSystem>());

    std::cout << nk_engine->UuidGenerator->Generate();

    nk_engine->PrintAllSystem();

    while (!nk_engine->Quitting()) {
        nk_engine->Update();
    }

    return 0;
}
