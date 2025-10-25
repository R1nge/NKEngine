#include <iostream>
#include <string>

#include "MyGameEventSubscriber.h"
#include "NKEngine.h"

//TODO: engine generate id, store in a map by id, e.x renderer has a map of sprites, physics engine has a map of colliders, they are synced by id
//TODO: so, when engine destroys an object it destroys if everywhere it exists and releases resources
//TODO: engine -> renderer (sprite)
//TODO: engine -> phys engine (col)
//TODO: engine -> transform
//TODO: stored by the same id

//TODO: save engine settings into ini file https://github.com/dujingning/inicpp    (resolution, reference resolution, scale (width-height 0-1)

//TODO: store object in dict<uuid, NKObject>, destroy by id
//TODO: target fps + frametime + deltatime (add target fps to the config)


//TODO: transformation matrix (position, scale, rotation)
//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories
//TODO: C# binding jff

int main() {
    auto nk_engine = std::make_shared<NKEngine>();

    nk_engine->Renderer->CreateSprite("assets/space_invaders.png",
                                      new NKSpriteData(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20 * SCALE_X, 10 * SCALE_Y,
                                                       0, 0, 20, 10, 255, 255, 255));
    auto player = nk_engine->Renderer->CreateSprite("assets/space_invaders.png",
                                                    new NKSpriteData(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20 * SCALE_X,
                                                                     10 * SCALE_Y, 0, 48, 20, 10, 255, 255, 255));

    NKEventSubscriber *mySub = new MyGameEventSubscriber(player, nk_engine);
    nk_engine->EventDispatcher->AddSubscriber(mySub);

    std::cout << nk_engine->UuidGenerator->Generate();
    nk_engine->Update();

    return 0;
}
