#ifndef TPERSON_HPP
#define TPERSON_HPP

#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/RenderToTexture.hpp"

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
	Light* light;
	GameObject* plane;
	GameObject* puzzleObject;
	GameObject* puzzleObject1;
	GameObject* puzzleObject2;
	GameObject* desk;
	AbstractMaterial* litMaterialR;
	AbstractMaterial* litMaterialG;
	AbstractMaterial* litMaterialB;
	AbstractMaterial* blackMaterial;
	AbstractMaterial* greyMaterial;
	AbstractMaterial* shadowMaterial;

	glm::mat4 puzzleSolution1 = glm::transpose( glm::mat4{ 
										-0.1, +0.2, -0.1, +1.5,
										+0.2, +0.1, -0.1, +3.0,
										+0.0, -0.2, -0.2, +5.5,
										+0.0, +0.0, +0.0, +1.0 });

	float solutionDegreesX = glm::degrees(glm::acos(glm::dot(glm::normalize(puzzleSolution1[0]), glm::vec4(1, 0, 0, 1))));
	float solutionDegreesY = glm::degrees(glm::acos(glm::dot(glm::normalize(puzzleSolution1[1]), glm::vec4(0, 1, 0, 1))));
	float solutionDegreesZ = glm::degrees(glm::acos(glm::dot(glm::normalize(puzzleSolution1[2]), glm::vec4(0, 0, 1, 1))));

	float trick = 0;

	void _updateHud();
	void _checkPuzzle();

	TPerson(const TPerson&);
	TPerson& operator=(const TPerson&);
};

#endif // TPERSON_HPP
