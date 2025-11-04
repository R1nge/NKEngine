//
// Created by r1nge on 10/26/25.
//

#include "NKReversibleDouble.h"

void NKReversibleDouble::Move(int tick, double delta) {
    currentValue += delta;
    deltas[tick] += delta;
}
