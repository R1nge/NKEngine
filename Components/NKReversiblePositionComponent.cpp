//
// Created by r1nge on 10/26/25.
//

#include "NKReversiblePositionComponent.h"

#include "../NKWindow.h"

NKReversiblePositionComponent::NKReversiblePositionComponent(int x, int y) {
    position = new NKReversibleVector2Int(x + SCREEN_WIDTH / 2, -y + SCREEN_HEIGHT / 2);
}
