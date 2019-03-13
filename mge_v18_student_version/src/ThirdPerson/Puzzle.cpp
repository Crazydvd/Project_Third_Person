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
	_popups = new UserInterface(_window);

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_loadfile(L, ("../src/ThirdPerson/levels/level" + std::to_string(_levelIndex) + ".lua").c_str());

	lua_pcall(L, 0, 0, 0);

	lua_getglobal(L, "puzzle");

	getPuzzles(L, "Puzzle");

	loadScoreTimes(L);

	loadLetter(L);

	lua_close(L);

	for (size_t i = 0; i < _puzzleObjects.size(); i++)
	{
		_puzzleObjects[i]->setBehaviour(new MouseRotatingBehaviour(_window, _world, _puzzleObjects));
	}
}

void Puzzle::loadObject(std::string pName, std::string pProperties[2][2], glm::vec3 pVectors[3])
{
	GameObject* object = new GameObject("puzzleObject", pVectors[0]);
	object->setMesh(Mesh::load(config::THIRDPERSON_MODEL_PATH + pProperties[0][1]));
	object->scale(pVectors[1]);
	object->setMaterial(new LitTextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + pProperties[1][1])));


	this->add(object);
	if (pName != "polaroid")
	{
		object->rotate(glm::radians((float)(std::rand() % 120) + 60.0f), glm::vec3(1, 0, 0));
		object->rotate(glm::radians((float)(std::rand() % 120) + 60.0f), glm::vec3(0, 1, 0));
		object->rotate(glm::radians((float)(std::rand() % 120) + 60.0f), glm::vec3(0, 0, 1));
		_puzzleObjects.push_back(object);
	}
	else
	{
		object->rotate(glm::radians(pVectors[2].x), glm::vec3(1.0f, 0, 0));
		object->rotate(glm::radians(pVectors[2].y), glm::vec3(0, 1.0f, 0));
		object->rotate(glm::radians(pVectors[2].z), glm::vec3(0, 0, 1.0f));
	}
}

void Puzzle::update(float pStep)
{
	if (Paused)
		return;

	// check for the game starting
	if (!_started)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if (_levelIndex == 1 && !_tutorial)
			{
				UITexture* tutorial = new UITexture(_window, "storypopuptutorial.png");
				_popups->EmptyInterface();
				_popups->Add(tutorial);
				_tutorial = true;
				return;
			}
			_started = true;
			_popups->QueueClear();
		}
		return;
	}

	GameObject::update(pStep);

	if (_puzzleObjects.size() > 1)
	{
		checkMultiplePuzzles();
	}
	else
	{
		checkOnePuzzle();
	}
	PuzzleTimer->SetTime(PuzzleTimer->GetTime() + pStep);
}


void Puzzle::getPuzzles(lua_State *L, std::string name)
{
	lua_pushnil(L);
	std::string params[2][2];
	glm::vec3 vectors[3] = { glm::vec3{1,1,1}, glm::vec3{1,1,1}, glm::vec3{1,1,1} };
	int index = 0;

	while (lua_next(L, -2) != 0)
	{
		if (lua_isstring(L, -1))
		{
			params[index][0] = lua_tostring(L, -2);
			params[index][1] = lua_tostring(L, -1);
			index++;
		}
		else if (lua_isnumber(L, -1))
		{
			printf("%s = %d", lua_tostring(L, -2), (int)lua_tonumber(L, -1));
		}
		else if (lua_istable(L, -1))
		{
			if ((std::string)lua_tostring(L, -2) == "position")
			{
				glm::vec3* position = fill_vector3(L);
				vectors[0] = *position;
			}
			else if ((std::string)lua_tostring(L, -2) == "scale")
			{
				glm::vec3* scale = fill_vector3(L);
				vectors[1] = *scale;
			}
			else if ((std::string)lua_tostring(L, -2) == "rotation")
			{
				glm::vec3* rotation = fill_vector3(L);
				vectors[2] = *rotation;
			}
			else
			{
				getPuzzles(L, lua_tostring(L, -2));
			}
		}
		lua_pop(L, 1);

	}
	if (params[0][0] != "")
	{
		loadObject(name, params, vectors);
	}
}

glm::vec3* Puzzle::fill_vector3(lua_State *L)
{
	lua_pushnil(L);
	glm::vec3* vector = new glm::vec3();
	int index = 0;

	while (lua_next(L, -2) != 0)
	{
		if (lua_isnumber(L, -1))
		{
			if ((std::string)lua_tostring(L, -2) == "x")
			{
				vector->x = (float)lua_tonumber(L, -1);
			}
			else if ((std::string)lua_tostring(L, -2) == "y")
			{
				vector->y = (float)lua_tonumber(L, -1);
			}
			else if ((std::string)lua_tostring(L, -2) == "z")
			{
				vector->z = (float)lua_tonumber(L, -1);
			}
		}
		lua_pop(L, 1);
		index++;
	}
	return vector;
}

