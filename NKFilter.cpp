//
// Created by r1nge on 11/4/25.
//

#include "NKFilter.h"


NKFilter::NKFilter(NKEngine *engine) {
    _engine = engine;
}

std::vector<std::uint_fast16_t> NKFilter::Build() {
    //Clear list
    _entities.clear();
    //Find all existing components that meet the query

    for (auto &group: _engine->_components) {
        for (auto &component: group.second) {
            for (auto &toSearchFor: _componentsToSearchFor) {
                if (component.get() == toSearchFor) {
                    _entities.emplace_back(group.first);
                }
            }
        }
    }

    return _entities;
}
