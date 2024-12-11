#pragma once
#include <Typedefs.h>

// TODO Move elsewhere.
// That way we can utilize this during compile time
// to make sure all of our shaders are valid.
#define MAX_UNIFORM_NAME_LENGTH 64

struct Shader
{
public:
    uint32 Id;
    std::unordered_map<uint64, int32> UniformLocationMap;

public:
    void Bind() const;
    void Unbind() const;
    bool IsBound() const;

    void SetUniform(const char* name, const int32& value) const;
    void SetUniform(const char* name, const uint32& value) const;
    void SetUniform(const char* name, const float& value) const;

    void SetUniform(const char* name, const glm::ivec2& value) const;
    void SetUniform(const char* name, const glm::ivec3& value) const;
    void SetUniform(const char* name, const glm::ivec4& value) const;

    void SetUniform(const char* name, const glm::uvec2& value) const;
    void SetUniform(const char* name, const glm::uvec3& value) const;
    void SetUniform(const char* name, const glm::uvec4& value) const;

    void SetUniform(const char* name, const glm::vec2& value) const;
    void SetUniform(const char* name, const glm::vec3& value) const;
    void SetUniform(const char* name, const glm::vec4& value) const;

    void SetUniform(const char* name, const glm::mat2& value, const bool transpose = false) const;
    void SetUniform(const char* name, const glm::mat2x3& value, const bool transpose = false) const;
    void SetUniform(const char* name, const glm::mat2x4& value, const bool transpose = false) const;

    void SetUniform(const char* name, const glm::mat3& value, const bool transpose = false) const;
    void SetUniform(const char* name, const glm::mat3x2& value, const bool transpose = false) const;
    void SetUniform(const char* name, const glm::mat3x4& value, const bool transpose = false) const;

    void SetUniform(const char* name, const glm::mat4& value, const bool transpose = false) const;
    void SetUniform(const char* name, const glm::mat4x2& value, const bool transpose = false) const;
    void SetUniform(const char* name, const glm::mat4x3& value, const bool transpose = false) const;

private:
    void PopulateUniformLocationMap();

    bool TryToFindUniform(const char* name, int32& uniformLocation) const;
};

Shader LoadShader(const char* vertexFileName, const char* fragmentFileName);