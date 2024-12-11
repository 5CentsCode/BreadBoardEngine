#include "Texture.h"
#include <glad/glad.h>

Texture CreateColorTexture(const Color& color)
{
    Color normalColor = glm::normalize(color);
    uint8 pixelData[] =
    {
        (uint8)(color.r * 255),
        (uint8)(color.g * 255),
        (uint8)(color.b * 255),
        (uint8)(color.a * 255)
    };

    Image image = { 0 };
    image.Data = pixelData;
    image.Width = 1;
    image.Height = 1;
    image.MipMaps = 0;
    image.Format = PixelFormat::RGBA8;

    Texture texture = { 0 };
    if (image.Data != NULL)
    {
        texture = LoadTextureFromImage(image);
    }

    return texture;
}

Texture LoadTexture(const char* fileName)
{
    Texture texture = { 0 };

    Image image = LoadImageFromFile(fileName);

    if (image.Data != NULL)
    {
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    return texture;
}

Texture LoadTextureFromImage(Image& image)
{
    Texture texture = { 0 };

    if (image.Width > 0 && image.Height > 0)
    {
        glGenTextures(1, &texture.Id);
        glBindTexture(GL_TEXTURE_2D, texture.Id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        uint32 format = GL_NONE;
        switch (image.Format)
        {
            case PixelFormat::RGBA8:
                format = GL_RGBA;
                break;
            case PixelFormat::RGB8:
                format = GL_RGB;
                break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE, image.Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    texture.Width = image.Width;
    texture.Height = image.Height;
    texture.MipMaps = image.MipMaps;
    texture.Format = image.Format;

    return texture;
}

void DrawTexture(const Texture& texture, const glm::vec2& position, const Color& tint)
{
    REFERENCE(texture);
    REFERENCE(position);
    REFERENCE(tint);

    /*
    if (texture.Id > 0)
    {
        float textureWidth = (float)texture.Width;
        float textureHeight = (float)texture.Height;

        glBindTexture(GL_TEXTURE_2D, texture.Id);
    }

    Rect source = Rect(0.0f, 0.0f, texture.Width, texture.Height);
    Rect dest = Rect(position.x, position.y, texture.Width, texture.Height);
    glm::vec2 origin = glm::vec2(0.0f);
    */
}