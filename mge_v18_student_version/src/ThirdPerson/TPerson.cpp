#include <iostream>
#include <string>

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

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/MouseRotatingBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "ThirdPerson/config.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Ray.hpp"

std::vector<GameObject*> TPerson::puzzleObjects = std::vector<GameObject*>();

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
TPerson::TPerson() :AbstractGame(), _hud(0)
{

}

void TPerson::initialize()
{
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
	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* planeMeshDefault = Mesh::load(config::THIRDPERSON_MODEL_PATH + "plane.obj");
	Mesh* sphereMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "sphere_smooth.obj");
	Mesh* pliersDown = Mesh::load(config::THIRDPERSON_MODEL_PATH + "PliersDown.obj");
	Mesh* pliersUp = Mesh::load(config::THIRDPERSON_MODEL_PATH + "PliersUp.obj");
	Mesh* umbrellaMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Umbrella.obj");
	Mesh* deskMesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "Desk.obj");

	//MATERIALS

	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + "bricks.jpg"));
	AbstractMaterial* landMaterial = new TextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + "land.jpg"));
	AbstractMaterial* litMaterialR = new LitMaterial(glm::vec3(1, 0, 0));
	AbstractMaterial* litMaterialG = new LitMaterial(glm::vec3(0.5f, 0.5f, 0.5f));
	AbstractMaterial* litMaterialB = new LitMaterial(glm::vec3(0, 0, 1));

	//SCENE SETUP

   //add camera first (it will be updated last)
	Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	//add a light. Note that the light ABSOLUTELY WORKS! YES ! REALLY !

	//a light to light the scene!
	Light* light = new Light("light", glm::vec3(-5.85, 2, -2.30), LightType::POINT);
	light->SetLightIntensity(1.5f);
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->setMesh(sphereMesh);
	light->setMaterial(lightMaterial);
	light->setBehaviour(new KeysBehaviour(25, 90));
	_world->add(light);
	LitMaterial::AddLight(light);

	//add the floor
	GameObject* plane = new GameObject("plane", glm::vec3(0, -4, 0));
	plane->scale(glm::vec3(15, 15, 15));
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(litMaterialG);
	_world->add(plane);

	//add a desk
	GameObject* desk = new GameObject("desk", glm::vec3(-3, 0, -3));
	desk->scale(glm::vec3(3.5f, 3.5f, 3.5f));
	desk->rotate(glm::radians(45.0f), glm::vec3(0, 1, 0));
	desk->setMesh(deskMesh);
	desk->setMaterial(litMaterialB);
	_world->add(desk);


	//add a cube sphere
	GameObject* umbrella = new GameObject("cube", glm::vec3(0, 0, 0));
	umbrella->scale(glm::vec3(0.5f, 0.5f, 0.5f));
	umbrella->setMesh(umbrellaMesh);
	umbrella->setMaterial(litMaterialR);
	umbrella->setBehaviour(new MouseRotatingBehaviour(_window, _world));
	_world->add(umbrella);

	//add a sphere
	GameObject* sphere = new GameObject("sphere", glm::vec3(20, 0, 0));
	sphere->scale(glm::vec3(0.5, 0.5, 0.5));
	sphere->setMesh(pliersUp);
	sphere->setMaterial(litMaterialB);
	sphere->setBehaviour(new MouseRotatingBehaviour(_window, _world));
	//_world->add(sphere);

	//puzzleObjects.push_back(sphere);
	puzzleObjects.push_back(umbrella);
}

void TPerson::_render()
{
	AbstractGame::_render();
	_updateHud();
}

void TPerson::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

TPerson::~TPerson()
{
	//dtor
}