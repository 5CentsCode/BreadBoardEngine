#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image LoadImageFromFile(const char* fileName)
{
    Image image = { 0 };

    int32 channels;
    image.Data = stbi_load(fileName, &image.Width, &image.Height, &channels, 0);

    if (image.Data != NULL)
    {
        switch (channels)
        {
            case 1:
                image.Format = PixelFormat::Grayscale;
                break;
            case 2:
                image.Format = PixelFormat::GrayscaleAlpha;
                break;
            case 3:
                image.Format = PixelFormat::RGB8;
                break;
            case 4:
                image.Format = PixelFormat::RGBA8;
                break;
        }
    }

    return image;
}

void UnloadImage(Image& image)
{
    delete image.Data;
}