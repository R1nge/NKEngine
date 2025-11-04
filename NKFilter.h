//
// Created by r1nge on 11/4/25.
//

#ifndef NKENGINE_NKFILTER_H
#define NKENGINE_NKFILTER_H
#include <vector>

#include "NKEngine.h"
#include "Components/NKComponent.h"


class NKFilter {
public:
    NKFilter(NKEngine *engine);

    //TODO: store a list of entities
    //TDOO: with = add to the list
    //TODO: without = remove from the list
    //TODO: get enities list
    template<typename Component>
    NKFilter With(NKComponent *component);

    template<typename Component>
    NKFilter Without(NKComponent *component);

    std::vector<int> Build();

private:
    std::vector<int> _entities;
    NKEngine *_engine;
};

#endif //NKENGINE_NKFILTER_H
