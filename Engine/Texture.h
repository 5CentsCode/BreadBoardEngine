#pragma once
#include "Typedefs.h"
#include "Resource.h"

class Texture : public Resource
{
public:
	Texture(Guid guid, std::string name, std::vector<uint8>& pixelData, int32 width, int32 height, int32 channels);
	~Texture();

public:
	void Upload();
	void Bind();

private:
	bool m_dirty;

	uint32 m_id;
	std::vector<uint8> m_pixelData;
	int32 m_width;
	int32 m_height;
	int32 m_channels;
};
