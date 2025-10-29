//
// Created by r1nge on 10/25/25.
//

#include "NKRenderingSystem.h"
#include "../NKEngine.h"

#include <SDL.h>
#include <SDL_image.h>

#include "../Components/NKCameraTag.h"
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

void NKRenderingSystem::Update(double deltaTime) {
    Render();
}

void NKRenderingSystem::Render() {
    SDL_RenderClear(_window->Renderer);

    std::vector<std::pair<int, NKRenderComponent *> > renderQueue;

    for (const auto &pair: engine->_components) {
        auto camera = engine->getComponent<NKCameraTag>(pair.first);
        if (camera != nullptr) {
            auto cameraPosition = engine->getComponent<NKReversiblePositionComponent>(pair.first);
            if (cameraPosition != nullptr) {
                for (const auto &pair2: engine->_components) {
                    auto renderComponent = engine->getComponent<NKRenderComponent>(pair2.first);

                    if (renderComponent != nullptr) {
                        renderQueue.emplace_back(pair2.first, renderComponent);
                    }
                }
            }
        }
    }

    std::sort(renderQueue.begin(), renderQueue.end(), [](const auto &a, const auto &b) {
        return a.second->data->layer < b.second->data->layer; // Sort in ascending order
    });

    for (const auto &pair: engine->_components) {
        auto camera = engine->getComponent<NKCameraTag>(pair.first);
        if (camera != nullptr) {
            auto cameraPosition = engine->getComponent<NKReversiblePositionComponent>(pair.first);
            for (auto &pair2: renderQueue) {
                auto worldPosition = engine->getComponent<NKReversiblePositionComponent>(pair2.first);
                if (worldPosition != nullptr) {
                    auto renderComponent = pair2.second;
                    renderComponent->spriteRect->x =
                            worldPosition->position->X->currentValue - static_cast<double>(renderComponent->spriteRect->
                                w) / static_cast<double>(2) - cameraPosition->position->X->currentValue;
                    renderComponent->spriteRect->y =
                            worldPosition->position->Y->currentValue - static_cast<double>(renderComponent->spriteRect->
                                h) / static_cast<double>(2) - cameraPosition->position->Y->currentValue;
                    SDL_RenderCopyF(_window->Renderer, renderComponent->texture, renderComponent->textureRect,
                                    renderComponent->spriteRect);
                }
            }
        }
    }

    SDL_RenderPresent(_window->Renderer);
}
