//
// Created by r1nge on 10/23/25.
//

#ifndef NKENGINE_MYGAMEEVENTSUBSCRIBER_H
#define NKENGINE_MYGAMEEVENTSUBSCRIBER_H
#include <memory>

#include "NKEngine.h"
#include "NKEventSubscriber.h"
#include "NKSprite.h"


class MyGameEventSubscriber : public NKEventSubscriber {
public:
    MyGameEventSubscriber(std::shared_ptr<NKSprite> sprite, std::shared_ptr<NKEngine> engine);
    void Invoke(NKEventType type) override;
private:
    std::shared_ptr<NKSprite> _sprite;
    std::shared_ptr<NKEngine> _engine;
};


#endif //NKENGINE_MYGAMEEVENTSUBSCRIBER_H