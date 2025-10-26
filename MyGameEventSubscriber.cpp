//
// Created by r1nge on 10/23/25.
//

#include "MyGameEventSubscriber.h"

#include "NKEngine.h"

MyGameEventSubscriber::MyGameEventSubscriber(std::shared_ptr<NKEngine> engine) {
    _engine = engine;
}

void MyGameEventSubscriber::Invoke(NKEventType type) {
    if (type == InputEnd) {
        auto tick = _engine->GetTick();
        switch (_engine->GetLastKeyInput()) {
            case SDLK_w:
                //_sprite->Move(tick, 0, -1);
                break;
            case SDLK_s:
                //_sprite->Move(tick, 0, 1);
                break;
            case SDLK_a:
                //_sprite->Move(tick, -1, 0);
                break;
            case SDLK_d:
                //_sprite->Move(tick, 1, 0);
                break;
            case SDLK_r:
                _engine->Rewind();
                break;
            default:
                break;
        }
    }
}
