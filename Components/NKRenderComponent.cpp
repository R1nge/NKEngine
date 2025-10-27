//
// Created by r1nge on 10/26/25.
//

#include "NKRenderComponent.h"

NKRenderComponent::NKRenderComponent(SDL_Texture *Texture, SDL_Rect *SpriteRect, SDL_Rect *TextureRect,
                                     NKSpriteData *Data) {
    texture = Texture;
    spriteRect = SpriteRect;
    textureRect = TextureRect;
    data = Data;
}
