#pragma once
#include <GLM/vec3.hpp>
#include <GLEW/glew.h>
#include <SDL/SDL_events.h>

enum CameraType
{
	STATIC,
	FREELOOK
};

class Camera
{
public:
	static const GLfloat FOV;
	static const GLfloat FAR_PLANE;
	static const GLfloat NEAR_PLANE;
	static constexpr GLfloat AspectRatio() { return 1024.f / 768.f; }

	Camera(CameraType t_type);
	~Camera();

	glm::vec3 getRotation() const;

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

	void debug();
private:
	const float SPEED = 350.f;

	CameraType m_type;

	glm::vec3 m_position;
	GLfloat m_pitch;
	GLfloat m_yaw;
	GLfloat m_roll;
};

