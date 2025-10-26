//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKREVERSABLEINT_H
#define NKENGINE_NKREVERSABLEINT_H
#include <map>


struct NKReversibleInt {
    int startValue;
    //TODO: original value
    int currentValue;
    //TODO: current value to be able to quickly add/sub a delta
    //Tick, delta-value
    std::map<int, int> deltas;
    //TODO: map<tick, delta>
    //TODO: store original state + delta + tick
};


#endif //NKENGINE_NKREVERSABLEINT_H
