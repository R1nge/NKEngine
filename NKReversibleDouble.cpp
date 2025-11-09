//
// Created by r1nge on 10/26/25.
//

#include "NKReversibleDouble.h"

void NKReversibleDouble::Move(int tick, double delta) {
    currentValue += delta;
    deltas[tick] += delta;
}

void NKReversibleDouble::Rewind(int tick) {
    if (deltas.contains(tick)) {
        auto delta = deltas.at(tick);
        previousValue = currentValue;
        currentValue -= delta;
        deltas.erase(tick);
    }
}
