//
// Created by r1nge on 10/28/25.
//

#ifndef NKENGINE_GAMETESTACTION_H
#define NKENGINE_GAMETESTACTION_H
#include "NKReversibleAction.h"


class GameTestAction : public NKReversibleAction {
public:
    void Do() override;

    void Undo() override;
};


#endif //NKENGINE_GAMETESTACTION_H
