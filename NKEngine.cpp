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

    AddSystem(1, std::make_unique<NKTransformSystem>());
    AddSystem(2, std::make_unique<NKInputSystem>());
    AddSystem(3, std::make_unique<NKRenderingSystem>(Window.get()));
    AddSystem(4, std::make_unique<NKCollisionTransformSyncSystem>());
    AddSystem(5, std::make_unique<NKCollisionSystem>());
    AddSystem(6, std::make_unique<NKCollisionResetSystem>());

    //TODO: what if instead of letting player to put a system before one I would store all engine systems in separate group starting from 1
    //TODO: 0 - before transform, 1 - after transform before input, 2 - after input before rendering and so on...
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
    for (const auto &groupPair: _groups) {
        for (const auto &systemPair: groupPair.second) {
            if (!_isPaused) {
                systemPair.second->Update();
            }
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

void NKEngine::Quit() {
    _isQuiting = true;
}

bool NKEngine::Quitting() {
    return _isQuiting;
}
