#include <iostream>
#include <string>
#include "Time.h"

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
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
#include "ThirdPerson/Audio.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
TPerson::TPerson() :AbstractGame(), _hud(0)
{
	Audio* audio = new Audio(SoundType::SOUND, "ThirdPerson/sounds/paper2.wav"); //Don't do this, for more information ask Daniel.
	//Audio audio(SoundType::SOUND, "ThirdPerson/sounds/paper2.wav"); //Use lines like this instead.
	audio->SetLoop(true);
	audio->Play();
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
	_renderToTexture = new RenderToTexture();
	_renderToTexture->setTPerson(this);

	//UI
	_userInterface = new UserInterface(_window);
	_world->add(_userInterface);

   //add camera first (it will be updated last)
	camera = new Camera("camera", glm::vec3(0, 3, 2.5f));
	camera->rotate(glm::radians(-45.0f), glm::vec3(1, 0, 0));
	camera->setBehaviour(new KeysBehaviour(25, 90));

	_world->add(camera);
	_world->setMainCamera(camera);

	room = new Room(this, _world, _window, _renderToTexture);
	_world->add(room);
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

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	AbstractGame::_render();

	_updateHud();
	room->_render();
}

void TPerson::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
	_userInterface->draw();
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

