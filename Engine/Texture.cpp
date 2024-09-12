#include "Texture.h"
#include <glad/glad.h>
#include <stb_image.h>

Texture::Texture(Guid guid, std::string name, std::vector<uint8>& pixelData, int32 width, int32 height, int32 channels)
	: Resource(guid, name)
{
	m_id = 0;

	m_pixelData = pixelData;
	m_width = width;
	m_height = height;
	m_channels = channels;

	m_dirty = true;
}

Texture::~Texture()
{
	m_pixelData.clear();
}

void Texture::Upload()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int32 format = 0;
	switch (m_channels)
	{
		case 1:
		{
			format = GL_RED;
			break;
		}

		case 3:
		{
			format = GL_RGB;
			break;
		}

		case 4:
		{
			format = GL_RGBA;
			break;
		}

		default:
		{
			printf("Unsupported format");
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_pixelData.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

int32 Texture::GetId() const
{
	return m_id;
}

int32 Texture::GetWidth() const
{
	return m_width;
}

int32 Texture::GetHeight() const
{
	return m_height;
}

glm::ivec2 Texture::GetSize() const
{
	return glm::ivec2(m_width, m_height);
}
