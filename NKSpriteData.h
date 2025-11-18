//
// Created by r1nge on 10/27/25.
//

#ifndef NKENGINE_NKSPRITEDATA_H
#define NKENGINE_NKSPRITEDATA_H


struct NKSpriteData {
    int positionX;
    int positionY;
    int spriteWidth = 64;
    int spriteHeight = 64;
    int texturePositionX;
    int texturePositionY;
    int textureWidth = 64;
    int textureHeight = 64;
    int layer;
    int colorR = 255;
    int colorG = 255;
    int colorB = 255;
};


#endif //NKENGINE_NKSPRITEDATA_H
