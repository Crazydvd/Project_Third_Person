#include "mge/behaviours/MouseRotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/TPerson.hpp"

MouseRotatingBehaviour::MouseRotatingBehaviour() : AbstractBehaviour()
{
}

void MouseRotatingBehaviour::update(float pStep)
{
	//Rotating with mouse
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_rotating)
	{
		_oldPos = sf::Mouse::getPosition();
		_oldRotation = _owner->getTransform();
		std::cout << _oldPos.x << std::endl;
		_rotating = true;
	}
	//Not roatating with mouse
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		_oldPos.x = 0;
		_rotating = false;
	}


	if (_rotating)
	{
		sf::Vector2i _newPos = sf::Mouse::getPosition();	
		glm::vec3 _direction = glm::vec3(_newPos.y - _oldPos.y, _newPos.x - _oldPos.x, 0);
		_rotation = glm::length(_direction);

		//Rotate towards the direction 
		if (_direction.x != 0 && _direction.y != 0 && _newPos != _latestPos)
		{
			_direction = glm::normalize(_direction);
			glm::mat4 _rotationMatrix = glm::rotate(glm::mat4(), pStep * glm::radians(_rotation * 10.0f), glm::vec3(_direction));
			_owner->setTransform(_rotationMatrix * _oldRotation);
			_latestPos = _newPos;
		}
	}
};