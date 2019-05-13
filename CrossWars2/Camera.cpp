#include "Camera.h"
#include <GLM/glm.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/ext.hpp>
#include "MouseManager.h"
#include "DeltaTime.h"
#include "MathHelper.h"
#include <string>

const GLfloat Camera::FOV = 70.0f;
const GLfloat Camera::FAR_PLANE = 1000.f;
const GLfloat Camera::NEAR_PLANE = 0.1f;

Camera::Camera(CameraType t_type) : m_type(t_type), m_position(glm::vec3(0.0f, 0.0f, 0.0f)), m_pitch(0), m_yaw(0), m_roll(0)
{
}

Camera::~Camera()
{
}

glm::vec3 Camera::getRotation() const
{
	return glm::vec3(
		m_pitch,
		m_yaw,
		m_roll
	);
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

void Camera::increaseRotation(glm::vec3 t_value)
{
	m_pitch += t_value.x;
	m_yaw += t_value.y;
	m_roll += t_value.z;
}

void Camera::move(SDL_KeyboardEvent* t_key)
{
	SDL_Keycode pressed = t_key->keysym.sym;

	float movement = SPEED * DeltaTime::GetInstance()->getDeltaTime();

	glm::mat4 transMatrix = MathHelper::createTransformationMatrix(getPosition(), getRotation(), 1);
	glm::vec3 forward = MathHelper::getForward(transMatrix);

	switch (pressed)
	{
	case SDLK_w:
		m_position += movement * forward;
		break;
	case SDLK_s:
		m_position -= movement * forward;
		break;
	case SDLK_a:
		m_position.x -= movement;
		break;
	case SDLK_d:
		m_position.x += movement;
		break;
	}
}

void Camera::rotate(SDL_MouseButtonEvent* t_button)
{
	if(m_type == FREELOOK)
	{
		glm::vec2 mouseDelta = MouseManager::GetInstance()->getMouseDelta();

		m_yaw += mouseDelta.x;
		m_pitch -= mouseDelta.y;

		if(m_pitch > 90)
		{
			m_pitch = 90;
		}
		else if(m_pitch < -90)
		{
			m_pitch = -90;
		}
	}
}

void Camera::debug()
{
	std::cout <<
		"Pitch: " + std::to_string(m_pitch) << " "
		"Yaw: " + std::to_string(m_yaw) << " "
		"Roll: " + std::to_string(m_roll) <<
	std::endl;

	std::cout <<
		"X: " + std::to_string(m_position.x) << " "
		"Y: " + std::to_string(m_position.y) << " "
		"Z: " + std::to_string(m_position.z) <<
	std::endl;
}
