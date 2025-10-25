//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKENGINE_H
#define NKENGINE_NKENGINE_H
#include <memory>
#include <SDL_keycode.h>

#include "NKEventDispatcher.h"
#include "NKRenderer.h"
#include "NKUuidGenerator.h"


class NKEngine {
public:
    NKEngine();
    ~NKEngine();
    void Update();

    SDL_Keycode GetLastKeyInput() const;
    std::unique_ptr<NKEventDispatcher> EventDispatcher;
    std::unique_ptr<NKUuidGenerator> UuidGenerator;
    std::unique_ptr<NKRenderer> Renderer;

private:
    bool _isPaused;
    SDL_Keycode _lastKeyInput;
};


#endif //NKENGINE_NKENGINE_H