void Puzzle::loadScoreTimes(lua_State* L)
{
	lua_getglobal(L, "triplestar");

	if (lua_isnumber(L, -1))
	{
		_tripleStarTime = (float)lua_tonumber(L, -1);
	}

	lua_getglobal(L, "doublestar");

	if (lua_isnumber(L, -1))
	{
		_doubleStarTime = (float)lua_tonumber(L, -1);
	}
}

void Puzzle::loadLetter(lua_State* L)
{
	std::string letter;
	lua_getglobal(L, "letter");

	if (lua_isnil(L, -1))
	{
		_started = true;
		printf("no letter\n");
		return;
	}
	else
	{
		letter = lua_tostring(L, -1);
	}

	UITexture* letterUI = new UITexture(_window, letter);
	_popups->Add(letterUI);
	this->add(_popups);
}

std::vector<GameObject*> Puzzle::getObjects()
{
	return _puzzleObjects;
}

void Puzzle::checkOnePuzzle()
{
	glm::vec3 rotation = _puzzleObjects[0]->getWorldRotation();

	//Check if we in solution range
	if ((rotation.y <= 8 || rotation.y >= 172) && !_inTolereance)
	{
		_puzzleObjects[0]->setBehaviour(new EmptyBehaviour());
		_inTolereance = true;
	}

	//Slowly rotate to perfect rotation and put a win screen
	if (_inTolereance)
	{
		//Rotate (slowly set X and Z of Y-axis to 0 so it points up)
		if (rotation.y >= 0.01 && rotation.y <= 179.99)
		{
			glm::mat4 newMatrix = _puzzleObjects[0]->getTransform();

			//x
			if (newMatrix[1].x <= -0.001 || newMatrix[1].x >= 0.001)
			{
				newMatrix[1].x -= glm::sign(newMatrix[1].x) * 0.0005;
			}
			else
			{
				newMatrix[1] = glm::vec4(0, newMatrix[1].y, newMatrix[1].z, 0);
			}

			//z
			if (newMatrix[1].z <= -0.001 || newMatrix[1].z >= 0.001)
			{
				newMatrix[1].z -= glm::sign(newMatrix[1].z) * 0.0005;
			}
			else
			{
				newMatrix[1] = glm::vec4(newMatrix[1].x, newMatrix[1].y, 0, 0);
			}

			//Orthonormolize the matrix according to Y-axis
			newMatrix[1] = glm::normalize(newMatrix[1]) * glm::length(_puzzleObjects[0]->getTransform()[1]);

			glm::mat3 normolizedMatrix = newMatrix;

			normolizedMatrix[0] = glm::orthonormalize(normolizedMatrix[0], normolizedMatrix[1]) * glm::length(newMatrix[0]);
			newMatrix[0] = glm::vec4(normolizedMatrix[0].x, normolizedMatrix[0].y, normolizedMatrix[0].z, 0);

			normolizedMatrix[2] = glm::orthonormalize(normolizedMatrix[2], normolizedMatrix[1]) * glm::length(newMatrix[2]);
			newMatrix[2] = glm::vec4(normolizedMatrix[2].x, normolizedMatrix[2].y, normolizedMatrix[2].z, 0);

			newMatrix[3] = _puzzleObjects[0]->getTransform()[3];		

			_puzzleObjects[0]->setTransform(newMatrix);
		}
		//Put a winscreen
		else
		{
			++_victoryDelay;

			if (_victoryDelay >= 240)
			{
				UITexture* winScreen = new UITexture(_window, "winscreen.png");
				winScreen->SetPosition(glm::vec3((_window->getSize().x - winScreen->GetRect().width) / 2, (_window->getSize().y - winScreen->GetRect().height) / 2, 0));
				//_userInterface->Add(winScreen);

				_victoryDelay = -20000;
			}
		}
	}
	else
	{
		rotateWithKeys();
	}
}

