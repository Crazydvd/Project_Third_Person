#include <iostream>
#include <string>
#include "Time.h"

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/MouseRotatingBehaviour.hpp"
#include "mge/behaviours/EmptyBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "ThirdPerson/config.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Ray.hpp"
#include "ThirdPerson/RenderToTexture.hpp"
#include "ThirdPerson/UserInterface.hpp"


std::vector<GameObject*> TPerson::puzzleObjects = std::vector<GameObject*>();

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
TPerson::TPerson() :AbstractGame(), _hud(0)
{

}

void TPerson::initialize()
{
	TPerson::_levelIndex = 1;
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void TPerson::_initializeScene()
{
	renderToTexture = new RenderToTexture();
	renderToTexture->setTPerson(this);

	//UI
	_userInterface = new UserInterface(_window);
	_world->add(_userInterface);

	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* planeMeshDefault = Mesh::load(config::THIRDPERSON_MODEL_PATH + "plane.obj");
	Mesh* sphereMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "sphere_smooth.obj");
	Mesh* umbrellaMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Umbrella.obj");
	Mesh* pliersDown = Mesh::load(config::THIRDPERSON_MODEL_PATH + "PliersDown.obj");
	Mesh* pliersUp = Mesh::load(config::THIRDPERSON_MODEL_PATH + "PliersUp.obj");
	Mesh* plunger1 = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Toilet_plunger_1.obj");
	Mesh* plunger2 = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Toilet_plunger_2.obj");
	Mesh* syringeMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Syringe.obj");
	Mesh* scissorMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Scissor.obj");
	Mesh* bottleMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Bottle.obj");
	Mesh* deskMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Desk.obj");
	//Mesh* plunger1 = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Toilet_plunger_2.obj");
	//Mesh* plunger2 = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Toilet_plunger_1.obj");

	//MATERIALS

	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + "bricks.jpg"));
	AbstractMaterial* landMaterial = new TextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + "land.jpg"));
	AbstractMaterial* umbrellaMaterial = new TextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + "AlbedoUmbrella.png"));
	AbstractMaterial* deskMaterial = new LitTextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + "DeskBase.png"));
	litMaterialR = new LitMaterial(glm::vec3(1, 0, 0));
	litMaterialG = new LitMaterial(glm::vec3(0.5f, 0.5f, 0.5f));
	litMaterialB = new LitMaterial(glm::vec3(0, 0, 1));
	blackMaterial = new ColorMaterial(glm::vec3(0, 0, 0));
	greyMaterial = new ColorMaterial(glm::vec3(0.5f, 0.5f, 0.5f));
	shadowMaterial = new TextureMaterial(renderToTexture->getTexture());

	//SCENE SETUP

   //add camera first (it will be updated last)
	camera = new Camera("camera", glm::vec3(0, 3, 2.5f));
	camera->rotate(glm::radians(-45.0f), glm::vec3(1, 0, 0));
	camera->setBehaviour(new KeysBehaviour(25, 90));
	_world->add(camera);
	_world->setMainCamera(camera);

	room = new Room(this, _world, _window, _levelIndex, renderToTexture);
	_world->add(room);

	//a light to light the scene!
	light = new Light("light", glm::vec3(0, 4.0f, 0), LightType::POINT);
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0));
	light->translate(glm::vec3(0, 0, 3));
	light->SetLightIntensity(1.5f);
	//light->setMesh(sphereMesh);
	light->setMaterial(lightMaterial);
	_world->add(light);
	//light->SetLightColor(glm::vec3(1, 0, 0.8f));
	LitMaterial::AddLight(light);

	//add the plane
	plane = new GameObject("plane", glm::vec3(0, 0.9f, -0));
	plane->scale(glm::vec3(1, 1, 1));
	/*plane->rotate(glm::radians(-90.0f), glm::vec3(0, 0, 1));
	plane->rotate(glm::radians(25.0f), glm::vec3(1, 0, 0));
	plane->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));*/
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(shadowMaterial);
	_world->add(plane);

	////add the floor
	//GameObject* floor = new GameObject("floor", glm::vec3(0, -2.5f, 0));
	//floor->scale(glm::vec3(15, 15, 15));
	//floor->setMesh(planeMeshDefault);
	//floor->setMaterial(greyMaterial);
	//_world->add(floor);

	//add a desk
	desk = new GameObject("desk", glm::vec3(0, -0.5f, 0));
	desk->scale(glm::vec3(3.0f, 3.0f, 3.0f));
	//desk->rotate(glm::radians(45.0f), glm::vec3(0, 1, 0));
	desk->setMesh(deskMesh);
	desk->setMaterial(deskMaterial);
	_world->add(desk);

	//add a puzzle object
	//puzzleObject = new GameObject("puzzleObject", glm::vec3(0, 3, 0));
	//puzzleObject->scale(glm::vec3(0.5f, 0.5f, 0.5f));
	////puzzleObject->rotate(glm::radians(45.0f), glm::vec3(1, 0.5f, 0));
	//puzzleObject->setMesh(umbrellaMesh);
	//puzzleObject->setMaterial(litMaterialR);
	//puzzleObject->setBehaviour(new MouseRotatingBehaviour(_window, _world));
	//_world->add(puzzleObject);

	puzzleObject1 = new GameObject("puzzleObject1", glm::vec3(0, 2, 0));
	puzzleObject1->scale(glm::vec3(0.1, 0.1, 0.1));
	puzzleObject1->rotate(glm::radians(95.0f), glm::vec3(1, 0.5f, 0.6f));
	puzzleObject1->setMesh(scissorMesh);
	puzzleObject1->setMaterial(umbrellaMaterial);
	puzzleObject1->setBehaviour(new MouseRotatingBehaviour(_window, _world));
	_world->add(puzzleObject1);

	//puzzleObject2 = new GameObject("puzzleObject2", glm::vec3(-0.23, 1.785, 0.1));
	//puzzleObject2->scale(glm::vec3(0.1, 0.1, 0.1));
	//puzzleObject2->rotate(glm::radians(45.0f), glm::vec3(1, 0.5f, 0));
	//puzzleObject2->setMesh(plunger2);
	//puzzleObject2->setMaterial(litMaterialR);
	//puzzleObject2->setBehaviour(new MouseRotatingBehaviour(_window, _world));
	//_world->add(puzzleObject2);

	//puzzleObjects.push_back(puzzleObject);
	puzzleObjects.push_back(puzzleObject1);
	//puzzleObjects.push_back(puzzleObject2);
}

