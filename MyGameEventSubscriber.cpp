//
// Created by r1nge on 10/23/25.
//

#include "MyGameEventSubscriber.h"

#include <iostream>

#include "NKEngine.h"

MyGameEventSubscriber::MyGameEventSubscriber(std::shared_ptr<NKSprite> sprite, std::shared_ptr<NKEngine> engine) {
    _sprite = sprite;
    _engine = engine;
}

void MyGameEventSubscriber::Invoke(NKEventType type) {
    std::cout << type << '\n';
    std::cout << _engine->GetLastKeyInput() << '\n';
    if (type == InputEnd) {
        switch (_engine->GetLastKeyInput()) {
            case SDLK_w:
                _sprite->spriteRect->y -= 1;
                break;
            case SDLK_s:
                _sprite->spriteRect->y += 1;
                break;
            case SDLK_a:
                _sprite->spriteRect->x -= 1;
                break;
            case SDLK_d:
                _sprite->spriteRect->x += 1;
                break;
            default:
                break;
        }
    }
}
