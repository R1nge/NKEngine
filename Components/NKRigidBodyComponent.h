//
// Created by r1nge on 11/3/25.
//

#ifndef NKENGINE_NKGRAVITYCOMPONENT_H
#define NKENGINE_NKGRAVITYCOMPONENT_H
#include "NKComponent.h"
#include "../box2cpp.h"
#include "../NKReversibleVector2Double.h"


struct NKRigidBodyComponent : NKComponent {
    NKRigidBodyComponent(b2::Body *body);

    b2::Body *rigidBody;
};


#endif //NKENGINE_NKGRAVITYCOMPONENT_H
