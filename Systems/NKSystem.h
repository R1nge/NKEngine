//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKSYSTEM_H
#define NKENGINE_NKSYSTEM_H

class NKEngine;

class NKSystem {
public:
    void SetEngine(NKEngine *engine) {
        this->engine = engine;
    }

    void Init();

    virtual void Update(double deltaTime);

    void Dispose();

protected:
    NKEngine *engine;
};


#endif //NKENGINE_NKSYSTEM_H
