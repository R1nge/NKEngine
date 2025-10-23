//
// Created by r1nge on 10/23/25.
//

#ifndef NKENGINE_NKEVENTSUBSCRIBER_H
#define NKENGINE_NKEVENTSUBSCRIBER_H
#include "NKEvent.h"


class NKEventSubscriber {
public:
    virtual void Invoke(NKEventType type);
};


#endif //NKENGINE_NKEVENTSUBSCRIBER_H