//
// Created by r1nge on 10/25/25.
//

#include "NKRenderingSystem.h"
#include "../NKEngine.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "../Components/NKCameraTag.h"
#include "../Components/NKRenderComponent.h"
#include "../Components/NKReversiblePositionComponent.h"

NKRenderingSystem::NKRenderingSystem(NKWindow *window) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        }

        _window = window;
    }
}

float CalculateAngle(float sinValue, float cosValue) {
    // Calculate angle in radians using atan2
    float angleRadians = atan2(sinValue, cosValue);

    // Convert radians to degrees
    float angleDegrees = angleRadians * (180.0f / M_PI);

    // Normalize the angle to the range [0, 360)
    if (angleDegrees < 0) {
        angleDegrees += 360;
    }

    float clockwiseAngle = 360 - angleDegrees;

    // Normalize the angle to range [0, 360)
    if (clockwiseAngle >= 360) {
        clockwiseAngle -= 360;
    }

    return clockwiseAngle;
}

void EntitiesInspector(bool my_tool_active, NKEngine *engine) {
    ImGui::Begin("Entities inspector", &my_tool_active, ImGuiWindowFlags_MenuBar);
    ImGui::Separator(); // Adds a horizontal separator
    ImGui::Text("Entities");
    ImGui::Separator(); // Adds a horizontal separator
    for (const auto &[entityId, componentList]: engine->_components) {
        // Create a header for each entity
        ImGui::Text("Entity ID: %lu", entityId);

        // Display the components
        for (const auto &component: componentList) {
            std::string typeName = typeid(*component).name();
            std::string remove = "Component";
            auto iter = typeName.find(remove);

            while (iter != std::string::npos) {
                typeName.erase(iter, remove.length());
                iter = typeName.find(remove, iter);
            }
            size_t startPos = 0;
            while (startPos < typeName.length() && std::isdigit(typeName[startPos])) {
                ++startPos;
            }

            std::string cleanTypeName = typeName.substr(startPos);
            ImGui::BulletText("%s", cleanTypeName.c_str()); // Show component's name
            // Add more details about the component if needed
        }

        ImGui::Separator(); // Adds a horizontal separator for clarity
    }

    ImGui::End();
}

void SystemsInspector(bool my_tool_active, NKEngine *engine) {
    ImGui::Begin("Systems inspector", &my_tool_active, ImGuiWindowFlags_MenuBar);
    ImGui::Separator();
    ImGui::Text("Systems");
    ImGui::Separator(); // Adds a horizontal separator
    for (const auto &[group, systemMap]: engine->_groups) {
        // Create a header for each entity
        ImGui::Text("Group ID: %lu", group);

        // Display the systems
        for (const auto &pair: systemMap) {
            std::string typeName = typeid(*pair.second.get()).name();
            typeName = typeName.substr(0, typeName.size() - 6);

            size_t startPos = 0;
            while (startPos < typeName.length() && std::isdigit(typeName[startPos])) {
                ++startPos;
            }

            std::string cleanTypeName = typeName.substr(startPos);
            ImGui::BulletText("%s", cleanTypeName.c_str()); // Show component's name
            // Add more details about the component if needed
        }

        ImGui::Separator(); // Adds a horizontal separator for clarity
    }

    ImGui::End();
}

void RenderSprites(NKEngine *engine, NKWindow *_window) {
    std::vector<std::pair<int, NKRenderComponent *> > renderQueue;

    for (const auto &pair: engine->_components) {
        auto camera = engine->GetComponent<NKCameraTag>(pair.first);
        if (camera != nullptr) {
            auto cameraPosition = engine->GetComponent<NKReversiblePositionComponent>(pair.first);
            if (cameraPosition != nullptr) {
                for (const auto &pair2: engine->_components) {
                    auto renderComponent = engine->GetComponent<NKRenderComponent>(pair2.first);

                    if (renderComponent != nullptr) {
                        renderQueue.emplace_back(pair2.first, renderComponent);
                    }
                }
            }
        }
    }

    std::sort(renderQueue.begin(), renderQueue.end(), [](const auto &a, const auto &b) {
        return a.second->data->layer < b.second->data->layer; // Sort in ascending order
    });

    for (const auto &pair: engine->_components) {
        auto camera = engine->GetComponent<NKCameraTag>(pair.first);
        if (camera != nullptr) {
            auto cameraPosition = engine->GetComponent<NKReversiblePositionComponent>(pair.first);
            for (auto &pair2: renderQueue) {
                auto worldPosition = engine->GetComponent<NKReversiblePositionComponent>(pair2.first);
                if (worldPosition != nullptr) {
                    auto renderComponent = pair2.second;
                    renderComponent->spriteRect->x =
                            worldPosition->position->X->currentValue - static_cast<double>(renderComponent->spriteRect->
                                w) / static_cast<double>(2) - cameraPosition->position->X->currentValue;
                    renderComponent->spriteRect->y =
                            worldPosition->position->Y->currentValue - static_cast<double>(renderComponent->spriteRect->
                                h) / static_cast<double>(2) - cameraPosition->position->Y->currentValue;
                    auto rigidBody = engine->GetComponent<NKRigidBodyComponent>(pair2.first);
                    if (rigidBody != nullptr) {
                        SDL_RenderCopyExF(_window->Renderer, renderComponent->texture, renderComponent->textureRect,
                                          renderComponent->spriteRect,
                                          CalculateAngle(rigidBody->rigidBody->GetRotation().s,
                                                         rigidBody->rigidBody->GetRotation().c), nullptr,
                                          SDL_FLIP_NONE);
                    } else {
                        SDL_RenderCopyF(_window->Renderer, renderComponent->texture, renderComponent->textureRect,
                                        renderComponent->spriteRect);
                    }
                }
            }
        }
    }
}

void NKRenderingSystem::Update(double deltaTime) {
    SDL_RenderClear(_window->Renderer);
    RenderImgui();
    RenderSprites(engine, _window);
    SDL_RenderPresent(_window->Renderer);
}


void NKRenderingSystem::RenderImgui() {
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    bool my_tool_active = true;
    ImGui::Begin("FPS", &my_tool_active, ImGuiWindowFlags_MenuBar);
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
    //ENTITIES START
    EntitiesInspector(my_tool_active, engine);

    //INSPECTOR SYSTEMS
    SystemsInspector(my_tool_active, engine);

    SDL_RenderSetScale(_window->Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_RenderSetScale(_window->Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);


    engine->debug_renderer.DrawShapes(engine->World); // Draw Box2D shapes.
    engine->debug_renderer.DrawModeToggles();


    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), _window->Renderer);
}
