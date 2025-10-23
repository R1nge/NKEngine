//
// Created by r1nge on 10/23/25.
//

#include "MyGameEventSubscriber.h"

#include <iostream>

MyGameEventSubscriber::MyGameEventSubscriber(std::shared_ptr<NKSprite> sprite) {
    _sprite = sprite;
}

void MyGameEventSubscriber::Invoke(NKEventType type) {
    std::cout << type << '\n';
    if (type == InputEnd) {
        _sprite->dimensions->x += 0;
    }
}
