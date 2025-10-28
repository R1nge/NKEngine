//
// Created by r1nge on 10/28/25.
//


#ifndef NKENGINE_NKREVERSIBLEACTION_H
#define NKENGINE_NKREVERSIBLEACTION_H

class NKEngine;

class NKReversibleAction {
public:
    NKReversibleAction();

    void SetEngine(NKEngine *engine) {
        this->_engine = engine;
    }

    int tick;

    virtual void Do() = 0;

    virtual void Undo() = 0;

protected:
    NKEngine *_engine;
};


#endif //NKENGINE_NKREVERSIBLEACTION_H
