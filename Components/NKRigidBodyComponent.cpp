//
// Created by r1nge on 11/3/25.
//

#include "NKRigidBodyComponent.h"

NKRigidBodyComponent::NKRigidBodyComponent(double mass, bool isKinematic) {
    this->mass = mass;
    this->isKinematic = isKinematic;
}
