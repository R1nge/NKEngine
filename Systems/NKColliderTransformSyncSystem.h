//
// Created by r1nge on 10/27/25.
//

#ifndef NKENGINE_NKCOLLISIONTRANSFORMSYNC_H
#define NKENGINE_NKCOLLISIONTRANSFORMSYNC_H
#include "NKSystem.h"


class NKColliderTransformSyncSystem : public NKSystem {
    void Update(double deltaTime) override;
};


#endif //NKENGINE_NKCOLLISIONTRANSFORMSYNC_H