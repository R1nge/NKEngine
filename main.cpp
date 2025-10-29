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
#include "Systems/Game/GameCameraFollowPlayer.h"
#include "Systems/Game/GamePlayerMovementSystem.h"
#include "Systems/Game/GamePrintOnCollision.h"
#include "Systems/Game/GameRewindTriggerSystem.h"

//TODO: screen to world/world to screen


//TODO: target fps + (add target fps to the config) https://www.gafferongames.com/post/fix_your_timestep/
//TODO: update loops (fixed, update) make 2 dicts + methods to add, execute system in separate loops
//TODO: https://thenumb.at/cpp-course/sdl2/08/08.html
//TODO: do the same for the actions???

//TODO: create Filter.With/Filter.Without

//TODO: make input independent of the selected input language

//TODO: save engine settings into ini file  (resolution, reference resolution, scale (width-height 0-1), debug (on/off))

//TODO: dear Imgui
// https://martin-fieber.de/blog/gui-development-with-cpp-sdl2-and-dear-imgui/
// https://github.com/Green-Sky/imgui_entt_entity_editor/tree/master
//TODO: make UI ecs based

//TODO: sld2 cmake clone
//TODO: resolve headers (src, includes...)
//TODO: look into that https://en.cppreference.com/w/cpp/language/modules.html


//TODO: engine core -> callbacks -> modules -> callbacks -> developer

//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories


int main() {
    auto nk_engine = std::make_unique<NKEngine>();

    //Entities
    auto cameraEntity = nk_engine->CreateEntity();
    auto playerEntity = nk_engine->CreateEntity();

    auto collider = nk_engine->CreateEntity();

    //Components
    nk_engine->AddComponent<NKReversiblePositionComponent>(cameraEntity,
                                                           std::make_unique<NKReversiblePositionComponent>(
                                                               -SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2)));
    nk_engine->AddComponent<NKCameraTag>(cameraEntity, std::make_unique<NKCameraTag>());

    nk_engine->AddComponent<NKReversiblePositionComponent>(
        playerEntity, std::make_unique<NKReversiblePositionComponent>(0, 0));
    auto spriteComponent = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                  new NKSpriteData(10, 550, 100, 100, 10, 10, 10, 10));
    nk_engine->AddComponent<NKRenderComponent>(playerEntity, std::move(spriteComponent));
    nk_engine->AddComponent<NKInputComponent>(playerEntity, std::make_unique<NKInputComponent>());
    nk_engine->AddComponent<NKCollisionComponent>(playerEntity,
                                                  std::make_unique<
                                                      NKCollisionComponent>(new SDL_Rect(50, 50, 100, 100)));
    nk_engine->AddComponent<GamePlayerTag>(playerEntity, std::make_unique<GamePlayerTag>());

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
    nk_engine->AddSystem(NKGroupType::NKTransform, std::make_unique<GameCameraFollowPlayer>());

    //Actions
    nk_engine->AddAction(10, std::make_unique<GameTestAction>());

    std::cout << nk_engine->UuidGenerator->Generate();

    nk_engine->PrintAllSystem();

    while (!nk_engine->Quitting()) {
        nk_engine->Update();
    }

    return 0;
}
