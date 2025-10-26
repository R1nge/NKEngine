//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKTRANSFORM_H
#define NKENGINE_NKTRANSFORM_H
#include "NKReversibleVector2Int.h"


class NKTransformComponent {
public:
    NKTransformComponent(int x, int y);

    NKReversibleVector2Int *position;
};


#endif //NKENGINE_NKTRANSFORM_H
