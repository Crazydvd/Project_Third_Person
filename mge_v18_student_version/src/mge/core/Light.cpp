#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"

Light::Light(const std::string& pName, const glm::vec3& pPosition, LightType pType) :GameObject(pName, pPosition)
{
	_type = pType;
}

Light::~Light()
{
}

LightType Light::GetType()
{
	return _type;
}

glm::vec3 Light::GetColor()
{
	return _color * _intensity;
}

glm::vec3 Light::GetAmbientColor()
{
	return GetColor() * _ambientContribution;
}

glm::vec3 Light::GetPosition()
{
	return getWorldPosition();
}

glm::vec3 Light::GetForwardDirection()
{
	return getWorldTransform()[2];
}

float Light::getFalloff()
{
	return _falloff;
}

float Light::GetConeAngle()
{
	return _coneAngle;
}

float Light::GetFallOffAngle()
{
	return _fallOffAngle;
}

void Light::SetLightType(LightType pType)
{
	_type = pType;
}

void Light::SetLightIntensity(float pIntensity)
{
	_intensity = pIntensity;
}

void Light::SetLightColor(glm::vec3 pColor)
{
	_color = pColor;
}

void Light::setAmbientContribution(float pContribution)
{
	_ambientContribution = pContribution;
}

void Light::setFalloff(float pFalloff)
{
	_falloff = pFalloff;
}


void Light::setConeAngle(float pAngle)
{
	_coneAngle = pAngle;
}

void Light::setFallOffAngle(float pAngle)
{
	_fallOffAngle = pAngle;
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively(World* pWorld)
{

	//store the previous and new world before and after storing the given world
	World* previousWorld = _world;
	GameObject::_setWorldRecursively(pWorld);
	World* newWorld = _world;

	//check whether we need to register or unregister
	if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}


