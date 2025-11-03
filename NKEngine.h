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

#include "NKCoordinatesConverter.h"
#include "NKGroupType.h"
#include "NKReversibleAction.h"
#include "NKSpriteCreator.h"
#include "Events/NKEventDispatcher.h"
#include "Systems/NKRenderingSystem.h"
#include "Systems/NKSystem.h"
#include "NKUuidGenerator.h"
#include "Components/NKComponent.h"
#include "Components/NKCollisionComponent.h"
#include "Components/NKGravityComponent.h"
#include "Components/NKInputComponent.h"
#include "Components/NKRenderComponent.h"
#include "Components/NKReversiblePositionComponent.h"

class NKEngine {
public:
    NKEngine();

    ~NKEngine();

    void Update();

    void Rewind();

    std::uint_fast32_t GetTick() const;


    std::unique_ptr<NKEventDispatcher> EventDispatcher;
    std::unique_ptr<NKUuidGenerator> UuidGenerator;
    std::unique_ptr<NKWindow> Window;
    std::unique_ptr<NKSpriteCreator> SpriteCreator;
    std::unique_ptr<NKCoordinatesConverter> CoordinatesConverter;

    int CreateEntity();

    template<typename ActionType>
    void AddAction(std::uint_fast32_t tick, std::unique_ptr<ActionType> action) {
        action->SetEngine(this);
        action->Do();
        _actions[tick] = std::move(action);
    }

    void ReverseAction(std::uint_fast32_t tick) {
        if (_actions.contains(tick)) {
            _actions[tick]->Undo();
            _actions.erase(tick);
        }
    }

    template<typename ComponentType>
    void AddComponent(std::uint_fast32_t entityId, std::unique_ptr<ComponentType> component) {
        auto &componentsList = _components[entityId];
        componentsList.emplace_back(std::move(component));
    }

    template<typename ComponentType>
    void RemoveComponent(std::uint_fast32_t entityId) {
        auto &componentsList = _components[entityId];
        componentsList.remove_if([](const std::unique_ptr<NKComponent> &component) {
            //std::cout << "Removed a component";
            return typeid(*component) == typeid(ComponentType);
        });
    }

    template<typename ComponentType>
    ComponentType *GetComponent(std::uint_fast32_t entityId) {
        auto component = _components.find(entityId);
        if (component != _components.end()) {
            for (const auto &component: component->second) {
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
        auto group = _groups.find(groupType);
        if (group != _groups.end()) {
            // Group exists, add the system to the existing group
            //it->second.insert()
            group->second.emplace(group->second.size(), std::move(system));
        } else {
            // Group doesn't exist, create it and add the system
            std::map<std::uint_fast32_t, std::unique_ptr<NKSystem> > newGroup;
            // Replace std::set with your preferred container type
            newGroup.emplace(0, std::move(system)); // Add system to the new group
            _groups.emplace(groupType, std::move(newGroup)); // Initialize the group in the map
        }
    }

    void PrintAllSystem() {
        std::cout << "\n" << "Printing all systems" << "\n";
        std::cout << "---------------\n---------------\n";
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

            std::cout << "---------------\n---------------\n";
        }
    }

    bool IsRewinding();

    void Quit();

    bool Quitting();

    //TODO: create a world class (wrapper for systems and components)
    std::map<std::uint_fast16_t, std::list<std::unique_ptr<NKComponent> > > _components;
    std::map<NKGroupType, std::map<std::uint_fast16_t, std::unique_ptr<NKSystem> > > _groups;
    //TODO: make a list of actions
    //Tick
    std::map<std::uint_fast16_t, std::unique_ptr<NKReversibleAction> > _actions;

private:
    std::uint_fast32_t _entityId;
    std::uint_fast32_t _currentTick;
    bool _isRewinding;
    bool _isPaused;
    bool _isQuiting;
    std::uint_fast64_t _currentFrameTime = SDL_GetPerformanceCounter();
    std::uint_fast64_t _lastFrameTime = 0;
    double _deltaTime = 0;
};


#endif //NKENGINE_NKENGINE_H
