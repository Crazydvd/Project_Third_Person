#ifndef TPERSON_HPP
#define TPERSON_HPP

#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/RenderToTexture.hpp"

class DebugHud;
class Camera;

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
	
	static std::vector<GameObject*> puzzleObjects;

protected:
	//override so we can construct the actual scene
	virtual void _initializeScene();

	//override render to render the hud as well.
	virtual void _render();

private:
	RenderToTexture* renderToTexture;
	DebugHud* _hud;                   //hud display
	Camera* camera;
	GameObject* plane;
	GameObject* umbrella;
	AbstractMaterial* litMaterialR;
	AbstractMaterial* litMaterialG;
	AbstractMaterial* litMaterialB;
	AbstractMaterial* shadowMaterial;
	AbstractMaterial* test;

	float trick = 0;

	void _updateHud();

	TPerson(const TPerson&);
	TPerson& operator=(const TPerson&);
};

#endif // TPERSON_HPP
