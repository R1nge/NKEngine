//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKTRANSFORMSYSTEM_H
#define NKENGINE_NKTRANSFORMSYSTEM_H
#include "NKSystem.h"
#include "../Components/NKReversiblePositionComponent.h"


class NKTransformSystem : public NKSystem {
public:
    void Update(double deltaTime) override;
    void Rewind(int tick);
};


#endif //NKENGINE_NKTRANSFORMSYSTEM_H