void Puzzle::checkMultiplePuzzles()
{
	//Check if we in solution range
	if (!_inTolereance)
	{
		for (int i = 0; i < _puzzleObjects.size(); i++)
		{
			glm::vec3 rotation = _puzzleObjects[i]->getWorldRotation();

			if (rotation.x <= 25 && rotation.y <= 25 && rotation.z <= 25)
			{
				_inTolereance = true;
			}
			else
			{
				_inTolereance = false;
				break;
			}
		}

		//Disable the rotation if completed
		if (_inTolereance == true)
		{
			for (int i = 0; i < _puzzleObjects.size(); i++)
			{
				_puzzleObjects[i]->setBehaviour(new EmptyBehaviour());
			}
		}
	}

	//Slowly rotate to perfect rotation and put a win screen
	if (_inTolereance)
	{
		for (int i = 0; i < _puzzleObjects.size(); i++)
		{
			glm::vec3 rotation = _puzzleObjects[i]->getWorldRotation();

			//Rotate (slowly set X and Z of Y-axis to 0 so it points up)
			if (rotation.y >= 0.01 && rotation.y <= 179.99)
			{
				glm::mat4 newMatrix = _puzzleObjects[i]->getTransform();

				//x
				if (newMatrix[1].x <= -0.001 || newMatrix[1].x >= 0.001)
				{
					newMatrix[1].x -= glm::sign(newMatrix[1].x) * 0.0005;
				}
				else
				{
					newMatrix[1] = glm::vec4(0, newMatrix[1].y, newMatrix[1].z, 0);
				}

				//z
				if (newMatrix[1].z <= -0.001 || newMatrix[1].z >= 0.001)
				{
					newMatrix[1].z -= glm::sign(newMatrix[1].z) * 0.0005;
				}
				else
				{
					newMatrix[1] = glm::vec4(newMatrix[1].x, newMatrix[1].y, 0, 0);
				}

				//Orthonormolize the matrix according to Y-axis
				newMatrix[1] = glm::normalize(newMatrix[1]) * glm::length(_puzzleObjects[i]->getTransform()[1]);

				glm::mat3 normolizedMatrix = newMatrix;

				normolizedMatrix[0] = glm::orthonormalize(normolizedMatrix[0], normolizedMatrix[1]) * glm::length(newMatrix[0]);
				newMatrix[0] = glm::vec4(normolizedMatrix[0].x, normolizedMatrix[0].y, normolizedMatrix[0].z, 0);

				normolizedMatrix[2] = glm::orthonormalize(normolizedMatrix[2], normolizedMatrix[1]) * glm::length(newMatrix[2]);
				newMatrix[2] = glm::vec4(normolizedMatrix[2].x, normolizedMatrix[2].y, normolizedMatrix[2].z, 0);

				newMatrix[3] = _puzzleObjects[i]->getTransform()[3];
			
				_puzzleObjects[i]->setTransform(newMatrix);		
			}
			else
			{
				//Rotate around Y to perfection
				if (_puzzleObjects[i]->getWorldRotation().x >= 3 && _puzzleObjects[i]->getWorldRotation().z >= 3)
				{
					float _direction = glm::sign(_puzzleObjects[i]->getTransform()[2].x);
					_puzzleObjects[i]->rotate(glm::radians(-0.07 * _direction), glm::vec3(0, 1, 0));
					_completed = false;
					std::cout << _puzzleObjects[i]->getWorldRotation() << std::endl;
				}
				else
				{
					_puzzleObjects[i]->setWorldRotation(glm::vec3(0, 0, 0));
					_completed = true;
				}
			}
		}

		//Put a winscreen
		if (_completed)
		{
			++_victoryDelay;

			if (_victoryDelay >= 240)
			{
				UITexture* winScreen = new UITexture(_window, "winscreen.png");
				winScreen->SetPosition(glm::vec3((_window->getSize().x - winScreen->GetRect().width) / 2, (_window->getSize().y - winScreen->GetRect().height) / 2, 0));
				//_userInterface->Add(winScreen);

				_victoryDelay = -200000;
			}
		}
	}
	else
	{
		rotateWithKeys();
	}
}

void Puzzle::draw()
{
	_popups->draw();
}

void Puzzle::rotateWithKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		for (int i = 0; i < _puzzleObjects.size(); i++)
		{
			_puzzleObjects[i]->setWorldRotation(glm::vec3(0, 0, 0));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_puzzleObjects[0]->rotate(glm::radians(-1.0), glm::vec3(1, 0, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_puzzleObjects[0]->rotate(glm::radians(1.0), glm::vec3(1, 0, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_puzzleObjects[0]->rotate(glm::radians(-1.0), glm::vec3(0, 1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		_puzzleObjects[0]->rotate(glm::radians(1.0), glm::vec3(0, 1, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_puzzleObjects[0]->rotate(glm::radians(-1.0), glm::vec3(0, 0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		_puzzleObjects[0]->rotate(glm::radians(1.0), glm::vec3(0, 0, 1));


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_puzzleObjects[0]->rotate(glm::radians(1.0), glm::vec3(1, 0, 1));

}

Puzzle::~Puzzle()
{
	//dtor
}