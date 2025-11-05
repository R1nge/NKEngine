//
// Created by r1nge on 11/5/25.
//

#ifndef NKENGINE_NKRIGIDBODYTRANSFORMSYNCSYSTEM_H
#define NKENGINE_NKRIGIDBODYTRANSFORMSYNCSYSTEM_H
#include "NKSystem.h"


class NKTransformRigidBodySyncSystem : public NKSystem {
    void Update(double deltaTime) override;
};


#endif //NKENGINE_NKRIGIDBODYTRANSFORMSYNCSYSTEM_H
