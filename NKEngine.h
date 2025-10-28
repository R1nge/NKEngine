//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKENGINE_H
#define NKENGINE_NKENGINE_H
#include <iostream>
#include <map>
#include <memory>
#include <SDL_keycode.h>
#include <typeindex>

#include "NKGroupType.h"
#include "NKSpriteCreator.h"
#include "Events/NKEventDispatcher.h"
#include "Systems/NKRenderingSystem.h"
#include "Systems/NKSystem.h"
#include "NKUuidGenerator.h"
#include "Components/NKComponent.h"

class NKEngine {
public:
    NKEngine();

    ~NKEngine();

    void Update();

    void Rewind();

    int GetTick() const;

    std::unique_ptr<NKEventDispatcher> EventDispatcher;
    std::unique_ptr<NKUuidGenerator> UuidGenerator;
    std::unique_ptr<NKWindow> Window;
    std::unique_ptr<NKSpriteCreator> SpriteCreator;

    int CreateEntity();

    template<typename ComponentType>
    void AddComponent(int entityId, std::unique_ptr<ComponentType> component) {
        auto &componentsList = _components[entityId];
        componentsList.emplace_back(std::move(component));
    }

    template<typename ComponentType>
    void RemoveComponent(int entityId) {
        auto &componentsList = _components[entityId];
        componentsList.remove_if([](const std::unique_ptr<NKComponent> &component) {
            std::cout << "Removed a component";
            return typeid(*component) == typeid(ComponentType);
        });
    }

    template<typename ComponentType>
    ComponentType *getComponent(int entityId) {
        auto it = _components.find(entityId);
        if (it != _components.end()) {
            for (const auto &component: it->second) {
                if (auto castedComponent = dynamic_cast<ComponentType *>(component.get())) {
                    return castedComponent;
                }
            }
        }
        // Entity or component not found
        return nullptr;
    }

    //Adds system to the end of the specified group type
    template<typename SystemType>
    void AddSystem(NKGroupType groupType, std::unique_ptr<SystemType> system) {
        system->SetEngine(this);

        // Check if the group exists
        auto it = _groups.find(groupType);
        if (it != _groups.end()) {
            // Group exists, add the system to the existing group
            //it->second.insert()
            it->second.emplace(it->second.size(), std::move(system));
        } else {
            // Group doesn't exist, create it and add the system
            std::map<int, std::unique_ptr<NKSystem> > newGroup; // Replace std::set with your preferred container type
            newGroup.emplace(0, std::move(system)); // Add system to the new group
            _groups.emplace(groupType, std::move(newGroup)); // Initialize the group in the map
        }
    }

    void PrintAllSystem() {
        std::cout << "\n" << "Printing all systems" << "\n";
        for (const auto &groupPair: _groups) {
            for (const auto &systemPair: groupPair.second) {
                std::string typeName = typeid(*systemPair.second).name();

                size_t startPos = 0;
                while (startPos < typeName.length() && std::isdigit(typeName[startPos])) {
                    ++startPos;
                }

                std::string cleanTypeName = typeName.substr(startPos);

                std::cout << "Group order " << groupPair.first
                        << " System order " << systemPair.first
                        << " System " << cleanTypeName << "\n";
            }
        }
    }

    bool IsRewinding();

    void Quit();

    bool Quitting();

    //TODO: create a world class (wrapper for systems and components)
    std::map<int, std::list<std::unique_ptr<NKComponent> > > _components;
    std::map<NKGroupType, std::map<int, std::unique_ptr<NKSystem> > > _groups;

private:
    int _entityId;
    int _currentTick;
    bool _isRewinding;
    bool _isPaused;
    bool _isQuiting;
};


#endif //NKENGINE_NKENGINE_H
