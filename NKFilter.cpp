//
// Created by r1nge on 11/4/25.
//

#include "NKFilter.h"

template<typename Component>
NKFilter NKFilter::With(NKComponent *comp) {
    for (auto group: _engine->_components) {
        if (_engine->GetComponent<Component>(group.first) != nullptr) {
            _entities.emplace_back(group.first);
        }
    }
}

template<typename Component>
NKFilter NKFilter::Without(NKComponent *component) {
    for (auto group: _engine->_components) {
        if (_engine->GetComponent<Component>(group.first) != nullptr) {
            //_entities.
            //_entities.
            //_entities.(group.first);
        }
    }
}

std::vector<int> NKFilter::Build() {
    return _entities;
}
