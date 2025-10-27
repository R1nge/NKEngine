//
// Created by r1nge on 10/19/25.
//

#include "NKEngine.h"

#include <memory>
#include <SDL_image.h>

#include "Systems/NKInputSystem.h"
#include "Systems/NKTransformSystem.h"

NKEngine::NKEngine() {
    EventDispatcher = std::make_unique<NKEventDispatcher>();
    UuidGenerator = std::make_unique<NKUuidGenerator>();
    Window = std::make_unique<NKWindow>();
    SpriteCreator = std::make_unique<NKSpriteCreator>(Window->Renderer);
    AddSystem(std::make_unique<NKTransformSystem>());
    AddSystem(std::make_unique<NKInputSystem>());
    AddSystem(std::make_unique<NKRenderingSystem>(Window.get()));
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
    for (const auto &systemPair: _systems) {
        if (!_isPaused) {
            systemPair.second->Update();
        }
    }

    if (!_isRewinding) {
        _currentTick++;
    } else {
        _currentTick--;
        if (_currentTick == 0) {
            _isRewinding = false;
        }
    }
}

void NKEngine::Rewind() {
    _isRewinding = true;
}

int NKEngine::GetTick() const {
    return _currentTick;
}

int NKEngine::CreateEntity() {
    _entityId++;
    return _entityId;
}

bool NKEngine::IsRewinding() {
    return _isRewinding;
}
