#include "Camera.h"

const GLfloat Camera::FOV = 90.0f;
const GLfloat Camera::FAR_PLANE = 0.1f;
const GLfloat Camera::NEAR_PLANE = 1000.f;

Camera::Camera() : m_position(glm::vec3(0, 0, 0)), m_pitch(0), m_yaw(0), m_roll(0)
{
}

Camera::~Camera()
{
}

glm::vec3 Camera::getPosition() const
{
	return m_position;
}

void Camera::setPosition(const glm::vec3& t_value)
{
	m_position = t_value;
}

GLfloat Camera::getPitch() const
{
	return m_pitch;
}

void Camera::setPitch(GLfloat t_value)
{
	m_pitch = t_value;
}

GLfloat Camera::getYaw() const
{
	return m_yaw;
}

void Camera::setYaw(GLfloat t_value)
{
	m_yaw = t_value;
}

GLfloat Camera::getRoll() const
{
	return m_roll;
}

void Camera::setRoll(GLfloat t_value)
{
	m_roll = t_value;
}

void Camera::move(SDL_KeyboardEvent* t_key)
{
	SDL_Keycode pressed = t_key->keysym.sym;
	switch (pressed)
	{
	case SDLK_w:
		m_position.y += 0.2f;
		break;
	case SDLK_s:
		m_position.y -= 0.2f;
		break;
	case SDLK_a:
		m_position.x -= 0.2f;
		break;
	case SDLK_d:
		m_position.x += 0.2f;
		break;
	}
}
