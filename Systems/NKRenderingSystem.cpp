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

void NKRenderingSystem::Update(double deltaTime) {
    Render();
}

void NKRenderingSystem::Render() {
    SDL_RenderClear(_window->Renderer);
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    //ImGui::ShowDemoWindow();
    bool my_tool_active = true;
    ImGui::Begin("Inspector", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) {
                /* Do stuff */
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                /* Do stuff */
            }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();

        ImGui::Separator(); // Adds a horizontal separator

        for (const auto &[entityId, componentList]: engine->_components) {
            // Create a header for each entity
            ImGui::Text("Entity ID: %u", entityId);

            // Display the components
            for (const auto &component: componentList) {
                //ImGui::BulletText("%s", component.);  // Show component's name
                // Add more details about the component if needed
            }

            ImGui::Separator(); // Adds a horizontal separator for clarity
        }
        ImGui::End();
    }

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
                    SDL_RenderCopyF(_window->Renderer, renderComponent->texture, renderComponent->textureRect,
                                    renderComponent->spriteRect);
                }
            }
        }
    }

    SDL_RenderSetScale(_window->Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_RenderSetScale(_window->Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), _window->Renderer);

    SDL_RenderPresent(_window->Renderer);
}
