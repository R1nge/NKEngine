#include <algorithm>
#include <iostream>
#include <string>

#include "box2cpp.h"
#include "GameTestAction.h"
#include "NKEngine.h"
#include "Components/Game/GamePlayerTag.h"
#include "Systems/Game/GameCameraFollowPlayer.h"
#include "Systems/Game/GamePlayerMovementSystem.h"
#include "Systems/Game/GameRewindTriggerSystem.h"

//TODO: create a rigidbody + shape creators
//TODO: rewind rigidbody????? (maybe disable it and reset velocity on rewind, then rewind transform??)

//TODO: create Filter.With/Filter.Without
//TODO: store filters in map by component type
//When building a filter = clear list, iterate over all entities, add
//When using filter -> return a list with components to iterate over


//TODO: create a shadow that repeats actions on rewind




//TODO: orthogonal 2d projection??

//TODO: make input independent of the selected input language SDL scancodes SDL3???

//TODO: target fps + (add target fps to the config) https://www.gafferongames.com/post/fix_your_timestep/
//TODO: update loops (fixed, update) make 2 dicts + methods to add, execute system in separate loops
//TODO: https://thenumb.at/cpp-course/sdl2/08/08.html
//TODO: do the same for the actions???

//TODO: save engine settings into ini file  (resolution, reference resolution, scale (width-height 0-1), debug (on/off))
//TODO: sdl2 dll
//TODO: dear Imgui dll
// https://martin-fieber.de/blog/gui-development-with-cpp-sdl2-and-dear-imgui/
// https://github.com/Green-Sky/imgui_entt_entity_editor/tree/master
//TODO: make UI ecs based???

//TODO: engine core -> callbacks -> modules -> callbacks -> developer


int main() {
    auto nk_engine = std::make_unique<NKEngine>();

    //Entities
    auto playerEntity = nk_engine->CreateEntity();

    auto collider = nk_engine->CreateEntity();

    auto floor = nk_engine->CreateEntity();
    auto spriteComponent3 = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                   new NKSpriteData(
                                                                       10, 550, 500, 50, 10, 10, 10, 10, 1));
    nk_engine->AddComponent(floor, std::move(spriteComponent3));
    nk_engine->AddComponent(floor, std::make_unique<NKReversiblePositionComponent>(0, 0));

    //Components
    nk_engine->AddComponent<NKReversiblePositionComponent>(
        playerEntity, std::make_unique<NKReversiblePositionComponent>(0, 300));
    auto spriteComponent = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                  new NKSpriteData(
                                                                      10, 550, 100, 100, 10, 10, 10, 10, 1));
    nk_engine->AddComponent<NKRenderComponent>(playerEntity, std::move(spriteComponent));

    nk_engine->AddComponent<NKInputComponent>(playerEntity, std::make_unique<NKInputComponent>());
    nk_engine->AddComponent<GamePlayerTag>(playerEntity, std::make_unique<GamePlayerTag>());


    nk_engine->AddComponent<NKReversiblePositionComponent>(
        collider, std::make_unique<NKReversiblePositionComponent>(100, 50));
    auto spriteComponent2 = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                                   new NKSpriteData(
                                                                       10, 250, 100, 100, 10, 10, 10, 10, 0, 0, 255,
                                                                       0));
    nk_engine->AddComponent<NKRenderComponent>(collider, std::move(spriteComponent2));

    //Systems
    nk_engine->AddSystem(NKGroupType::NKTransform, std::make_unique<GamePlayerMovementSystem>());
    //nk_engine->AddSystem(NKGroupType::NKInput, std::make_unique<GameRewindTriggerSystem>());
    //nk_engine->AddSystem(NKGroupType::NKCollision, std::make_unique<GamePrintOnCollision>());
    nk_engine->AddSystem(NKGroupType::NKTransform, std::make_unique<GameCameraFollowPlayer>());

    //Actions
    nk_engine->AddAction(10, std::make_unique<GameTestAction>());

    std::cout << "\n" << nk_engine->UuidGenerator->Generate();

    nk_engine->PrintAllSystem();

    //nk_engine->AudioPlayer->LoadSong("assets/Music.mp3", "test1");
    //nk_engine->AudioPlayer->PlaySong("test1");
    //nk_engine->AudioPlayer->SetMusicVolume(100);
    //nk_engine->AudioPlayer->ReplaceCurrentSong("assets/Music2.mp3", "test2");

    b2::Body::Params rigidBodyParent;
    rigidBodyParent.type = b2_dynamicBody;

    b2::Body rigidBody = nk_engine->World.CreateBody(b2::OwningHandle, rigidBodyParent);


    rigidBody.CreateShape(
        b2::DestroyWithParent,
        b2::Shape::Params{},
        b2MakeBox(1, 1)
        //b2Circle{.center = b2Vec2(), .radius = 3}
    );
    nk_engine->AddComponent<NKRigidBodyComponent>(playerEntity, std::make_unique<NKRigidBodyComponent>(&rigidBody));

    rigidBody.ApplyForceToCenter(b2Vec2(1000, -100000), true);

    b2::Body::Params staticParent;
    staticParent.type = b2_staticBody;
    staticParent.position = b2Vec2(0, -1400);

    b2::Body staticBody = nk_engine->World.CreateBody(b2::OwningHandle, staticParent);

    staticBody.CreateShape(
        b2::DestroyWithParent,
        b2::Shape::Params{},
        b2MakeBox(100, 1)
    );

    while (!nk_engine->Quitting()) {
        nk_engine->Update();
    }

    return 0;
}
