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

    template<typename Component>
    NKFilter *With(NKComponent *component);

    template<typename Component>
    NKFilter *Without(NKComponent *component);

    std::vector<std::uint_fast16_t> Build();
    std::vector<std::uint_fast16_t> _entities;
private:
    std::vector<NKComponent*> _componentsToSearchFor;
    NKEngine *_engine;
};

#endif //NKENGINE_NKFILTER_H
