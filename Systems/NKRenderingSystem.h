//
// Created by r1nge on 10/25/25.
//

#ifndef NKENGINE_NKRENDERER_H
#define NKENGINE_NKRENDERER_H

#include "NKSystem.h"
#include "../NKWindow.h"

class NKRenderingSystem : public NKSystem {
public:
    NKRenderingSystem(NKWindow *window);

    void Update() override;
    void Render();
    void Rewind(int tick);

private:
    NKWindow *_window;
};


#endif //NKENGINE_NKRENDERER_H
