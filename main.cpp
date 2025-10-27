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
#include "Systems/Game/GamePrintOnCollision.h"
#include "Systems/Game/GameRewindTriggerSystem.h"


//TODO: think about if I want to allow player to insert systems in between engine systems or allow to add any engine system???
//TODO: the latter is boilerplaty, also requires the basic understanding on how the engine should behave, so it's a no go

//TODO: store actions as commands that can be done/undone to be able to restore the game state
//TODO: if a ship has fired I can rewind the position and destroy the bullet, undo damage, reset timer, ect...

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
    nk_engine->AddSystem(0, std::make_unique<GameRewindTriggerSystem>());
    nk_engine->AddSystem(0, std::make_unique<NKCollisionTransformSyncSystem>());
    nk_engine->AddSystem(0, std::make_unique<NKCollisionSystem>());

    nk_engine->AddSystem(0, std::make_unique<GamePrintOnCollision>());

    nk_engine->AddSystem(0, std::make_unique<NKCollisionResetSystem>());

    std::cout << nk_engine->UuidGenerator->Generate();

    nk_engine->PrintAllSystem();

    while (!nk_engine->Quitting()) {
        nk_engine->Update();
    }

    return 0;
}
