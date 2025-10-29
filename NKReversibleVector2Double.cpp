//
// Created by r1nge on 10/19/25.
//

#include "NKReversibleVector2Double.h"

NKReversibleVector2Double::NKReversibleVector2Double(double x, double y) {
    X = new NKReversibleDouble(x, x);
    Y = new NKReversibleDouble(y, y);
}
