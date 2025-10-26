//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKENGINE_H
#define NKENGINE_NKENGINE_H
#include <memory>
#include <SDL_keycode.h>

#include "Events/NKEventDispatcher.h"
#include "NKRenderer.h"
#include "Systems/NKSystem.h"
#include "NKUuidGenerator.h"

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

    SDL_Keycode GetLastKeyInput() const;
    std::unique_ptr<NKEventDispatcher> EventDispatcher;
    std::unique_ptr<NKUuidGenerator> UuidGenerator;
    std::unique_ptr<NKRenderer> Renderer;

    int CreateEntity();

    template<typename ComponentType>
    void AddComponent(int entityId, std::unique_ptr<ComponentType> component) {
        _components[entityId] = std::move(component);
    }

    template<typename ComponentType>
    ComponentType *getComponent(int entityId) {
        auto it = _components.find(entityId);
        if (it != _components.end()) {
            return dynamic_cast<ComponentType *>(it->second.get());
        }
        // Entity or component not found
        return nullptr;
    }

    template<typename SystemType>
    void addSystem(std::unique_ptr<SystemType> system) {
        system->SetEngine(this);
        _systems[_systemId] = std::move(system);
        _systemId++;
    }

private:
    int _systemId;
    int _entityId;
    int _currentTick;
    bool _isRewinding;
    bool _isPaused;
    SDL_Keycode _lastKeyInput;
    std::map<int, std::unique_ptr<NKComponent> > _components;
    std::map<int, std::unique_ptr<NKSystem> > _systems;
};


#endif //NKENGINE_NKENGINE_H
