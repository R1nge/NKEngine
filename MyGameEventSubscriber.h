//
// Created by r1nge on 10/23/25.
//

#ifndef NKENGINE_MYGAMEEVENTSUBSCRIBER_H
#define NKENGINE_MYGAMEEVENTSUBSCRIBER_H
#include "NKEventSubscriber.h"


class MyGameEventSubscriber : public NKEventSubscriber {
public:
    void Invoke(NKEventType type) override;
};


#endif //NKENGINE_MYGAMEEVENTSUBSCRIBER_H