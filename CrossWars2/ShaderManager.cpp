#include "ShaderManager.h"
#include <vector>
#include <fstream>
#include "FileLoader.h"
#include <GLM/glm.hpp>


ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::setActiveShader(ProtoShader* t_proto_shader)
{
	m_loaded_shader = t_proto_shader;
}

ProtoShader* ShaderManager::getActiveShader() const
{
	return m_loaded_shader;
}

void ShaderManager::loadVertexShader(const char* t_filename)
{
	FileLoader fileLoader;
	auto str = fileLoader.loadFileToString(t_filename, SHADER);
	char const * vertexSourcePointer = str.c_str();

	m_vertex_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertex_id, 1, &vertexSourcePointer, nullptr);
	glCompileShader(m_vertex_id);
}

void ShaderManager::loadFragmentShader(const char* t_filename)
{
	FileLoader fileLoader;
	auto str = fileLoader.loadFileToString(t_filename, SHADER);
	char const * fragmentSourcePointer = str.c_str();

	m_fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragment_id, 1, &fragmentSourcePointer, nullptr);
	glCompileShader(m_fragment_id);
}

void ShaderManager::bindPrograms()
{
	m_program_id = glCreateProgram();
	glAttachShader(m_program_id, m_vertex_id);
	glAttachShader(m_program_id, m_fragment_id);
	glLinkProgram(m_program_id);

	GLint result = GL_FALSE;
	int infoLogLength;
	glGetProgramiv(m_program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(m_program_id, infoLogLength, nullptr, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glUseProgram(m_program_id);

	glDetachShader(m_program_id, m_vertex_id);
	glDetachShader(m_program_id, m_fragment_id);

	glDeleteShader(m_vertex_id);
	glDeleteShader(m_fragment_id);
}

GLuint ShaderManager::getProgramID()
{
	return m_program_id;
}

GLuint ShaderManager::getVariable(const char* t_var)
{
	return glGetUniformLocation(m_program_id, t_var);
}

void ShaderManager::bindAttribute(GLint t_attribute, const char* t_variable)
{
	glBindAttribLocation(m_program_id, t_attribute, t_variable);
}

void ShaderManager::loadFloat(GLint t_var_location, GLfloat t_value)
{
	glUniform1f(t_var_location, t_value);
}

void ShaderManager::loadVector(GLint t_var_location, glm::vec3 t_value)
{
	glUniform3f(t_var_location, t_value.x, t_value.y, t_value.z);
}

void ShaderManager::loadVector(GLint t_var_location, glm::vec4 t_value)
{
	glUniform4f(t_var_location, t_value.x, t_value.y, t_value.z, t_value.y);
}

void ShaderManager::loadMatrix(GLint t_var_location, glm::mat4 t_value)
{
	glUniformMatrix4fv(t_var_location, 1, GL_FALSE, &t_value[0][0]);
}

void ShaderManager::loadBool(GLint t_var_location, bool t_value)
{
	loadFloat(t_var_location, t_value ? 1 : 0);
}