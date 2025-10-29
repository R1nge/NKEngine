libs:  
https://github.com/libsdl-org/SDL/tree/SDL2  
https://github.com/mariusbancila/stduuid  
https://github.com/brofield/simpleini

After finishing basic stuff and creating a fully featured space invaders game I have to decide what to do next:  
1. Make time rewind that's build into the engine...Well, if I am already going as far as rewinding time, then why not to add all kinds of time-manipulation?
2. time rewind  
3. time slowdown/speedup  
4. time stop  
5. also, it should be possible to independently affect entities. Like, have groups that can be affected differently? Like...A tag/flag system of some sort. So that the developer would be able to change it during runtime.

Refs:  
https://powerlisting.fandom.com/wiki/Time_Manipulation


Also, NKEngine sounds lame...  
Chronos?  
Jikan?  
Saturn?  
Norns?  
(  
Urd – Representing the past, Urd is often depicted as the eldest of the Norns. She embodies the events and actions that have already transpired, influencing the present and future.  
Verdandi – Symbolizing the present, Verdandi plays a crucial role in weaving the current threads of life. She is the active force, reflecting the choices and actions that define existence at any given moment.  
Skuld – The youngest sister, Skuld represents the future. Her role is to determine the potential outcomes and paths that lie ahead, reminding all beings of the uncertainty and possibilities that await.  
)  
移動時間?  


Example:
```cpp
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
```

Features:
- [x] Texture loading
- [x] Sprites
- [x] Reversible int
- [x] Reversible vector2Int
- [x] Reversible position
- [x] Coordinate system
- [x] ECS
- [x] Input system
- [x] Rendering system
- [x] AABB collision
- [x] Camera
- [x] Reversible actions
- [ ] Screen to world/World to screen
- [x] Delta time
- [ ] Fixed update
- [ ] Ini settings file
- [ ] Dear ImGui integration
