//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKTRANSFORM_H
#define NKENGINE_NKTRANSFORM_H
#include "NKComponent.h"
#include "../NKReversibleVector2Int.h"


struct NKReversiblePositionComponent : NKComponent {
    NKReversiblePositionComponent(int x, int y);
    NKReversibleVector2Int *position;
};


#endif //NKENGINE_NKTRANSFORM_H
