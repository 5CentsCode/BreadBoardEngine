#pragma once
#include <string>
#include <unordered_map>
#include "Resource.h"

// TODO Move elseware.
// That way we can utilize this during compile time
// to make sure all of our shaders are valid.
#define MAX_UNIFORM_NAME_LENGTH 64

class Shader : public Resource
{
public:
	Shader(Guid& guid, std::string& name, std::vector<char>& vertexSource, std::vector<char>& fragmentSource);
	~Shader();

public:
	void Bind() const;
	void Unbind() const;
	bool IsBound() const;

	void SetUniform(const char* name, const int32& value);
	void SetUniform(const char* name, const uint32& value);
	void SetUniform(const char* name, const float& value);

	void SetUniform(const char* name, const glm::ivec2& value);
	void SetUniform(const char* name, const glm::ivec3& value);
	void SetUniform(const char* name, const glm::ivec4& value);

	void SetUniform(const char* name, const glm::uvec2& value);
	void SetUniform(const char* name, const glm::uvec3& value);
	void SetUniform(const char* name, const glm::uvec4& value);

	void SetUniform(const char* name, const glm::vec2& value);
	void SetUniform(const char* name, const glm::vec3& value);
	void SetUniform(const char* name, const glm::vec4& value);

	void SetUniform(const char* name, const glm::mat2& value, const bool transpose = false);
	void SetUniform(const char* name, const glm::mat2x3& value, const bool transpose = false);
	void SetUniform(const char* name, const glm::mat2x4& value, const bool transpose = false);

	void SetUniform(const char* name, const glm::mat3& value, const bool transpose = false);
	void SetUniform(const char* name, const glm::mat3x2& value, const bool transpose = false);
	void SetUniform(const char* name, const glm::mat3x4& value, const bool transpose = false);

	void SetUniform(const char* name, const glm::mat4& value, const bool transpose = false);
	void SetUniform(const char* name, const glm::mat4x2& value, const bool transpose = false);
	void SetUniform(const char* name, const glm::mat4x3& value, const bool transpose = false);

private:
	void PopulateUniformLocationMap();

	bool TryToFindUniform(const char* name, int32& uniformLocation) const;

private:
	int32 m_id;
	std::unordered_map<uint64, int32> m_uniformLocationMap;
};