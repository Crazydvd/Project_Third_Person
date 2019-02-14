#include "ThirdPerson/Ray.hpp"

Ray::Ray() : _position(0, 0, 0), _target(0, 0, 0)
{
	calculateDirection();
}

Ray::Ray(glm::vec3 pPosition, glm::vec3 pTarget)
{
	_position = pPosition;
	_target = pTarget;
	calculateDirection();
}

Ray::Ray(glm::vec3 pDirection) : Ray::Ray(glm::vec3(0, 0, 0), pDirection)
{

}

Ray::Ray(float pX, float pY, float pZ) : Ray::Ray(glm::vec3(pX, pY, pZ))
{

}



Ray Ray::MouseRay(sf::RenderWindow pWindow, float pCameraFOV)
{
	sf::Vector2u size = pWindow.getSize();
	sf::Vector2i mousePos = sf::Mouse::getPosition(pWindow);
	glm::vec2 MouseRelativeToScreenPosition = glm::vec2(
		(float)mousePos.x - (size.x / 2),
		(float)mousePos.y + (size.y / 2)
	);

	float planeDistance = (size.y / 2) / glm::tan(glm::radians(pCameraFOV / 2));

	return Ray(MouseRelativeToScreenPosition.x, MouseRelativeToScreenPosition.y, planeDistance);
}

float Ray::Length()
{
	return glm::length(_direction);
}

glm::vec3 Ray::calculateDirection()
{
	return _direction = _target - _position;
}

bool Ray::hitObject(GameObject pTarget, float pRadius)
{
	glm::vec3 differenceVector = pTarget.getWorldPosition() - _position;
	glm::vec3 projection = glm::dot(_direction, differenceVector) * _direction;
	glm::vec3 distanceVector = differenceVector - projection;

	float distance = glm::length(distanceVector);

	if (distance <= pRadius)
	{
		return true;
	}

	return false;
}

Ray::~Ray()
{

}