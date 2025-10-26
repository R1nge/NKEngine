//
// Created by r1nge on 10/19/25.
//

#include "NKEngine.h"

#include <memory>
#include <SDL_image.h>

//TODO: create a sprite class (base position on a sprite sheet)
//TODO: create a base class { position, sprite }

//TODO: engine core -> callbacks -> modules -> callbacks -> developer

NKEngine::NKEngine() {
    EventDispatcher = std::make_unique<NKEventDispatcher>();
    UuidGenerator = std::make_unique<NKUuidGenerator>();
    addSystem(std::make_unique<NKRenderingSystem>());
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
    bool quit = false;

    //Event handler
    SDL_Event event;

    //While application is running
    while (!quit) {
        EventDispatcher->AddEvent(InputStart);
        EventDispatcher->Dispatch();

        //Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
            //User requests quit
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (!_isPaused) {
                    _lastKeyInput = event.key.keysym.sym;
                }
            } else if (event.type == SDL_KEYUP) {
                if (!_isPaused) {
                    if (event.key.keysym.sym == _lastKeyInput) {
                        _lastKeyInput = 0;
                    }
                }
            }
        }

        EventDispatcher->AddEvent(InputEnd);
        EventDispatcher->Dispatch();

        for (const auto &systemPair: _systems) {
            if (!_isPaused) {
                systemPair.second->Update();
            }
        }

        if (!_isRewinding) {
            _currentTick++;
        } else {
            _currentTick--;
            //Renderer->Rewind(_currentTick);
            if (_currentTick == 0) {
                _isRewinding = false;
            }
        }
    }
}

void NKEngine::Rewind() {
    _isRewinding = true;
}

int NKEngine::GetTick() const {
    return _currentTick;
}

SDL_Keycode NKEngine::GetLastKeyInput() const {
    return _lastKeyInput;
}

int NKEngine::CreateEntity() {
    _entityId++;
    return _entityId;
}
