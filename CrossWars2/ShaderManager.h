#pragma once
#include "Singleton.h"
#include "GLEW/glew.h"
#include <GLM/vec3.hpp>
#include <GLM/fwd.hpp>
#include "ProtoShader.h"

class ShaderManager : public TSingleton<ShaderManager>
{
public:
	ShaderManager();
	~ShaderManager();

	void setActiveShader(ProtoShader* t_proto_shader);
	ProtoShader* getActiveShader() const;

	void loadVertexShader(const char* t_filename);
	void loadFragmentShader(const char* t_filename);
	GLuint bindPrograms();

	GLuint getVariable(const char* t_var);
	void bindAttribute(GLint t_attribute, const char* t_variable);

	void loadFloat(GLint t_var_location, GLfloat t_value);
	void loadVector(GLint t_var_location, glm::vec3 t_value);
	void loadVector(GLint t_var_location, glm::vec4 t_value);
	void loadMatrix(GLint t_var_location, glm::mat4 t_value);
	void loadBool(GLint t_var_location, bool t_value);
private:
	GLuint m_vertex_id;
	GLuint m_fragment_id;

	GLuint m_program_id;

	ProtoShader* m_loaded_shader;
};

