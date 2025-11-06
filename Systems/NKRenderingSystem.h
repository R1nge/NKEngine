//
// Created by r1nge on 10/25/25.
//

#ifndef NKENGINE_NKRENDERER_H
#define NKENGINE_NKRENDERER_H

#include "NKSystem.h"
#include "../NKWindow.h"
#include "../cmake-build-debug/_deps/imgui-src/imgui.h"
#include "../cmake-build-debug/_deps/imgui-src/backends/imgui_impl_sdl2.h"
#include "../cmake-build-debug/_deps/imgui-src/backends/imgui_impl_sdlrenderer2.h"
#include "../cmake-build-debug/_deps/imgui-src/backends/imgui_impl_opengl3.h"
#include "../debug_imgui_renderer.h"

class NKRenderingSystem : public NKSystem {
public:
    NKRenderingSystem(NKWindow *window);

    void Update(double deltaTime) override;

    void Render();

private:
    NKWindow *_window;
};


#endif //NKENGINE_NKRENDERER_H
