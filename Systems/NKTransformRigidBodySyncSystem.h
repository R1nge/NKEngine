//
// Created by r1nge on 11/5/25.
//

#ifndef NKENGINE_NKRIGIDBODYTRANSFORMSYNCSYSTEM_H
#define NKENGINE_NKRIGIDBODYTRANSFORMSYNCSYSTEM_H
#include "NKSystem.h"
#include "../NKFilter.h"


class NKTransformRigidBodySyncSystem : public NKSystem {
public:
    void Init() override;
    void Update(double deltaTime) override;

    NKFilter *filter = nullptr;
};


#endif //NKENGINE_NKRIGIDBODYTRANSFORMSYNCSYSTEM_H
