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
    for (const auto &group: _engine->_components) {
        for (const auto &component: group.second) {
            // Check if any of the types stored in _componentsToSearchFor match the component's type
            for (const auto &toSearchFor: _componentsToSearchFor) {
                if (std::type_index(typeid(*component)) == toSearchFor) {
                    // Compare the actual type
                    _entities.emplace_back(group.first);
                    break; // No need to check other types if already found
                }
            }
        }
    }

    return _entities;

    return _entities;
}
