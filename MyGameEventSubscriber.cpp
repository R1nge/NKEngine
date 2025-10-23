//
// Created by r1nge on 10/23/25.
//

#include "MyGameEventSubscriber.h"

#include <iostream>

void MyGameEventSubscriber::Invoke(NKEventType type) {
    std::cout << type << '\n';
}
