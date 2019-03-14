#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/core/Camera.hpp"

CameraMovementBehaviour::CameraMovementBehaviour(Camera* pCamera) : AbstractBehaviour(),
_camera(pCamera), _oldPosition(pCamera->getWorldPosition()), _originalRotation(_camera->getTransform())
{

}

CameraMovementBehaviour::~CameraMovementBehaviour()
{

}

void CameraMovementBehaviour::update(float pStep)
{
	if (_moving)
	{
		if (!_reverse)
		{
			rotate(_newRotation, _interValue);
		}
		else
		{
			rotate(_newRotation, -_interValue);
		}

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


void CameraMovementBehaviour::AddPath(std::vector<glm::vec3> pPath, std::vector<glm::vec3> pRotations, std::string pName)
{
	if (pPath.size() > 1)
	{
		_paths[pName] = pPath;
		_rotations[pName] = pRotations;
	}
}

void CameraMovementBehaviour::RemovePath(std::string pName)
{
	_paths.erase(pName);
	_rotations.erase(pName);
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


	_currentRotations = _rotations[pName];
	SetRotation(_originalRotation);
	_oldRotation = _camera->getWorldTransform();
	_newRotation = _currentRotations[_index];

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


	_currentRotations = _rotations[pName];
	SetRotation(_originalRotation);

	for (int i = 1; i < _currentRotations.size(); i++)
	{
		glm::vec3 rotation = _currentRotations[i];

		_camera->rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0));
		_camera->rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0));
		_camera->rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
	}

	_oldRotation = _camera->getWorldTransform();
	_newRotation = _currentRotations[_index + 1];

	updateDeltaVector();
}

void CameraMovementBehaviour::updatePath()
{
	SetPosition(_currentPath[_index]);

	_index++;

	if (_index == _currentPath.size())
	{
		_moving = false;
		return;
	}

	_oldPosition = GetPosition();
	_newPosition = _currentPath[_index];

	_oldRotation = _camera->getWorldTransform();
	_newRotation = _currentRotations[_index];

	updateDeltaVector();
}

void CameraMovementBehaviour::updateReversePath()
{
	SetPosition(_currentPath[_index]);

	_index--;

	if (_index == -1)
	{
		_moving = false;
		return;
	}

	_oldPosition = GetPosition();
	_newPosition = _currentPath[_index];

	_oldRotation = _camera->getWorldTransform();
	_newRotation = _currentRotations[_index + 1];

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

void CameraMovementBehaviour::SetRotation(glm::mat4 pRotation)
{
	glm::vec4 position = _camera->getTransform()[3];
	glm::mat4 transform;

	transform[0] = pRotation[0];
	transform[1] = pRotation[1];
	transform[2] = pRotation[2];
	transform[3] = position;

	_camera->setTransform(transform);
}

void CameraMovementBehaviour::updateDeltaVector()
{
	_deltaVector = _newPosition - _oldPosition;
}

void CameraMovementBehaviour::rotate(glm::vec3 pDegrees, float pValue)
{
	SetRotation(_oldRotation);

	glm::vec3 rotation = pDegrees * pValue;

	if (pValue > 0)
	{
		_camera->rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0));
		_camera->rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0));
		_camera->rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
	}
	else if (pValue < 0)
	{
		_camera->rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
		_camera->rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0));
		_camera->rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0));
	}
}

void CameraMovementBehaviour::generateRotation(std::string pName)
{

}

