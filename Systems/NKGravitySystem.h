//
// Created by r1nge on 11/3/25.
//

#ifndef NKENGINE_NKPHYSICSSYSTEM_H
#define NKENGINE_NKPHYSICSSYSTEM_H
#include "NKSystem.h"


class NKGravitySystem : public NKSystem {
    void Update(double deltaTime) override;
};


#endif //NKENGINE_NKPHYSICSSYSTEM_H
