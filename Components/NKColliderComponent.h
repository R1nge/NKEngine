//
// Created by r1nge on 10/27/25.
//

#ifndef NKENGINE_NKCOLLISIONCOMPONENT_H
#define NKENGINE_NKCOLLISIONCOMPONENT_H
#include <SDL_rect.h>

#include "NKComponent.h"


struct NKColliderComponent : NKComponent {
    NKColliderComponent(SDL_Rect *box);

    SDL_Rect *boundingBox;
};


#endif //NKENGINE_NKCOLLISIONCOMPONENT_H