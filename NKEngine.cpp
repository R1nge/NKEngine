//
// Created by r1nge on 10/19/25.
//

#include "NKEngine.h"

#include <memory>
#include <SDL_image.h>

#include "Systems/NKCollisionResetSystem.h"
#include "Systems/NKCollisionSystem.h"
#include "Systems/NKCollisionTransformSyncSystem.h"
#include "Systems/NKInputSystem.h"
#include "Systems/NKTransformSystem.h"

NKEngine::NKEngine() {
    EventDispatcher = std::make_unique<NKEventDispatcher>();
    UuidGenerator = std::make_unique<NKUuidGenerator>();
    Window = std::make_unique<NKWindow>();
    SpriteCreator = std::make_unique<NKSpriteCreator>(Window->Renderer);
    CoordinatesConverter = std::make_unique<NKCoordinatesConverter>();

    AddSystem(NKGroupType::NKTransform, std::make_unique<NKTransformSystem>());
    AddSystem(NKGroupType::NKInput, std::make_unique<NKInputSystem>());
    AddSystem(NKGroupType::NKRendering, std::make_unique<NKRenderingSystem>(Window.get()));
    AddSystem(NKGroupType::NKCollisionTransformSync, std::make_unique<NKCollisionTransformSyncSystem>());
    AddSystem(NKGroupType::NKCollision, std::make_unique<NKCollisionSystem>());
    AddSystem(NKGroupType::NKCollisionReset, std::make_unique<NKCollisionResetSystem>());

    _isPaused = false;
}

NKEngine::~NKEngine() {
    //SDL_DestroyRenderer(Renderer);
    //Renderer = nullptr;
    //SDL_DestroyWindow(Window);
    //Window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

void NKEngine::Update() {
    if (!_isPaused || !_isQuiting) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                Quit();
            }
        }

        _lastFrameTime = _currentFrameTime;
        _currentFrameTime = SDL_GetPerformanceCounter();
        _deltaTime = (_currentFrameTime - _lastFrameTime) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency());


        for (const auto &groupPair: _groups) {
            for (const auto &systemPair: groupPair.second) {
                systemPair.second->Update(_deltaTime);
            }
        }

        if (!_isRewinding) {
            _currentTick++;
        } else {
            ReverseAction(_currentTick);
            _currentTick--;
            if (_currentTick == 0) {
                _isRewinding = false;
            }
        }

        //std::cout << _deltaTime << "\n";
    }
}

void NKEngine::Rewind() {
    _isRewinding = true;
}

std::uint_fast32_t NKEngine::GetTick() const {
    return _currentTick;
}

int NKEngine::CreateEntity() {
    _entityId++;
    return _entityId;
}

bool NKEngine::IsRewinding() {
    return _isRewinding;
}

void NKEngine::Quit() {
    _isQuiting = true;
}

bool NKEngine::Quitting() {
    return _isQuiting;
}
