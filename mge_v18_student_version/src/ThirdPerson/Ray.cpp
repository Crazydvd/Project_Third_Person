#include "ThirdPerson/Ray.hpp"

Ray::Ray() : _start(0, 0, 0), _target(0, 0, 0)
{
	calculateDirection();
}

Ray::Ray(glm::vec3 pPosition, glm::vec3 pTarget)
{
	_start = pPosition;
	_target = pTarget;
	calculateDirection();
}

Ray::Ray(glm::vec3 pDirection) : Ray::Ray(glm::vec3(0, 0, 0), pDirection)
{

}

Ray::Ray(float pX, float pY, float pZ) : Ray::Ray(glm::vec3(pX, pY, pZ))
{
	
}



Ray Ray::MouseRay(const sf::RenderWindow* pWindow, const float pCameraFOV, World* pWorld)
{
	sf::Vector2u size = pWindow->getSize();
	sf::Vector2i mousePos = sf::Mouse::getPosition(*pWindow);
	glm::vec2 MouseRelativeToScreenCenter = glm::vec2(
		(float)mousePos.x - (size.x / 2),
		(float)-mousePos.y + (size.y / 2)
	);

	float planeDistance = (size.y / 2) / tan(glm::radians(pCameraFOV / 2));

	glm::vec4 ray(
		MouseRelativeToScreenCenter.x,
		MouseRelativeToScreenCenter.y,
		-planeDistance,
		0
	);

	//see where this ray is actually pointing in the world and normalize it so we can use it for projection
	glm::vec3 rayWorld = glm::vec3(pWorld->getMainCamera()->getWorldTransform() * ray);
	rayWorld = glm::normalize(rayWorld);

	Ray mouseRay = Ray::ToRay(rayWorld);

	//For this 'special' ray, the origin needs to be the camera (but direction should stay the same).
	mouseRay._start = pWorld->getMainCamera()->getWorldPosition();

	return mouseRay;
}


float Ray::Length()
{
	return glm::length(_direction);
}

glm::vec3 Ray::calculateDirection()
{
	return _direction = _target - _start;
}

bool Ray::HitObject(const GameObject* pTarget, const float pRadius)
{
	glm::vec3 differenceVector = pTarget->getWorldPosition() - _start;

	//cloning the ray so that we can normalize without modifying the original
	Ray clone = Clone();
	glm::vec3 direction = clone.ToVec3();
	direction =  glm::normalize(direction);

	glm::vec3 projection = glm::dot(differenceVector, direction) * direction;
	glm::vec3 distanceVector = differenceVector - projection;

	float distance = glm::length(distanceVector);
	
	if (distance <= pRadius)
	{
		return true;
	}

	return false;
}

GameObject* Ray::GetCollision(GameObject* pObjects[], int pSize)
{
	GameObject* closestCollision = NULL;
	float lengthToClosestCollision = 0;

	for (int i = 0; i < pSize; i++)
	{
		GameObject* testObj = pObjects[i];				


		if (HitObject(testObj, 2))
		{
			if (closestCollision == NULL)
			{
				closestCollision = testObj;
			}
			else
			{
				lengthToClosestCollision = (lengthToClosestCollision == 0)? glm::length(closestCollision ->getWorldPosition() - _start) : lengthToClosestCollision;
				float newLength = glm::length(testObj->getWorldPosition() - _start);

				if (newLength < lengthToClosestCollision)
				{
					closestCollision = testObj;
					lengthToClosestCollision = newLength;
				}
			}
		}
	}

	return closestCollision;
}

glm::vec3 Ray::ToVec3()
{
	return glm::vec3(_direction.x, _direction.y, _direction.z);
}

glm::vec4 Ray::ToVec4()
{
	return glm::vec4(_direction.x, _direction.y, _direction.z, 0);
}

Ray Ray::ToRay(glm::vec3 pVec3)
{
	return Ray(pVec3);
}

Ray Ray::ToRay(glm::vec4 pVec4)
{
	return Ray((glm::vec3) pVec4);
}

Ray Ray::Clone() //TODO: srsly Daniel...? rework that 2nd line.
{
	glm::vec3 clone = ToVec3();
	return Ray(clone.x, clone.y, clone.z);
}

Ray::~Ray()
{

}