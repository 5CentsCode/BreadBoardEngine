#pragma once
#include <stdint.h>
#include <glm/glm.hpp>

#include <Windows.h> // TEMP?
#include <winnt.h> // TEMP?

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

#define VEC3_RIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define VEC3_LEFT (-VEC3_RIGHT)

#define VEC3_UP glm::vec3(0.0f, 1.0f, 0.0f)
#define VEC3_DOWN (-VEC3_UP)

#define VEC3_FORWARD glm::vec3(0.0f, 0.0f, 1.0f)
#define VEC3_BACKWARD (-VEC3_FORWARD)