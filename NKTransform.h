//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKTRANSFORM_H
#define NKENGINE_NKTRANSFORM_H
#include "NKReversibleVector2Int.h"


class NKTransform {
public:
    NKTransform(int x, int y);

    NKReversibleVector2Int *position;

    void Move(int tick, int deltaX, int deltaY);

    void Rewind(int tick);
};


#endif //NKENGINE_NKTRANSFORM_H
