//
// Created by r1nge on 10/19/25.
//

#include "NKReversibleVector2Double.h"

NKReversibleVector2Double::NKReversibleVector2Double(double x, double y) {
    X = std::make_unique<NKReversibleDouble>(x, x, x);
    Y = std::make_unique<NKReversibleDouble>(y, y, y);
}
