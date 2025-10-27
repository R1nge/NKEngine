//
// Created by r1nge on 10/27/25.
//

#include "NKInputSystem.h"

#include <iostream>

#include "../NKEngine.h"
#include "../Components/NKInputComponent.h"

void NKInputSystem::Update() {
    NKSystem::Update();

    for (const auto &pair: engine->_components) {
        auto inputComponent = engine->getComponent<NKInputComponent>(pair.first);
        if (inputComponent != nullptr) {
            bool quit = false;
            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                //User requests quit
                if (event.type == SDL_QUIT) {
                    quit = true;
                } else if (event.type == SDL_KEYDOWN) {
                    auto key = event.key.keysym.sym;
                    if (key == SDLK_a) {
                        inputComponent->HorizontalAxis = -1;
                    } else if (key == SDLK_d) {
                        inputComponent->HorizontalAxis = 1;
                    }

                    if (key == SDLK_w) {
                        inputComponent->VerticalAxis = -1;
                    } else if (key == SDLK_s) {
                        inputComponent->VerticalAxis = 1;
                    }
                } else if (event.type == SDL_KEYUP) {
                }

                std::cout << "Vertical " << inputComponent->VerticalAxis << "\n";
                std::cout << "Horizontal " << inputComponent->HorizontalAxis << "\n";
            }
        }
    }
}
