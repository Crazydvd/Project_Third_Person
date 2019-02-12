#ifndef TPERSON_HPP
#define TPERSON_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class TPerson : public AbstractGame
{
	//PUBLIC FUNCTIONS

public:
	TPerson();
	virtual ~TPerson();

	//override initialize so we can add a DebugHud
	virtual void initialize();

protected:
	//override so we can construct the actual scene
	virtual void _initializeScene();

	//override render to render the hud as well.
	virtual void _render();

private:
	DebugHud* _hud;                   //hud display

	void _updateHud();

	TPerson(const TPerson&);
	TPerson& operator=(const TPerson&);
};

#endif // TPERSON_HPP
