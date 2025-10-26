//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKTRANSFORMSYSTEM_H
#define NKENGINE_NKTRANSFORMSYSTEM_H


class NKTransformSystem {
public:
    void Move(int tick, int deltaX, int deltaY);

    void Rewind(int tick);
};


#endif //NKENGINE_NKTRANSFORMSYSTEM_H
