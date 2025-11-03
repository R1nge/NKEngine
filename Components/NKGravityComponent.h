//
// Created by r1nge on 11/3/25.
//

#ifndef NKENGINE_NKGRAVITYCOMPONENT_H
#define NKENGINE_NKGRAVITYCOMPONENT_H
#include "NKComponent.h"


struct NKGravityComponent : NKComponent {
    NKGravityComponent(double y);

    double y;
};


#endif //NKENGINE_NKGRAVITYCOMPONENT_H
