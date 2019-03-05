#include "mge/behaviours/MouseRotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Ray.hpp"

MouseRotatingBehaviour::MouseRotatingBehaviour(sf::RenderWindow* pWindow, World* pWorld) : AbstractBehaviour(), _window(pWindow), _world(pWorld)
{
}

void MouseRotatingBehaviour::update(float pStep)
{
	//Rotating with mouse
	if (!_mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_rotating)
	{
		_mousePressed = true;
		Ray mouseray = Ray::MouseRay(_window, 60.0f, _world);

		//Get objects array
		GameObject* objects[2];
		objects[0] = TPerson::puzzleObjects.at(0);
		objects[1] = TPerson::puzzleObjects.at(1);

		if (mouseray.GetCollision(objects, 2) == _owner)
		{
			_oldPos = sf::Mouse::getPosition();
			_oldRotation = _owner->getTransform();
			_rotating = true;
		}
	}
	//Not rotating with mouse
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		_oldPos.x = 0;
		_rotating = false;
		_mousePressed = false;
		
	}

	if (_rotating)
	{
		sf::Vector2i _newPos = sf::Mouse::getPosition();
		glm::vec3 _direction = glm::vec3(_newPos.y - _oldPos.y, _newPos.x - _oldPos.x, 0);
		_rotation = glm::length(_direction);

		//Rotate towards the direction 
		if (_direction.x != 0 && _direction.y != 0)
		{
			//get the rotation matrix
			_direction = glm::normalize(_direction);
			glm::mat4 _rotationMatrix = glm::rotate(glm::mat4(), pStep * glm::radians(_rotation * 20.0f), glm::vec3(_direction));

			//get the inverse translate
			glm::mat4 translationMatrix = glm::mat4(1);
			translationMatrix[3] = _owner->getWorldTransform()[3];
			glm::mat4 inverseTranslation = glm::inverse(translationMatrix);


			_owner->setTransform(inverseTranslation * _oldRotation);			    //move to origin
			_owner->setTransform(_rotationMatrix * _owner->getWorldTransform());	//rotate		
			_owner->setTransform(translationMatrix * _owner->getWorldTransform());  //move back
		}
	}
};