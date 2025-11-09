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
    //All entities
    for (const auto &group: _engine->_components) {
        //All component
        bool shouldAdd = true;
        for (const auto &component: group.second) {
            //Component
            for (const auto &toSearchFor: _componentsToSearchFor) {
                if (std::type_index(typeid(*component)) != toSearchFor) {
                    shouldAdd = false;
                } else {
                    shouldAdd = true;
                }
            }
        }


        if (shouldAdd) {
            _entities.emplace_back(group.first);
        }
    }

    return _entities;
}
