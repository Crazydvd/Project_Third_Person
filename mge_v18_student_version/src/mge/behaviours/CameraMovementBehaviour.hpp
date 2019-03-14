#ifndef CAMERAMOVEMENTBEHAVIOUR_HPP
#define CAMERAMOVEMENTBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"
#include <map>
#include <vector>

class Camera;

class CameraMovementBehaviour : public AbstractBehaviour
{
public:
	CameraMovementBehaviour(Camera* pCamera);
	~CameraMovementBehaviour();
	virtual void update(float pStep);

	void AddPath(std::vector<glm::vec3> pPath, std::vector<glm::vec3> pRotations, std::string pName);
	void RemovePath(std::string pName);
	void FollowPath(std::string pName);
	void FollowReversePath(std::string pName);

	/*
	* vector of glm::vec3 that represent the amount of degrees it has to rotate
	* store old rotation
	* add the amount of degrees * _interValue
	*/

	void SetPosition(glm::vec3 pPosition);
	glm::vec3 GetPosition();

	void SetRotation(glm::mat4 pRotation);

	bool IsPlayingAnimation();

private:
	Camera* _camera;

	std::map<std::string, std::vector<glm::vec3>> _paths;
	std::vector<glm::vec3> _currentPath;

	std::map<std::string, std::vector<glm::vec3>> _rotations;
	std::vector<glm::vec3> _currentRotations;

	void updatePath();
	void updateReversePath();
	void updateDeltaVector();

	void rotate(glm::vec3 pDegrees, float pValue);
	void generateRotation(std::string pName);

	glm::vec3 _oldPosition;
	glm::vec3 _newPosition;
	glm::vec3 _deltaVector;

	glm::vec3 _newRotation;
	glm::mat4 _oldRotation;
	glm::mat4 _originalRotation;
	glm::vec3 _deltaRotationVector;

	int _index = 0;
	bool _moving = false;
	bool _reverse = false;

	float _interValue = 0;
};

#endif // !CAMERAMOVEMENTBEHAVIOUR_HPP