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

	void AddPath(std::vector<glm::vec3> pPath, std::string pName);
	void RemovePath(std::string pName);
	void FollowPath(std::string pName);
	void FollowReversePath(std::string pName);

	void SetPosition(glm::vec3 pPosition);
	glm::vec3 GetPosition();

private:
	Camera* _camera;
	std::map<std::string, std::vector<glm::vec3>> _paths;
	std::vector<glm::vec3> _currentPath;

	void updatePath();
	void updateReversePath();
	void updateDeltaVector();

	glm::vec3 _oldPosition;
	glm::vec3 _newPosition;
	glm::vec3 _deltaVector;

	int _index = 0;
	bool _moving = false;
	bool _reverse = false;

	float _interValue = 0;
};

#endif // !CAMERAMOVEMENTBEHAVIOUR_HPP