//
// Created by r1nge on 10/27/25.
//

#include "NKColliderComponent.h"

NKColliderComponent::NKColliderComponent(SDL_Rect *box, bool pushable) {
    boundingBox = box;
    isPushable = pushable;
}
