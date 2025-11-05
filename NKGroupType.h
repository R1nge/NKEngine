//
// Created by r1nge on 10/28/25.
//

#ifndef NKENGINE_NKGROUPTYPE_H
#define NKENGINE_NKGROUPTYPE_H
#include <iosfwd>
#include <string>


enum class NKGroupType {
    NKInput = 0,
    NKTransform = 1,
    NKPhysics = 2,
    NKCollision = 3,
    NKCollisionReset = 4,
    NKRendering = 5,
};

std::ostream &operator<<(std::ostream &stream, const NKGroupType groupType);

#endif //NKENGINE_NKGROUPTYPE_H
