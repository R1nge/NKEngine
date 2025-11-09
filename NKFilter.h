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
    NKFilter *With() {
        std::type_index typeIndex = std::type_index(typeid(Component));

        // Check if the type is already stored
        if (std::find(_componentsToSearchFor.begin(), _componentsToSearchFor.end(), typeIndex) == _componentsToSearchFor
            .end()) {
            _componentsToSearchFor.push_back(typeIndex); // Store the type
        }

        return this;
    }


    template<typename Component>
    NKFilter *Without() {
        auto findIter = std::remove_if(_componentsToSearchFor.begin(), _componentsToSearchFor.end(),
                                       [](NKComponent *comp) {
                                           return dynamic_cast<Component *>(comp) != nullptr;
                                           // Check if the component is of the specified type
                                       });

        _componentsToSearchFor.erase(findIter, _componentsToSearchFor.end());
        return this;
    }


    std::vector<std::uint_fast16_t> Build();

    std::vector<std::uint_fast16_t> _entities;

private:
    std::vector<std::type_index> _componentsToSearchFor;
    NKEngine *_engine;
};

#endif //NKENGINE_NKFILTER_H
