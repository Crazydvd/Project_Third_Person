#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

enum LightType : int
{
	DIRECTIONAL = 1,
	POINT = 2,
	SPOT = 3,
	AMBIENT = 0,
};

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
public:
	Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(2.0f, 10.0f, 5.0f), LightType pType = LightType::DIRECTIONAL);
	virtual ~Light();

	//override set parent to register/deregister light...
	virtual void _setWorldRecursively(World* pWorld) override;

	LightType GetType();
	glm::vec3 GetColor(); //returns color * intensity
	glm::vec3 GetColour() { return GetColor(); }; //same as GetColor()
	glm::vec3 GetAmbientColor(); //returns GetColor() * _ambientContribution
	glm::vec3 GetAmbientColour() { return GetAmbientColor(); }; //same as GetAmbientColor()
	glm::vec3 GetPosition();
	glm::vec3 GetForwardDirection();
	float GetConeAngle();
	float GetFallOffAngle();

	void SetLightType(LightType pType);
	void SetLightIntensity(float pIntensity);
	void SetLightColor(glm::vec3 pColor);
	void SetLightColour(glm::vec3 pColour) { SetLightColor(pColour); }; //same as SetLightColor(glm::vec3)
	void setAmbientContribution(float pContribution);
	void setConeAngle(float pAngle);
	void setFallOffAngle(float pAngle);

private:
	LightType _type;

	glm::vec3 _color = glm::vec3(1, 0.96f, 0.84f); //default unity light colour
	glm::vec3& _colour = _color; //same as _color;
	float _intensity = 1;
	float _ambientContribution = 0;

	float _coneAngle = 30.0f;
	float _fallOffAngle = 10.0f;
};

#endif // LIGHT_HPP
