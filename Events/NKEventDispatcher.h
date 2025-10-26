//
// Created by r1nge on 10/23/25.
//

#ifndef NKENGINE_EVENTDISPATCHER_H
#define NKENGINE_EVENTDISPATCHER_H
#include <list>
#include <queue>

#include "NKEvent.h"
#include "NKEventSubscriber.h"


class NKEventDispatcher {
public:
    void AddEvent(NKEventType);
    void Dispatch();
    void AddSubscriber(NKEventSubscriber* subscriber);
    void RemoveSubscriber(NKEventSubscriber* subscriber);
private:
    std::queue<NKEventType> _eventQueue;
    std::list<NKEventSubscriber*> _subscribers;
};


#endif //NKENGINE_EVENTDISPATCHER_H