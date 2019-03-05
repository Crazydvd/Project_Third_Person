#include "glm.hpp"
#include "mge/core/Camera.hpp"

Camera::Camera(std::string pName, glm::vec3 pPosition, glm::mat4 pProjectionMatrix)
	: GameObject(pName, pPosition), _projection(pProjectionMatrix)
{

}

Camera::~Camera()
{
	//dtor
}

glm::mat4& Camera::getProjection()
{
	return _projection;
}

void Camera::SetFOV(float pAngleDegrees)
{
	_FOV = pAngleDegrees;
	_projection = glm::perspective(glm::radians(pAngleDegrees), 4.0f / 3.0f, 0.1f, 1000.0f);
}

float Camera::GetFOV()
{
	return _FOV;
}

