#include <algorithm>
#include <iostream>
#include <SDL_image.h>
#include <string>

#include "MyGameEventSubscriber.h"
#include "NKEngine.h"
#include "Components/NKRenderComponent.h"
#include "Components/NKReversiblePositionComponent.h"
#include "Systems/NKTransformSystem.h"

//TODO: rendering system that uses transform component
//TODO: game/scene coordinates

//TODO: support 3 types of api? (ECS, event-driven, base class)????
//TODO: look into that https://en.cppreference.com/w/cpp/language/modules.html

//TODO: save engine settings into ini file https://github.com/dujingning/inicpp    (resolution, reference resolution, scale (width-height 0-1)

//TODO: target fps + frametime + deltatime (add target fps to the config)

//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories


int main() {
    auto nk_engine = std::make_shared<NKEngine>();
    auto transformSystem = std::make_unique<NKTransformSystem>();
    nk_engine->addSystem(std::move(transformSystem));

    auto testEntity = nk_engine->CreateEntity();
    nk_engine->AddComponent<NKReversiblePositionComponent>(testEntity, std::make_unique<NKReversiblePositionComponent>(50, 50));
    //TODO: load textures
    //auto player = LoadTexture(nk_engine->)
    auto playerTexture = new SDL_Rect(50, 50, 100, 100);
    auto playerSprite = new SDL_Rect(50, 50, 100, 100);

    auto texture = nk_engine->Window->LoadTexture("assets/space_invaders.png");
    nk_engine->AddComponent<NKRenderComponent>(
        testEntity, std::make_unique<NKRenderComponent>(texture, playerSprite, playerTexture));

    //nk_engine->Renderer->CreateSprite("assets/space_invaders.png",new NKSpriteData(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20 * SCALE_X, 10 * SCALE_Y,0, 0, 20, 10, 255, 255, 255));
    //auto player = nk_engine->Renderer->CreateSprite("assets/space_invaders.png",new NKSpriteData(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20 * SCALE_X,10 * SCALE_Y, 0, 48, 20, 10, 255, 255, 255));

    //NKEventSubscriber *mySub = new MyGameEventSubscriber(player, nk_engine);
    //nk_engine->EventDispatcher->AddSubscriber(mySub);

    std::cout << nk_engine->UuidGenerator->Generate();
    nk_engine->Update();

    return 0;
}
