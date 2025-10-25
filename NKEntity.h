//
// Created by r1nge on 10/25/25.
//

#ifndef NKENGINE_NKENTITY_H
#define NKENGINE_NKENTITY_H
#include "NKUuidGenerator.h"
#include "uuid.h"


class NKEntity {
public:
    NKEntity(uuids::uuid id);

    uuids::uuid Id;
};


#endif //NKENGINE_NKENTITY_H
