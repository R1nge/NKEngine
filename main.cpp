#include <algorithm>
#include <iostream>
#include <SDL_image.h>
#include <string>

#include "GameTestAction.h"
#include "NKEngine.h"
#include "Components/NKCameraTag.h"
#include "Components/NKCollisionComponent.h"
#include "Components/NKInputComponent.h"
#include "Components/NKRenderComponent.h"
#include "Components/NKReversiblePositionComponent.h"
#include "Components/Game/GamePlayerTag.h"
#include "Systems/Game/GamePlayerMovementSystem.h"
#include "Systems/Game/GamePrintOnCollision.h"
#include "Systems/Game/GameRewindTriggerSystem.h"

//https://martin-fieber.de/blog/gui-development-with-cpp-sdl2-and-dear-imgui/


//TODO: camera
//TODO: to simulate camera viewport - offset all transform components by camera position???
//TODO: renderer should take camera position into account and only move the render position, so it's cameraPos + transformPos

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
    auto cameraEntity = nk_engine->CreateEntity();
    auto testEntity = nk_engine->CreateEntity();

    auto collider = nk_engine->CreateEntity();

    //Components
    nk_engine->AddComponent<NKReversiblePositionComponent>(cameraEntity,
                                                           std::make_unique<NKReversiblePositionComponent>(
                                                               -SCREEN_WIDTH / 2, +SCREEN_HEIGHT / 2));
    nk_engine->AddComponent<NKCameraTag>(cameraEntity, std::make_unique<NKCameraTag>());

    nk_engine->AddComponent<NKReversiblePositionComponent>(
        testEntity, std::make_unique<NKReversiblePositionComponent>(0, 0));
    auto spriteComponent = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                  new NKSpriteData(10, 550, 100, 100, 10, 10, 10, 10));
    nk_engine->AddComponent<NKRenderComponent>(testEntity, std::move(spriteComponent));
    nk_engine->AddComponent<NKInputComponent>(testEntity, std::make_unique<NKInputComponent>());
    nk_engine->AddComponent<NKCollisionComponent>(testEntity, std::make_unique<NKCollisionComponent>(new SDL_Rect(50,50,100,100)));
    nk_engine->AddComponent<GamePlayerTag>(testEntity, std::make_unique<GamePlayerTag>());

    nk_engine->AddComponent<NKReversiblePositionComponent>(
        collider, std::make_unique<NKReversiblePositionComponent>(100, 100));
    auto spriteComponent2 = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                   new NKSpriteData(
                                                                       10, 250, 100, 100, 10, 10, 10, 10, 0, 255, 0));
    nk_engine->AddComponent<NKRenderComponent>(collider, std::move(spriteComponent2));
    nk_engine->AddComponent<NKCollisionComponent>(collider, std::make_unique<NKCollisionComponent>(new SDL_Rect(300, 550, 100, 100)));

    //Systems
    nk_engine->AddSystem(NKGroupType::NKTransform, std::make_unique<GamePlayerMovementSystem>());
    nk_engine->AddSystem(NKGroupType::NKTransform, std::make_unique<GameRewindTriggerSystem>());
    nk_engine->AddSystem(NKGroupType::NKCollision, std::make_unique<GamePrintOnCollision>());

    //Actions
    nk_engine->AddAction(10, std::make_unique<GameTestAction>());

    std::cout << nk_engine->UuidGenerator->Generate();

    nk_engine->PrintAllSystem();

    while (!nk_engine->Quitting()) {
        nk_engine->Update();
    }

    return 0;
}
