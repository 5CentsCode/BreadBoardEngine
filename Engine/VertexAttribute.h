#pragma once
#include "Typedefs.h"
#include <vector>

enum AttributeType : uint32
{
	Bool = 0x8B56,

	Int8 = 0x1400,
	Int16 = 0x1402,
	Int32 = 0x1404,

	Uint8 = 0x1401,
	Uint16 = 0x1403,
	Uint32 = 0x1405,

	Float = 0x1406,
	Double = 0x140A,

	Invalid = 0x0501
};

struct VertexAttribute
{
	uint8 LayoutLocation = 0;
	uint32 Count = 0;
	AttributeType Type = AttributeType::Invalid;
	bool Normalize = false;
	int32 Stride = 0;
	uint64 Offset = 0;
};

struct VertexDescription
{
	std::vector<VertexAttribute> Attributes;
};