#pragma once
#include "Typedefs.h"

enum PixelFormat : uint8
{
    Grayscale = 1,      // 8 bit per pixel (no alpha)
    GrayscaleAlpha,     // 8*2 bpp (2 channels)
    R5G6B5,             // 16 bpp
    RGB8,               // 24 bpp
    R5G5B5A1,           // 16 bpp (1 bit alpha)
    RGBA4,              // 16 bpp (4 bit alpha)
    RGBA8,              // 32 bpp
    R32,                // 32 bpp (1 channel - float)
    RGB32,              // 32*3 bpp (3 channels - float)
    RGBA32,             // 32*4 bpp (4 channels - float)
    DXT1_RGB,           // 4 bpp (no alpha)
    DXT1_RGBA,          // 4 bpp (1 bit alpha)
    DXT3_RGBA,          // 8 bpp
    DXT5_RGBA,          // 8 bpp
    ETC1_RGB,           // 4 bpp
    ETC2_RGB,           // 4 bpp
    ETC2_EAC_RGBA,      // 8 bpp
    PVRT_RGB,           // 4 bpp
    PVRT_RGBA,          // 4 bpp
    ASTC_4x4_RGBA,      // 8 bpp
    ASTC_8x8_RGBA       // 2 bpp
};

struct Image
{
public:
    void* Data;
    int32 Width;
    int32 Height;
    int8 MipMaps;
    PixelFormat Format;
};

Image LoadImageFromFile(const char* fileName);
void UnloadImage(Image& image);