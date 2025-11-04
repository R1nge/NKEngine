//
// Created by r1nge on 11/4/25.
//

#include "NKFilter.h"

template<typename Component>
NKFilter *NKFilter::With(NKComponent *component) {
    for (auto group: _engine->_components) {
        if (_engine->GetComponent<Component>(group.first) != nullptr) {
            _entities.emplace_back(group.first);
        }
    }
    return this;
}

template<typename Component>
NKFilter *NKFilter::Without(NKComponent *component) {
    NKFilter *result = new NKFilter(_engine); // Create a new filter to hold the results
    for (auto group: _engine->_components) {
        // Check if the entity has the specified component
        if (_engine->GetComponent<Component>(group.first) == nullptr) {
            result->_entities.emplace_back(group.first);
        }
    }
    return result;
}

std::vector<int> NKFilter::Build() {
    return _entities;
}
