#ifndef EMPTYBEHAVIOUR_HPP
#define  EMPTYBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

class EmptyBehaviour : public AbstractBehaviour
{
	//Its here to be able to clear the behaviours from an object

	void update(float pStep) {};
};

#endif //  EMPTYBEHAVIOUR_HPP
