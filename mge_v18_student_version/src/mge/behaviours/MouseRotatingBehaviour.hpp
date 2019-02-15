#ifndef MOUSEROTATINGBEHAVIOUR_HPP
#define  MOUSEROTATINGBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/TPerson.hpp"


class MouseRotatingBehaviour : public AbstractBehaviour
{
	public:
		MouseRotatingBehaviour();
		virtual void update(float pStep);

	private:
		float _rotation;
		glm::mat4 _oldRotation;
		sf::Vector2i _oldPos;
		sf::Vector2i _latestPos;
		bool _rotating;
};


#endif //MOUSEROTATINGBEHAVIOUR_HPP
