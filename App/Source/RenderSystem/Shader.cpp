#include "pch.h"

#include "Shader.h"
#include <string>
#include <fstream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(StringRef vertexShaderFilepath,
			   StringRef fragmentShaderFilepath)
{
	const GLuint vertexShader   = CompileShader(vertexShaderFilepath, ShaderType::Vertex);
	const GLuint fragmentShader = CompileShader(fragmentShaderFilepath, ShaderType::Fragment);

	const GLuint shaderProgram  = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint isLinked = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		LOG(infoLog.data());
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_ID = shaderProgram;
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::Bind() const
{
	glUseProgram(m_ID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetInt(StringRef uniformName,
                    const int value) const
{
	const GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	glUniform1i(location, value);
}

void Shader::SetIntArray(StringRef uniformName,
						 int* values,
                         const Uint32 count) const
{
	const GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	glUniform1iv(location, count, values);
}

void Shader::SetFloat(StringRef uniformName,
                      const float value) const
{
	const GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	glUniform1f(location, value);
}

void Shader::SetFloat2(StringRef uniformName,
					   const glm::vec2& value) const
{
	const GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	glUniform2f(location, value.x, value.y);
}

void Shader::SetFloat3(StringRef uniformName,
					   const glm::vec3& value) const
{
	const GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetFloat4(StringRef uniformName,
					   const glm::vec4& value) const
{
	const GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetMat3(StringRef uniformName,
					 const glm::mat3& value) const
{
	const GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(StringRef uniformName,
					 const glm::mat4& value) const
{
	const GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::GetID() const
{
	return m_ID;
}

String Shader::ReadFileAsString(StringRef filepath) const
{
	String result;
	std::ifstream fileStream(filepath, std::ios::in);
	String line = String();

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		line += "\n";
		result += line;
	}

	fileStream.close();
	return result;
}

GLuint Shader::CompileShader(StringRef filepath,
                             const ShaderType shaderType) const
{
	GLuint shader = 0;
	switch (shaderType)
	{
		case ShaderType::Vertex:
		{
			shader = glCreateShader(GL_VERTEX_SHADER);
		} break;
		case ShaderType::Fragment:
		{
			shader = glCreateShader(GL_FRAGMENT_SHADER);
		} break;
	}

	const String shaderStr = ReadFileAsString(filepath.c_str());
	const char* shaderSrc = shaderStr.c_str();
	glShaderSource(shader, 1, &shaderSrc, nullptr);
	glCompileShader(shader);
	return shader;
}
