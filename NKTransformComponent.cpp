//
// Created by r1nge on 10/26/25.
//

#include "NKTransformComponent.h"

NKTransformComponent::NKTransformComponent(int x, int y) {
    position = new NKReversibleVector2Int(x, y);
}
