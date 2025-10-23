//
// Created by r1nge on 10/23/25.
//

#include "NKEventDispatcher.h"

void NKEventDispatcher::AddEvent(NKEventType type) {
    _eventQueue.push(type);
}

void NKEventDispatcher::Dispatch() {
    for (int i = 0; i < _eventQueue.size(); ++i) {
        auto event = _eventQueue.front();
        if (event != None) {
            for (auto const& subscriber : _subscribers) {
                subscriber->Invoke(event);
            }
        }

        _eventQueue.pop();
    }
}

void NKEventDispatcher::AddSubscriber(NKEventSubscriber *subscriber) {
    _subscribers.push_back(subscriber);
}

void NKEventDispatcher::RemoveSubscriber(NKEventSubscriber *subscriber) {
    _subscribers.remove(subscriber);
}


