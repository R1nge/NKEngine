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

                    if (key != SDLK_a && key != SDLK_d && key != SDLK_w && key != SDLK_s) {
                        inputComponent->LastKey = key;
                    }
                } else if (event.type == SDL_KEYUP) {
                    auto key = event.key.keysym.sym;
                    if (key == SDLK_a) {
                        if (inputComponent->HorizontalAxis == -1) {
                            inputComponent->HorizontalAxis = 0;
                        }
                    } else if (key == SDLK_d) {
                        if (inputComponent->HorizontalAxis == 1) {
                            inputComponent->HorizontalAxis = 0;
                        }
                    }

                    if (key == SDLK_w) {
                        if (inputComponent->VerticalAxis == -1) {
                            inputComponent->VerticalAxis = 0;
                        }
                    } else if (key == SDLK_s) {
                        if (inputComponent->VerticalAxis == 1) {
                            inputComponent->VerticalAxis = 0;
                        }
                    }

                    if (key != SDLK_a && key != SDLK_d && key != SDLK_w && key != SDLK_s) {
                        inputComponent->LastKey = 0;
                    }
                }

                std::cout << "Vertical " << inputComponent->VerticalAxis << " Horizontal " << inputComponent->
                        HorizontalAxis << " Last key code " << inputComponent->LastKey <<"\n";
            }
        }
    }
}
