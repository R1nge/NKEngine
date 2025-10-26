//
// Created by r1nge on 10/19/25.
//

#include "NKReversibleVector2Int.h"

NKReversibleVector2Int::NKReversibleVector2Int(int x, int y) {
    X = new NKReversibleInt(x, x);
    Y = new NKReversibleInt(y, y);
}
