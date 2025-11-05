//
// Created by r1nge on 11/3/25.
//

#include "NKRigidBodyComponent.h"

NKRigidBodyComponent::NKRigidBodyComponent(double mass, bool isKinematic) {
    velocity = new NKReversibleVector2Double(0, 0);
    this->mass = mass;
    this->isKinematic = isKinematic;
}
