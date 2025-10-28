//
// Created by r1nge on 10/28/25.
//

#ifndef NKENGINE_NKGROUPTYPE_H
#define NKENGINE_NKGROUPTYPE_H
#include <iosfwd>
#include <string>


enum class NKGroupType {
    NKBeforeTransform = 0,
    NKTransform = 1,
    NKInput = 2,
    NKRendering = 3,
    NKCollisionTransformSync = 4,
    NKCollision = 5,
    NKCollisionReset = 6
};

std::ostream &operator<<(std::ostream &stream, const NKGroupType groupType);

#endif //NKENGINE_NKGROUPTYPE_H
