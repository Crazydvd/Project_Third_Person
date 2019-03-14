#include "AbstractBehaviour.hpp"

AbstractBehaviour::AbstractBehaviour():_owner(nullptr) {}

AbstractBehaviour::~AbstractBehaviour()
{
	_owner = nullptr;
}

void AbstractBehaviour::setOwner (GameObject* pOwner) {
    _owner = pOwner;
}

void AbstractBehaviour::AddPath(std::vector<glm::vec3> pPath, std::vector<glm::vec3> pRotations, std::string pName)
{
}

void AbstractBehaviour::RemovePath(std::string pName)
{
}

void AbstractBehaviour::FollowPath(std::string)
{
}

void AbstractBehaviour::FollowReversePath(std::string pName)
{

}
