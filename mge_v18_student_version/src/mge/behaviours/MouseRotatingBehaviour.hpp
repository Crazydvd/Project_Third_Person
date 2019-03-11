#ifndef MOUSEROTATINGBEHAVIOUR_HPP
#define  MOUSEROTATINGBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/TPerson.hpp"


class MouseRotatingBehaviour : public AbstractBehaviour
{
	public:
		MouseRotatingBehaviour(sf::RenderWindow* pWindow, World* pWorld, std::vector<GameObject*> pPuzzleObject);
		virtual void update(float pStep);

	private:
		std::vector<GameObject*> _puzzleObjects;
		float _rotation;
		glm::mat4 _oldRotation;
		sf::Vector2i _oldPos;
		bool _rotating;

		sf::RenderWindow* _window;
		World* _world;

		bool _mousePressed;
};


#endif //MOUSEROTATINGBEHAVIOUR_HPP
