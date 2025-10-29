//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKVECTOR2INT_H
#define NKENGINE_NKVECTOR2INT_H
#include "NKReversibleDouble.h"


struct NKReversibleVector2Double {
    NKReversibleVector2Double(double x, double y);

    NKReversibleDouble *X;
    NKReversibleDouble *Y;
};


#endif //NKENGINE_NKVECTOR2INT_H