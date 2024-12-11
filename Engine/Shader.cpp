#include "Shader.h"
#include <filesystem> // TEMP
#include <fstream> // TEMP
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

void Shader::Bind() const
{
    // Don't want to assert, but this should notify when
    // the shader is already bound.
    // It indicates that there might be some performance improvements
    // to be had, as a program should only be bound if it isn't already.
    // assert(!IsBound());
    glUseProgram(Id);
}

void Shader::Unbind() const
{
    assert(IsBound());
    glUseProgram(0);
}

bool Shader::IsBound() const
{
#ifdef _DEBUG
    int32 activeProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);
    return (uint32)activeProgram == Id;
#else
    return false;
#endif
}

void Shader::PopulateUniformLocationMap()
{
    int attributeCount;
    glGetProgramiv(Id, GL_ACTIVE_UNIFORMS, &attributeCount);

    int uniformNameLength;
    int uniformSize;
    uint32 uniformType;
    char uniformName[MAX_UNIFORM_NAME_LENGTH];
    int uniformLocation;

    UniformLocationMap.reserve(attributeCount);

    for (int i = 0; i < attributeCount; ++i)
    {
        glGetActiveUniform(Id, i, MAX_UNIFORM_NAME_LENGTH, &uniformNameLength, &uniformSize, &uniformType, uniformName);
        uniformLocation = glGetUniformLocation(Id, uniformName);

        uint64 nameHash = std::hash<std::string>{}(uniformName);

        UniformLocationMap[nameHash] = uniformLocation;
    }
}

inline bool Shader::TryToFindUniform(const char* name, int32& uniformLocation) const
{
    // assert(IsBound());

    uint64 nameHash = std::hash<std::string>{}(name);
    auto uniform = UniformLocationMap.find(nameHash);
    bool uniformExists = uniform != UniformLocationMap.end();

    // TODO:
    // I want to be notified when trying to bind to an unknown uniform
    // But I also don't want the program to crash.
    // assert(uniformExists);
    if (uniformExists)
    {
        uniformLocation = uniform->second;
    }

    return uniformExists;
}

void Shader::SetUniform(const char* name, const int32& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform1iv(uniformLocation, 1, &value);
    }
}

void Shader::SetUniform(const char* name, const uint32& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform1uiv(uniformLocation, 1, &value);
    }
}

void Shader::SetUniform(const char* name, const float& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform1fv(uniformLocation, 1, &value);
    }
}

void Shader::SetUniform(const char* name, const glm::ivec2& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform2iv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::ivec3& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform3iv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::ivec4& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform4iv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::uvec2& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform2uiv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::uvec3& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform3uiv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::uvec4& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform4uiv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::vec2& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform2fv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::vec3& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::vec4& value) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat2& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix2fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat2x3& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix2x3fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat2x4& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix2fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat3& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix3fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat3x2& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix3x2fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat3x4& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix3x4fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat4& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix4fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat4x2& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix4x2fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

void Shader::SetUniform(const char* name, const glm::mat4x3& value, bool transpose) const
{
    int32 uniformLocation;
    if (TryToFindUniform(name, uniformLocation))
    {
        glUniformMatrix4x3fv(uniformLocation, 1, transpose, glm::value_ptr(value));
    }
}

std::vector<char> ReadFile(std::string filePath)
{
    std::vector<char> buffer;
    bool fileExists = std::filesystem::exists(filePath);
    if (fileExists)
    {
        std::ifstream file(filePath);
        buffer.resize((uint64)std::filesystem::file_size(filePath));
        file.read(buffer.data(), buffer.size());
        file.close();
    }

    return buffer;
}

Shader LoadShader(const char* vertexFileName, const char* fragmentFileName)
{
    std::vector<char> vertexSource = ReadFile(vertexFileName);
    std::vector<char> fragmentSource = ReadFile(fragmentFileName);

    Shader shader;

    const char* vSource = vertexSource.data();
    const char* fSource = fragmentSource.data();

    int success;
    char infoLog[512];

    uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vSource, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR::OpenGLShader::VERTEX::COMPILATION_FAILED\n");
        printf("\t%s\n", infoLog);
    };

    uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fSource, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("ERROR::OpenGLShader::FRAGMENT::COMPILATION_FAILED\n");
        printf("\t%s\n", infoLog);
    };

    shader.Id = glCreateProgram();
    glAttachShader(shader.Id, vertex);
    glAttachShader(shader.Id, fragment);
    glLinkProgram(shader.Id);
    glGetProgramiv(shader.Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader.Id, 512, NULL, infoLog);
        printf("ERROR::OpenGLShader::PROGRAM::LINKING_FAILED\n");
        printf("\t%s\n", infoLog);
    };

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    int attributeCount;
    glGetProgramiv(shader.Id, GL_ACTIVE_UNIFORMS, &attributeCount);

    int uniformNameLength;
    int uniformSize;
    uint32 uniformType;
    char uniformName[MAX_UNIFORM_NAME_LENGTH];
    int uniformLocation;

    shader.UniformLocationMap.reserve(attributeCount);

    for (int i = 0; i < attributeCount; ++i)
    {
        glGetActiveUniform(shader.Id, i, MAX_UNIFORM_NAME_LENGTH, &uniformNameLength, &uniformSize, &uniformType, uniformName);
        uniformLocation = glGetUniformLocation(shader.Id, uniformName);

        uint64 nameHash = std::hash<std::string>{}(uniformName);

        shader.UniformLocationMap[nameHash] = uniformLocation;
    }

    return shader;
}