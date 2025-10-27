//
// Created by r1nge on 10/27/25.
//

#ifndef NKENGINE_NKINPUTCOMPONENT_H
#define NKENGINE_NKINPUTCOMPONENT_H
#include <SDL_keycode.h>

#include "NKComponent.h"


struct NKInputComponent : NKComponent {
    int HorizontalAxis;
    int VerticalAxis;
    SDL_Keycode LastKey;
};


#endif //NKENGINE_NKINPUTCOMPONENT_H
