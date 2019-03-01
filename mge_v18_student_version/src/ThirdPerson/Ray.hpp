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

	//Return the length of the Ray
	float Length();

	// \brief a way to check if a Ray is colliding with a given Gameobject with pRadius
	bool HitObject(const GameObject* pTarget, const float pRadius);

	GameObject* GetCollision(GameObject* pObjects[], int pSize);

	// \brief get the ray from the camera to the world mouse position
	static Ray MouseRay(const sf::RenderWindow* pWindow, const float pCameraFOV, World* pWorld);

	//Convert the rays to vectors and back
	glm::vec3 ToVec3();
	glm::vec4 ToVec4();
	static Ray ToRay(glm::vec3);
	static Ray ToRay(glm::vec4);

	//Clone the ray
	Ray Clone();

private:
	//The beginning, end and different between them.

	glm::vec3 _start;
	glm::vec3 _target;
	glm::vec3 _direction;
	glm::vec3 calculateDirection();
};
#endif // RAY_HPP