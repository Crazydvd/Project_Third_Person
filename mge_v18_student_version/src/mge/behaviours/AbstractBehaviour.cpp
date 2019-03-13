#include "AbstractBehaviour.hpp"

AbstractBehaviour::AbstractBehaviour():_owner(nullptr) {}

AbstractBehaviour::~AbstractBehaviour()
{
	_owner = nullptr;
}

void AbstractBehaviour::setOwner (GameObject* pOwner) {
    _owner = pOwner;
}

void AbstractBehaviour::FollowPath(std::string)
{

}

void AbstractBehaviour::FollowReversePath(std::string pName)
{

}
