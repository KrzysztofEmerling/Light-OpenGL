#include "Camera.h"
#include "gtc/matrix_transform.hpp"

Camera::Camera()
{
	m_Pos = glm::vec3(0, -10, 0);
	m_View = glm::translate(glm::mat4(1.0f), m_Pos);
}

Camera::~Camera()
{
}

void Camera::MoveCamera(glm::vec3 movement)
{
	m_Pos += movement;
	m_View = glm::translate(glm::mat4(1.0f), m_Pos);
}
