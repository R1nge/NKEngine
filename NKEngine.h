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


class NKEngine {
public:
    NKEngine();
    ~NKEngine();
    void Update();

    void Rewind();

    int GetTick();

    SDL_Keycode GetLastKeyInput() const;
    std::unique_ptr<NKEventDispatcher> EventDispatcher;
    std::unique_ptr<NKUuidGenerator> UuidGenerator;
    std::unique_ptr<NKRenderer> Renderer;

    template<typename ComponentType>
    void addComponent(int entityId, std::unique_ptr<ComponentType> component) {
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
    void addSystem(int systemId, std::unique_ptr<SystemType> system) {
        _systems[systemId] = std::move(system);
    }

private:
    int _currentTick;
    bool _isRewinding;
    bool _isPaused;
    SDL_Keycode _lastKeyInput;
    std::map<int, std::unique_ptr<NKComponent> > _components;
    std::map<int, std::unique_ptr<NKSystem> > _systems;
};


#endif //NKENGINE_NKENGINE_H
