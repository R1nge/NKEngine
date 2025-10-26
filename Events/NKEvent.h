//
// Created by r1nge on 10/23/25.
//

#ifndef NKENGINE_NKEVENT_H
#define NKENGINE_NKEVENT_H

enum NKEventType {
    None = 0,
    InputStart = 1,
    InputEnd = 2,
    RenderStart = 3,
    RenderEnd = 4
};

class NKEvent {
public:
    NKEventType type;
};


#endif //NKENGINE_NKEVENT_H
