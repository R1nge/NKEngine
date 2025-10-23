//
// Created by r1nge on 10/23/25.
//

#ifndef NKENGINE_MYGAMEEVENTSUBSCRIBER_H
#define NKENGINE_MYGAMEEVENTSUBSCRIBER_H
#include <memory>

#include "NKEventSubscriber.h"
#include "NKSprite.h"


class MyGameEventSubscriber : public NKEventSubscriber {
public:
    MyGameEventSubscriber(std::shared_ptr<NKSprite> sprite);
    void Invoke(NKEventType type) override;
private:
    std::shared_ptr<NKSprite> _sprite;
};


#endif //NKENGINE_MYGAMEEVENTSUBSCRIBER_H