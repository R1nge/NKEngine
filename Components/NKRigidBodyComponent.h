//
// Created by r1nge on 11/3/25.
//

#ifndef NKENGINE_NKGRAVITYCOMPONENT_H
#define NKENGINE_NKGRAVITYCOMPONENT_H
#include "NKComponent.h"


struct NKRigidBodyComponent : NKComponent {
    NKRigidBodyComponent(double mass, bool isKinematic);

    double mass;
    bool isKinematic;
};


#endif //NKENGINE_NKGRAVITYCOMPONENT_H
