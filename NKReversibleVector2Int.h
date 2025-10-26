//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKVECTOR2INT_H
#define NKENGINE_NKVECTOR2INT_H
#include "NKReversibleInt.h"


struct NKReversibleVector2Int {
    NKReversibleVector2Int(int x, int y);

    NKReversibleInt *X;
    NKReversibleInt *Y;
};


#endif //NKENGINE_NKVECTOR2INT_H