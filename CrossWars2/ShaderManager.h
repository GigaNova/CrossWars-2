#pragma once
#include "Singleton.h"
#include "GLEW/glew.h"

class ShaderManager : public TSingleton<ShaderManager>
{
public:
	ShaderManager();
	~ShaderManager();

	void loadVertexShader(std::string t_file_name);
	void loadFragmentShader(std::string t_file_name);
	void bindPrograms();

	GLuint getProgramID();
private:
	GLuint m_vertex_id;
	GLuint m_fragment_id;

	GLuint m_program_id;
};

