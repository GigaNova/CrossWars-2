#pragma once
#include <GLM/vec3.hpp>
#include <GLEW/glew.h>
#include <SDL/SDL_events.h>

class Camera
{
public:
	static const GLfloat FOV;
	static const GLfloat FAR_PLANE;
	static const GLfloat NEAR_PLANE;

	Camera();
	~Camera();

	glm::vec3 getPosition() const;
	void setPosition(const glm::vec3& t_value);
	GLfloat getPitch() const;
	void setPitch(GLfloat t_value);
	GLfloat getYaw() const;
	void setYaw(GLfloat t_value);
	GLfloat getRoll() const;
	void setRoll(GLfloat t_value);

	void increaseRotation(glm::vec3 t_value);

	void move(SDL_KeyboardEvent* t_key);
	void rotate(SDL_MouseButtonEvent* t_button);
private:
	const float SPEED = 25.f;

	glm::vec3 m_position;
	GLfloat m_pitch;
	GLfloat m_yaw;
	GLfloat m_roll;
};

