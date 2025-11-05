//
// Created by r1nge on 10/28/25.
//

#include "NKGroupType.h"
std::ostream &operator<<(std::ostream &stream, const NKGroupType groupType) {
    std::string outPut = "";
    switch (groupType) {
        case NKGroupType::NKTransform:
            outPut = "NKTransform";
            break;
        case NKGroupType::NKInput:
            outPut = "NKInput";
            break;
        case NKGroupType::NKRendering:
            outPut = "NKRendering";
            break;
        case NKGroupType::NKPhysics:
            outPut = "NKPhysics";
            break;
        case NKGroupType::NKCollision:
            outPut = "NKCollision";
            break;
        case NKGroupType::NKCollisionReset:
            outPut = "NKCollisionReset";
            break;
        default:
            outPut = "Unknown NKGroupType";
            break;
    }
    stream << outPut;
    return stream;
}
