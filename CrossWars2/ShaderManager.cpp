#include "ShaderManager.h"
#include <vector>
#include <fstream>
#include "FileLoader.h"


ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::loadVertexShader(const char* t_filename)
{
	FileLoader fileLoader;
	auto str = fileLoader.loadFileToString(t_filename);
	char const * vertexSourcePointer = str.c_str();

	m_vertex_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertex_id, 1, &vertexSourcePointer, nullptr);
	glCompileShader(m_vertex_id);
}

void ShaderManager::loadFragmentShader(const char* t_filename)
{
	FileLoader fileLoader;
	auto str = fileLoader.loadFileToString(t_filename);
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
