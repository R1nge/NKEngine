//
// Created by r1nge on 11/4/25.
//

#include "NKFilter.h"

template<typename Component>
NKFilter *NKFilter::With(NKComponent *component) {
    _componentsToSearchFor.emplace_back(component);
    return this;
}

template<typename Component>
NKFilter *NKFilter::Without(NKComponent *component) {

    auto findIter = std::find(_componentsToSearchFor.begin(), _componentsToSearchFor.end(), component);
    _componentsToSearchFor.erase(findIter);
    return this;
}

std::vector<std::uint_fast16_t> NKFilter::Build() {
    //Clear list
    _entities.clear();
    //Find all existing components that meet the query
    for (auto group : _engine->_components) {
        for (auto& component : group.second) {
            for (auto& toSearhFor : _componentsToSearchFor) {
                if (component.get() == toSearhFor) {
                    _entities.emplace_back(group.first);
                }
            }
        }
    }
    return _entities;
}