void TPerson::Render()
{
	AbstractGame::_render();
}

Renderer* TPerson::getRenderer(void) const
{
	return this->_renderer;
}

void TPerson::_render()
{
	glm::mat4 lightTransform = light->getTransform();
	renderToTexture->Render(puzzleObjects, blackMaterial, lightTransform);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	AbstractGame::_render();

	_updateHud();

	if (puzzleObjects.size() == 1)
	{
		_checkOnePuzzle();
	}

}

void TPerson::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
	_userInterface->draw();
}

void TPerson::_checkOnePuzzle()
{
	glm::vec3 rotation = puzzleObject1->getWorldRotation();
	
	//Check if we in solution range
	if ((rotation.y <= 8 || rotation.y >= 172) && !completed)
	{
		//puzzleObject1->setBehaviour(new EmptyBehaviour());

		completed = true;
	}

	//Slowly rotate to perfect rotation and put a win screen
	if (completed)
	{
		//Rotate (slowly set X and Z of Y-axis to 0 so it points up)
		if (rotation.y >= 0.1 && rotation.y <= 179.9)
		{
			glm::mat4 newMatrix = puzzleObject1->getTransform();

			//x
			if (newMatrix[1].x != 0)
			{
				newMatrix[1].x -= glm::sign(newMatrix[1].x) * 0.0001;
			}
			else
			{
				newMatrix[1] = glm::vec4(0, newMatrix[1].y, newMatrix[1].z, 0);
			}

			//z
			if (newMatrix[1].z != 0)
			{
				newMatrix[1].z -= glm::sign(newMatrix[1].z) * 0.0001;
			}
			else
			{
				newMatrix[1] = glm::vec4(newMatrix[1].x, newMatrix[1].y, 0, 0);
			}
					
			//Orthonormolize the matrix according to Y-axis
			newMatrix[1] = glm::normalize(newMatrix[1]) * glm::length(puzzleObject1->getTransform()[1]);
			glm::mat3 normolizedMatrix = newMatrix;

			normolizedMatrix[0] = glm::orthonormalize(normolizedMatrix[0], normolizedMatrix[1]) * glm::length(newMatrix[0]);
			newMatrix[0] = glm::vec4(normolizedMatrix[0].x, normolizedMatrix[0].y, normolizedMatrix[0].z, 0);

			normolizedMatrix[2] = glm::orthonormalize(normolizedMatrix[2], normolizedMatrix[1]) * glm::length(newMatrix[2]);
			newMatrix[2] = glm::vec4(normolizedMatrix[2].x, normolizedMatrix[2].y, normolizedMatrix[2].z, 0);

			newMatrix[3] = puzzleObject1->getTransform()[3];					

			puzzleObject1->setTransform(newMatrix);	
		}
		//Put a winscreen
		else
		{
			++victoryDelay;

			if (victoryDelay >= 240)
			{
				UITexture* winScreen = new UITexture(_window, "winscreen.png");
				winScreen->SetPosition(glm::vec3((_window->getSize().x - winScreen->GetRect().width) / 2, (_window->getSize().y - winScreen->GetRect().height) / 2, 0));
				_userInterface->Add(winScreen);

				victoryDelay = 0;
				//completed = false;
			}
		}
	}
	else
	{
		_rotateWithKeys();
	}
}

void TPerson::_rotateWithKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		puzzleObject1->setWorldRotation(glm::vec3(0, 180, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		puzzleObject1->rotate(glm::radians(-1.0f), glm::vec3(1, 0, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		puzzleObject1->rotate(glm::radians(1.0f), glm::vec3(1, 0, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		puzzleObject1->rotate(glm::radians(-1.0f), glm::vec3(0, 1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		puzzleObject1->rotate(glm::radians(1.0f), glm::vec3(0, 1, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		puzzleObject1->rotate(glm::radians(-1.0f), glm::vec3(0, 0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		puzzleObject1->rotate(glm::radians(1.0f), glm::vec3(0, 0, 1));


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		puzzleObject1->rotate(glm::radians(1.0f), glm::vec3(1, 0, 1));

}

void TPerson::MoveToPreviousLevel()
{
	_levelIndex--;
	if (_levelIndex < 1) { _levelIndex = 1; return; }
	_world->remove(room);
	delete(room);
	room = new Room(this, _world, _window, _levelIndex, renderToTexture);
	_world->add(room);
}

void TPerson::MoveToNextLevel()
{
	_levelIndex++;
	if (_levelIndex > 2) { _levelIndex = 2; return; }
	_world->remove(room);
	delete(room);
	room = new Room(this, _world, _window, _levelIndex, renderToTexture);
	_world->add(room);
}

Camera* TPerson::GetMainCamera()
{
	return _world->getMainCamera();
}

sf::RenderWindow* TPerson::GetWindow()
{
	return _window;
}

World* TPerson::GetWorld()
{
	return _world;
}

TPerson::~TPerson()
{
	//dtor
}

