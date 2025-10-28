//
// Created by r1nge on 10/27/25.
//

#include "NKInputSystem.h"

#include <iostream>

#include "../NKEngine.h"
#include "../Components/NKInputComponent.h"

void NKInputSystem::Update() {
    NKSystem::Update();

    //TODO: account for the case when 2 keys on the same axis are pressed
    //TODO: use SDL_GetKeyboardState(); instead of events
    for (const auto &pair: engine->_components) {
        auto inputComponent = engine->getComponent<NKInputComponent>(pair.first);
        if (inputComponent != nullptr) {
            auto keyboardState = SDL_GetKeyboardState(nullptr);
            if (keyboardState[SDL_SCANCODE_A] == 1) {
                inputComponent->HorizontalAxis = -1;
            }
            if (keyboardState[SDL_SCANCODE_D] == 1) {
                inputComponent->HorizontalAxis = 1;
            }

            if (keyboardState[SDL_SCANCODE_A] == 0) {
                if (inputComponent->HorizontalAxis == -1) {
                    inputComponent->HorizontalAxis = 0;
                }
            }

            if (keyboardState[SDL_SCANCODE_D] == 0) {
                if (inputComponent->HorizontalAxis == 1) {
                    inputComponent->HorizontalAxis = 0;
                }
            }


            if (keyboardState[SDL_SCANCODE_W] == 1) {
                inputComponent->VerticalAxis = -1;
            }
            if (keyboardState[SDL_SCANCODE_S] == 1) {
                inputComponent->VerticalAxis = 1;
            }

            if (keyboardState[SDL_SCANCODE_W] == 0) {
                if (inputComponent->VerticalAxis == -1) {
                    inputComponent->VerticalAxis = 0;
                }
            }
            if (keyboardState[SDL_SCANCODE_S]) {
                if (inputComponent->VerticalAxis == 1) {
                    inputComponent->VerticalAxis = 0;
                }
            }
        }

        //std::cout << "Vertical " << inputComponent->VerticalAxis << " Horizontal " << inputComponent->HorizontalAxis << " Last key code " << inputComponent->LastKey << "\n";
    }
}