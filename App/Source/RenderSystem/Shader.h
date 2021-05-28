#pragma once

#include "Utils/Log.h"
#include "glad.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils/TypeAlias.h"

enum class ShaderType
{
	Vertex,
	Fragment
};

class Shader final
{
public:
	explicit Shader(StringRef vertexShaderFilepath,
					StringRef fragmentShaderFilepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// UNIFORMS
	void SetInt(StringRef uniformName, int value) const;
	void SetIntArray(StringRef uniformName, int* values, Uint32 count) const;
	void SetFloat(StringRef uniformName, float value) const;
	void SetFloat2(StringRef uniformName, const glm::vec2& value) const;
	void SetFloat3(StringRef uniformName, const glm::vec3& value) const;
	void SetFloat4(StringRef uniformName, const glm::vec4& value) const;
	void SetMat3(StringRef uniformName, const glm::mat3& value) const;
	void SetMat4(StringRef uniformName, const glm::mat4& value) const;

	GLuint GetID() const;
private:
	GLuint m_ID;

	String ReadFileAsString(StringRef filepath) const;
	GLuint CompileShader(StringRef filepath, ShaderType shaderType) const;
};