#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/core/Camera.hpp"

CameraMovementBehaviour::CameraMovementBehaviour(Camera* pCamera) : AbstractBehaviour(), _camera(pCamera), _oldPosition(pCamera->getWorldPosition())
{

}

CameraMovementBehaviour::~CameraMovementBehaviour()
{

}

void CameraMovementBehaviour::update(float pStep)
{	
	if (_moving)
	{
		SetPosition(_oldPosition + _deltaVector * _interValue);
		_interValue = (_interValue < 1) ? _interValue += pStep : 1;

		if (_interValue >= 1)
		{
			if (!_reverse)
			{
				updatePath();
			}
			else
			{
				updateReversePath();
			}
			_interValue = 0;
		}
	}
}


void CameraMovementBehaviour::AddPath(std::vector<glm::vec3> pPath, std::string pName)
{
	if (pPath.size() > 1)
	{
		_paths[pName] = pPath;
	}
}

void CameraMovementBehaviour::RemovePath(std::string pName)
{
	_paths.erase(pName);
}

void CameraMovementBehaviour::FollowPath(std::string pName)
{
	_reverse = false;
	_moving = true;
	_interValue = 0;

	_currentPath = _paths[pName];
	SetPosition(_currentPath[0]);
	_oldPosition = GetPosition();
	_index = 1;
	_newPosition = _currentPath[_index];

	updateDeltaVector();
}

void CameraMovementBehaviour::FollowReversePath(std::string pName)
{
	_reverse = true;
	_moving = true;
	_interValue = 0;

	_currentPath = _paths[pName];
	SetPosition(_currentPath[_currentPath.size() - 1]);
	_oldPosition = GetPosition();
	_index = _currentPath.size() - 2;
	_newPosition = _currentPath[_index];

	updateDeltaVector();
}

void CameraMovementBehaviour::SetPosition(glm::vec3 pPosition)
{
	_camera->setLocalPosition(pPosition);
}

glm::vec3 CameraMovementBehaviour::GetPosition()
{
	return _camera->getLocalPosition();
}

void CameraMovementBehaviour::updatePath()
{
	SetPosition(_currentPath[_index++]);

	if (_index == _currentPath.size())
	{
		_moving = false;
		return;
	}

	_oldPosition = GetPosition();
	_newPosition = _currentPath[_index];

	updateDeltaVector();
}

void CameraMovementBehaviour::updateReversePath()
{
	SetPosition(_currentPath[_index--]);

	if (_index == -1)
	{
		_moving = false;
		return;
	}

	_oldPosition = GetPosition();
	_newPosition = _currentPath[--_index];

	updateDeltaVector();
}

void CameraMovementBehaviour::updateDeltaVector()
{
	_deltaVector = _newPosition - _oldPosition;
}

