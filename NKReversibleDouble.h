//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKREVERSABLEINT_H
#define NKENGINE_NKREVERSABLEINT_H
#include <map>


struct NKReversibleDouble {
    double startValue;
    //TODO: original value
    double currentValue;
    //TODO: current value to be able to quickly add/sub a delta
    double previousValue;
    //Tick, delta-value
    std::map<int, double> deltas;
    //TODO: map<tick, delta>
    //TODO: store original state + delta + tick
    void Move(int tick, double delta);

    void Rewind(int tick);
};


#endif //NKENGINE_NKREVERSABLEINT_H
