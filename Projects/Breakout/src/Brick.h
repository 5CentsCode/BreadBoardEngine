#pragma once
#include <Typedefs.h>

enum BrickType
{
	None,
	Solid,
	Breakable
};

struct Brick
{
	glm::vec3 Color;
	BrickType BrickType;
	int32 Health;
	bool Active;
};