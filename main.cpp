#include <algorithm>
#include <iostream>
#include <SDL_image.h>
#include <string>

#include "MyGameEventSubscriber.h"
#include "NKEngine.h"
#include "Components/NKInputComponent.h"
#include "Components/NKRenderComponent.h"
#include "Components/NKReversiblePositionComponent.h"
#include "Components/Game/GamePlayerTag.h"
#include "Systems/NKInputSystem.h"
#include "Systems/NKTransformSystem.h"
#include "Systems/Game/GamePlayerMovementSystem.h"

//TODO: input system (horizontal, vertical, key)
//TODO: system order property (int)
//TODO: system groups (systems, order property)
//TODO: game/scene coordinates (origin)

//TODO: support 3 types of api? (ECS, event-driven, base class)????
//TODO: look into that https://en.cppreference.com/w/cpp/language/modules.html

//TODO: save engine settings into ini file  (resolution, reference resolution, scale (width-height 0-1)

//TODO: target fps + frametime + deltatime (add target fps to the config) https://www.gafferongames.com/post/fix_your_timestep/

//TODO: engine core -> callbacks -> modules -> callbacks -> developer

//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories


int main() {
    auto nk_engine = std::make_unique<NKEngine>();

    auto testEntity = nk_engine->CreateEntity();
    nk_engine->AddComponent<NKReversiblePositionComponent>(testEntity, std::make_unique<NKReversiblePositionComponent>(50, 50));
    auto spriteComponent = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                  new NKSpriteData(50, 50, 100, 100, 10, 10, 10, 10));
    nk_engine->AddComponent<NKRenderComponent>(testEntity, std::move(spriteComponent));
    nk_engine->AddComponent<NKInputComponent>(testEntity, std::make_unique<NKInputComponent>());

    nk_engine->AddSystem(std::make_unique<GamePlayerMovementSystem>());
    nk_engine->AddComponent<GamePlayerTag>(testEntity, std::make_unique<GamePlayerTag>());

    std::cout << nk_engine->UuidGenerator->Generate();
    while (true) {
        nk_engine->Update();
    }


    return 0;
}
