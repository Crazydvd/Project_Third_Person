#ifndef CLICKBEHAVIOUR_HPP
#define CLICKBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/TPerson.hpp"

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class ClickBehaviour : public AbstractBehaviour
{
public:
	//move speed is in units per second, turnspeed in degrees per second
	ClickBehaviour(sf::RenderWindow* pWindow, World* pWorld);
	virtual void update(float pStep);

private:
	float _rotation;
	glm::mat4 _oldRotation;
	sf::Vector2i _oldPos;
	bool _rotating;

	sf::RenderWindow* _window;
	World* _world;

	bool _mousePressed;
};

#endif // CLICKBEHAVIOUR_HPP
