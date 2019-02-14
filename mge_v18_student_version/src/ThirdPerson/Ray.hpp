#ifndef RAY_HPP
#define RAY_HPP

#include "glm.hpp" 
#include "mge/core/Gameobject.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"

class Ray
{
public:
	Ray();
	Ray(glm::vec3 pPosition, glm::vec3 pTarget);
	Ray(glm::vec3 pDirection);
	Ray(float pX, float pY, float pZ);
	~Ray();

	float Length();
	bool HitObject(const GameObject* pTarget, const float pRadius);
	static Ray MouseRay(const sf::RenderWindow* pWindow, const float pCameraFOV, World* pWorld);

	glm::vec3 ToVec3();
	glm::vec4 ToVec4();
	static Ray ToRay(glm::vec3);
	static Ray ToRay(glm::vec4);

private:
	glm::vec3 _start;
	glm::vec3 _target;
	glm::vec3 _direction;
	glm::vec3 calculateDirection();

};
#endif // RAY_HPP