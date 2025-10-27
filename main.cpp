#include <algorithm>
#include <iostream>
#include <SDL_image.h>
#include <string>

#include "MyGameEventSubscriber.h"
#include "NKEngine.h"
#include "Components/NKRenderComponent.h"
#include "Components/NKReversiblePositionComponent.h"
#include "Systems/NKTransformSystem.h"

//TODO: Fix rewind (separate transform rewind system)???
//TODO: game/scene coordinates (origin)

//TODO: support 3 types of api? (ECS, event-driven, base class)????
//TODO: look into that https://en.cppreference.com/w/cpp/language/modules.html

//TODO: save engine settings into ini file  (resolution, reference resolution, scale (width-height 0-1)

//TODO: target fps + frametime + deltatime (add target fps to the config) https://www.gafferongames.com/post/fix_your_timestep/

//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories


int main() {
    auto nk_engine = std::make_unique<NKEngine>();
    auto transformSystem = std::make_unique<NKTransformSystem>();
    nk_engine->addSystem(std::move(transformSystem));

    auto testEntity = nk_engine->CreateEntity();
    nk_engine->AddComponent<NKReversiblePositionComponent>(testEntity, std::make_unique<NKReversiblePositionComponent>(50, 50));
    auto sprite = nk_engine->SpriteCreator->CreateSprite("assets/space_invaders.png",
                                                         new NKSpriteData(
                                                             50, 50, 100, 100, 10, 10, 10, 10, 255, 255, 255));
    nk_engine->AddComponent<NKRenderComponent>(testEntity, std::move(sprite));

    //nk_engine->Renderer->CreateSprite("assets/space_invaders.png",new NKSpriteData(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20 * SCALE_X, 10 * SCALE_Y,0, 0, 20, 10, 255, 255, 255));
    //auto player = nk_engine->Renderer->CreateSprite("assets/space_invaders.png",new NKSpriteData(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20 * SCALE_X,10 * SCALE_Y, 0, 48, 20, 10, 255, 255, 255));

    //NKEventSubscriber *mySub = new MyGameEventSubscriber(player, nk_engine);
    //nk_engine->EventDispatcher->AddSubscriber(mySub);

    std::cout << nk_engine->UuidGenerator->Generate();
    nk_engine->Update();

    return 0;
}
