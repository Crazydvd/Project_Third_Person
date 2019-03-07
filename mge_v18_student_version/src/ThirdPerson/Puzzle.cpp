#include "ThirdPerson/Puzzle.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/MouseRotatingBehaviour.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/behaviours/EmptyBehaviour.hpp"

Puzzle::Puzzle(sf::RenderWindow* pWindow, World* pWorld, int pLevelIndex, std::string pName, glm::vec3 pPosition) : GameObject(pName, pPosition), _levelIndex(pLevelIndex), _window(pWindow), _world(pWorld)
{
	PuzzleTimer = new Timer(pWindow);
	_puzzleObjects = std::vector<GameObject*>();

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//TODO: Replace this by make a new "puzzle object" class and load the objects in there
	luaL_loadfile(L, ("../src/ThirdPerson/level" + std::to_string(_levelIndex) + ".lua").c_str());

	//puts(lua_tostring(L, -1));

	lua_call(L, 0, 0);

	lua_getglobal(L, "model");
	std::string model = lua_tostring(L, -1);

	lua_getglobal(L, "texture");
	std::string texture = lua_tostring(L, -1);

	LoadObject(model, texture);

	lua_close(L);

	_puzzleObjects[0]->setBehaviour(new MouseRotatingBehaviour(_window, _world, _puzzleObjects));

	this->add(_puzzleObjects[0]);
}

void Puzzle::LoadObject(std::string pModel, std::string pTexture)
{
	GameObject* object = new GameObject("puzzleObject", glm::vec3(0, 2, 0));
	object->setMesh(Mesh::load(config::THIRDPERSON_MODEL_PATH + pModel));
	object->scale(glm::vec3(0.1, 0.1, 0.1));
	object->setMaterial(new LitTextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + pTexture)));
	object->rotate(glm::radians((float)(std::rand() % 160) + 35.0f), glm::vec3(1, 0, 0));
	object->rotate(glm::radians((float)(std::rand() % 160) + 35.0f), glm::vec3(0, 1, 0));
	object->rotate(glm::radians((float)(std::rand() % 160) + 35.0f), glm::vec3(0, 0, 1));
	
	_puzzleObjects.push_back(object);
}

void Puzzle::update(float pStep) {
	GameObject::update(pStep);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		_puzzleObjects[0]->rotate(glm::radians(1.0f), glm::vec3(1, 0, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		_puzzleObjects[0]->rotate(glm::radians(1.0f), glm::vec3(0, 1, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		_puzzleObjects[0]->rotate(glm::radians(1.0f), glm::vec3(0, 0, 1));
	}

	checkOnePuzzle();
	PuzzleTimer->SetTime(PuzzleTimer->GetTime() + pStep);
}

std::vector<GameObject*> Puzzle::getObjects() {
	return _puzzleObjects;
}

void Puzzle::checkOnePuzzle()
{
	glm::vec3 rotation = _puzzleObjects[0]->getWorldRotation();// -glm::vec3(solutionDegreesX, solutionDegreesY, solutionDegreesZ);

	//std::cout << tolerance << std::endl;
	//std::cout << solutionDegreesX << ", ";
	//std::cout << solutionDegreesY << ", ";
	//std::cout << solutionDegreesZ << std::endl;
	std::cout << rotation.x << ", ";
	std::cout << rotation.y << ", ";
	std::cout << rotation.z << std::endl;


	if (rotation.y <= 8 || rotation.y >= 172)
	{
		std::cout << "BITCH LASAGNA" << std::endl;
		_puzzleObjects[0]->setBehaviour(new EmptyBehaviour());

		_completed = true;
	}

	if (_completed)
	{

		/*if (rotation.y >= 5 && rotation.y <= 175)
		{*/
		glm::vec3 yAxis = _puzzleObjects[0]->getTransform()[1];
		glm::vec3 diffirenceVec = yAxis - glm::vec3(0, 1, 0);
		//_object1->rotate(glm::radians(0.3f), glm::vec3(diffirenceVec));
		//_object1->setWorldRotation(glm::vec3(0, 0, 0));

	}
	else
	{
		++_victoryDelay;

		if (_victoryDelay >= 240)
		{
			UITexture* winScreen = new UITexture(_window, "winscreen.png");
			winScreen->SetPosition(glm::vec3((_window->getSize().x - winScreen->GetRect().width) / 2, (_window->getSize().y - winScreen->GetRect().height) / 2, 0));
			//_userInterface->Add(winScreen);

			_victoryDelay = 0;
			_completed = false;
		}
	}
}

Puzzle::~Puzzle()
{
	//dtor
}