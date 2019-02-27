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
#include "ThirdPerson/RenderToTexture.hpp"

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
	this->renderToTexture = new RenderToTexture();
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
	litMaterialR = new LitMaterial(glm::vec3(1, 0, 0));
	litMaterialG = new LitMaterial(glm::vec3(0.5f, 0.5f, 0.5f));
	litMaterialB = new LitMaterial(glm::vec3(0, 0, 1));
	blackMaterial = new ColorMaterial(glm::vec3(0, 0, 0));
	greyMaterial = new ColorMaterial(glm::vec3(0.5f, 0.5f, 0.5f));
	shadowMaterial = new TextureMaterial(renderToTexture->getTexture());

	//SCENE SETUP

   //add camera first (it will be updated last)
	camera = new Camera("camera", glm::vec3(0, 4, 15));
	camera->rotate(glm::radians(-15.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	//add a light. Note that the light ABSOLUTELY WORKS! YES ! REALLY !

	//a light to light the scene!
	light = new Light("light", glm::vec3(7.65f, 2, 7.55f), LightType::POINT);
	light->SetLightIntensity(1.5f);
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->rotate(glm::radians(45.0f), glm::vec3(0,1,0));
	light->setMesh(sphereMesh);
	light->setMaterial(lightMaterial);
	light->setBehaviour(new KeysBehaviour(25, 90));
	_world->add(light);
	//light->SetLightColor(glm::vec3(1, 0, 0.8f));
	LitMaterial::AddLight(light);

	//add the plane
	plane = new GameObject("plane", glm::vec3(-4.5f, 2, -0.5f));
	plane->scale(glm::vec3(5, 5, 5));
	plane->rotate(glm::radians(-90.0f), glm::vec3(0,0,1));
	plane->rotate(glm::radians(45.0f), glm::vec3(1, 0, 0));
	plane->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(shadowMaterial);
	_world->add(plane);

	//add the floor
	GameObject* floor = new GameObject("floor", glm::vec3(0, -2.5f, 0));
	floor->scale(glm::vec3(15, 15, 15));
	floor->setMesh(planeMeshDefault);
	floor->setMaterial(greyMaterial);
	_world->add(floor);

	//add a desk
	desk = new GameObject("desk", glm::vec3(5, 0, -4));
	desk->scale(glm::vec3(3.5f, 3.5f, 3.5f));
	//desk->rotate(glm::radians(45.0f), glm::vec3(0, 1, 0));
	desk->setMesh(deskMesh);
	desk->setMaterial(litMaterialB);
	_world->add(desk);


	//add a cube umbrella
	umbrella = new GameObject("umbrella", glm::vec3(0, 3, 1));
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
	glm::mat4 transform = camera->getTransform();
	renderToTexture->bindFramebuffer();
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->setTransform(light->getTransform());
	umbrella->setMaterial(blackMaterial);
	desk->setMaterial(blackMaterial);
	plane->setMaterial(greyMaterial);
	AbstractGame::_render();
	renderToTexture->unbindFramebuffer();

	umbrella->setMaterial(litMaterialR);
	desk->setMaterial(litMaterialB);
	plane->setMaterial(shadowMaterial);
	camera->setTransform(transform);
	glClearColor(0.2f, 0.2f, 0.2f, 1);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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