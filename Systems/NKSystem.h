//
// Created by r1nge on 10/26/25.
//

#ifndef NKENGINE_NKSYSTEM_H
#define NKENGINE_NKSYSTEM_H

class NKFilter;
class NKEngine;

class NKSystem {
public:
    virtual ~NKSystem() = default;

    void SetEngine(NKEngine *engine) {
        this->engine = engine;
    }

    virtual void Init();

    virtual void Update(double deltaTime);

    void Dispose();

protected:
    NKEngine *engine = nullptr;
    NKFilter *filter = nullptr;
};


#endif //NKENGINE_NKSYSTEM_H
