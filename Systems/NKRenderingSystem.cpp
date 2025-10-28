//
// Created by r1nge on 10/25/25.
//

#include "NKRenderingSystem.h"
#include "../NKEngine.h"

#include <SDL.h>
#include <SDL_image.h>

#include "../Components/NKRenderComponent.h"
#include "../Components/NKReversiblePositionComponent.h"

NKRenderingSystem::NKRenderingSystem(NKWindow *window) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        _window = window;
    }
}

void NKRenderingSystem::Update() {
    Render();
}

void NKRenderingSystem::Render() {
    SDL_RenderClear(_window->Renderer);

    for (const auto &pair: engine->_components) {
        auto renderComponent = engine->getComponent<NKRenderComponent>(pair.first);
        if (renderComponent != nullptr) {
            auto transformComponent = engine->getComponent<NKReversiblePositionComponent>(pair.first);
            if (transformComponent != nullptr) {
                renderComponent->spriteRect->x =
                        transformComponent->position->X->currentValue - renderComponent->spriteRect->w / 2;
                renderComponent->spriteRect->y =
                        transformComponent->position->Y->currentValue - renderComponent->spriteRect->h / 2;
                SDL_RenderCopy(_window->Renderer, renderComponent->texture, renderComponent->textureRect,
                               renderComponent->spriteRect);
            }
        }
    }

    SDL_RenderPresent(_window->Renderer);
}
