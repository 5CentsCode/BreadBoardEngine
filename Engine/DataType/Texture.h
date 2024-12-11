#pragma once
#include "Typedefs.h"
#include "Image.h"

struct Texture
{
    uint32 Id;
    int32 Width;
    int32 Height;
    int32 MipMaps;
    PixelFormat Format;
};

Texture CreateColorTexture(const Color& color);

Texture LoadTexture(const char* filename);
Texture LoadTextureFromImage(Image& image);

void DrawTexture(const Texture& texture, const glm::vec2& position, const Color& tint);