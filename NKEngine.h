//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKENGINE_H
#define NKENGINE_NKENGINE_H
#include <map>
#include <memory>
#include <SDL_keycode.h>

#include "NKSpriteCreator.h"
#include "Events/NKEventDispatcher.h"
#include "Systems/NKRenderingSystem.h"
#include "Systems/NKSystem.h"
#include "NKUuidGenerator.h"
#include "Components/NKComponent.h"

//World -> systems
//World -> entities
//Engine -> world
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

    template<typename SystemType>
    void AddSystem(std::unique_ptr<SystemType> system) {
        system->SetEngine(this);
        _systems[_systemId] = std::move(system);
        _systemId++;
    }

    bool IsRewinding();

    std::map<int, std::list<std::unique_ptr<NKComponent> > > _components;
    std::map<int, std::unique_ptr<NKSystem> > _systems;
private:
    int _systemId;
    int _entityId;
    int _currentTick;
    bool _isRewinding;
    bool _isPaused;
};


#endif //NKENGINE_NKENGINE_H
