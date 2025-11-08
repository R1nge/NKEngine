//
// Created by r1nge on 10/19/25.
//

#include "NKEngine.h"

//TODO: aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
#include "cmake-build-release/_deps/imgui-src/imgui.h"
#include "cmake-build-release/_deps/imgui-src/backends/imgui_impl_sdl2.h"
#include "cmake-build-release/_deps/imgui-src/backends/imgui_impl_sdlrenderer2.h"
#include "cmake-build-release/_deps/imgui-src/backends/imgui_impl_opengl3.h"
#include "Systems/NKTransformRigidBodySyncSystem.h"

NKEngine::NKEngine() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // IF using Docking Branch
    ImGui::StyleColorsDark();

    World = b2::World::Params{};
    World.SetGravity(b2Vec2(0, -9.81));
    EventDispatcher = std::make_unique<NKEventDispatcher>();
    UuidGenerator = std::make_unique<NKUuidGenerator>();
    Window = std::make_unique<NKWindow>();
    SpriteCreator = std::make_unique<NKSpriteCreator>(Window->Renderer);
    CoordinatesConverter = std::make_unique<NKCoordinatesConverter>();
    AudioPlayer = std::make_unique<NKAudioPlayer>();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(Window->Window, Window->Renderer);
    ImGui_ImplSDLRenderer2_Init(Window->Renderer);

    debug_renderer = b2::DebugImguiRenderer();

    auto cameraEntity = CreateEntity();
    AddComponent<NKReversiblePositionComponent>(cameraEntity,
                                                std::make_unique<NKReversiblePositionComponent>(-500, 590));
    AddComponent<NKCameraTag>(cameraEntity, std::make_unique<NKCameraTag>());


    AddSystem(NKGroupType::NKTransform, std::make_unique<NKTransformSystem>()); //Rewind
    AddSystem(NKGroupType::NKInput, std::make_unique<NKInputSystem>()); //Input
    AddSystem(NKGroupType::NKPhysics, std::make_unique<NKTransformRigidBodySyncSystem>()); //Sync rigidbody
    AddSystem(NKGroupType::NKRendering, std::make_unique<NKRenderingSystem>(Window.get()));

    _isPaused = false;
}

NKEngine::~NKEngine() {
    //SDL_DestroyRenderer(Renderer);
    //Renderer = nullptr;
    //SDL_DestroyWindow(Window);
    //Window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

void NKEngine::Update() {
    if (!_isPaused || !_isQuiting) {
        if (_isRewinding == false) {
            _currentTick++;
        } else {
            if (_currentTick == 0) {
                _isRewinding = false;
            } else {
                ReverseAction(_currentTick);
                _currentTick--;
            }
        }


        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT) {
                Quit();
                //TODO: investigate why it doesn't work with RU on Ubuntu 24.04
                //TODO: it's possible that I would have to migrate to SDL3
            } else if (e.type == SDL_KEYDOWN) {
                //std::cout << "Last key" << e.key.keysym.scancode;
                for (const auto &pair: _components) {
                    auto inputComponent = GetComponent<NKInputComponent>(pair.first);
                    if (inputComponent != nullptr) {
                        inputComponent->LastKey = e.key.keysym.scancode;
                    }
                }
            } else if (e.type == SDL_KEYUP) {
                for (const auto &pair: _components) {
                    auto inputComponent = GetComponent<NKInputComponent>(pair.first);
                    if (inputComponent != nullptr) {
                        inputComponent->LastKey = SDL_SCANCODE_UNKNOWN;
                    }
                }
            }
        }


        _lastFrameTime = _currentFrameTime;
        _currentFrameTime = SDL_GetPerformanceCounter();
        _deltaTime = (_currentFrameTime - _lastFrameTime) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency());

        World.Step(1 / 60.f, 4);

        for (const auto &groupPair: _groups) {
            for (const auto &systemPair: groupPair.second) {
                systemPair.second->Update(_deltaTime);
            }
        }
    }
}

void NKEngine::StartRewind() {
    _isRewinding = true;
}

void NKEngine::StopRewind() {
    _isRewinding = false;
}

std::uint_fast32_t NKEngine::GetTick() const {
    return _currentTick;
}

int NKEngine::CreateEntity() {
    _entityId++;
    return _entityId;
}

void NKEngine::ReverseAction(std::uint_fast32_t tick) {
    if (_actions.contains(tick)) {
        _actions[tick]->Undo();
        _actions.erase(tick);
    }
}


void NKEngine::PrintAllSystem() {
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

bool NKEngine::IsRewinding() {
    return _isRewinding;
}

void NKEngine::Quit() {
    _isQuiting = true;
}

bool NKEngine::Quitting() {
    return _isQuiting;
}
