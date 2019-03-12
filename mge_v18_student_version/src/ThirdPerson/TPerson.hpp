#ifndef TPERSON_HPP
#define TPERSON_HPP

#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/RenderToTexture.hpp"
#include "ThirdPerson/Room.hpp"
#include "ThirdPerson/UITexture.hpp"
#include "ThirdPerson/UserInterface.hpp"

class DebugHud;
class Camera;
class Light;


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

	Camera* GetMainCamera();
	sf::RenderWindow* GetWindow();
	World* GetWorld();

	void Render();

	Renderer* getRenderer(void) const;

protected:
	//override so we can construct the actual scene
	virtual void _initializeScene();

	//override render to render the hud as well.
	virtual void _render();

private:
	UserInterface* _userInterface;
	Room* room;
	RenderToTexture* _renderToTexture;
	DebugHud* _hud;                   //hud display
	UITexture* _texture;
	Camera* camera;
	GameObject* plane;
	GameObject* puzzleObject;
	GameObject* puzzleObject1;
	GameObject* puzzleObject2;
	GameObject* desk;
	AbstractMaterial* litMaterialR;
	AbstractMaterial* litMaterialG;
	AbstractMaterial* litMaterialB;

	bool completed = false;
	float victoryDelay = 0;


	void _updateHud();
	void _checkOnePuzzle();
	void _rotateWithKeys();

	TPerson(const TPerson&);
	TPerson& operator=(const TPerson&);
};

#endif // TPERSON_HPP
