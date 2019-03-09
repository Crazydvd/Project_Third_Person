#include <SFML/Window/Keyboard.hpp>

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/RenderToTextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "ThirdPerson/config.hpp"
#include "ThirdPerson/TPerson.hpp"

#include "ThirdPerson/RenderToTexture.hpp"
#include "Room.hpp"

GameObject* _sphere;

Room::Room(TPerson* pGame, World* pWorld, sf::RenderWindow* pWindow, RenderToTexture* pRender, std::string pName, glm::vec3 pPosition)
	: GameObject(pName, pPosition), _renderToTexture(pRender), _window(pWindow)
{
	_game = pGame;
	_roomWorld = pWorld;
	_puzzle = new Puzzle(pWindow, pWorld, _levelIndex);
	_blackMaterial = new ColorMaterial(glm::vec3(0, 0, 0));
	_levelIndex = 1;

	Initialize(_levelIndex);
}

void Room::Initialize(int levelIndex)
{
	_roomParent = new GameObject("room", glm::vec3(0, 0, 0));
	_roomWorld->add(_roomParent);

	_roomParent->add(_puzzle);

	/* Load LUA */
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	if (luaL_loadfile(L, "../src/ThirdPerson/room.lua") || lua_pcall(L, 0, 0, 0))
	{
		printf("Cannot run file\n");
		return;
	}

	// Print table contents.
	lua_getglobal(L, "objects");

	print_table(L);

	lua_close(L);



	//a light to light the scene!
	glm::vec3 color(1, 1, 1);
	AbstractMaterial* lightMaterial = new ColorMaterial(color);
	light = new Light("light", glm::vec3(0, 4, 0), LightType::SPOT); //0, 4, 0
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	//light->translate(glm::vec3(0, 0, 3));
	light->SetLightIntensity(2);
	light->setAmbientContribution(0.2f);
	Mesh* mesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + "cone_smooth.obj");
	light->setMesh(mesh);
	light->setMaterial(lightMaterial);
	light->SetLightColor(color); //1, 0, 0.8f

	_roomParent->add(light);
	LitMaterial::AddLight(light);
}

void Room::update(float pStep)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		MoveToNextLevel();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		MoveToPreviousLevel();
	}
}

void Room::print_table(lua_State *L)
{
	lua_pushnil(L);
	std::string params[2][2];
	glm::vec3 vectors[3] = {glm::vec3{1,1,1}, glm::vec3{1,1,1}, glm::vec3{1,1,1}};
	int index = 0;

	while (lua_next(L, -2) != 0)
	{
		if (lua_isstring(L, -1))
		{
			params[index][0] = lua_tostring(L, -2);
			params[index][1] = lua_tostring(L, -1);
			index++;
		}
		else if (lua_isnumber(L, -1)) {
			printf("%s = %d", lua_tostring(L, -2), (int)lua_tonumber(L, -1));
		}
		else if (lua_istable(L, -1)) {
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
				print_table(L);
			}
		}
		lua_pop(L, 1);

	}
	if (params[0][0] != "")
	{
		addObject(params, vectors);
	}
}

glm::vec3* Room::fill_vector3(lua_State *L)
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

void Room::addObject(std::string pProperties[2][2], glm::vec3 pVectors[3])
{
	int h = 2 + (std::rand() % (5 - 2 + 1));
	GameObject* object = new GameObject("object", pVectors[0]);

	Mesh* mesh = Mesh::load(config::THIRDPERSON_MODEL_PATH + pProperties[0][1]);
	AbstractMaterial* material;
	if (pProperties[1][1] == "shadow") 
	{
		material = new RenderToTextureMaterial(_renderToTexture->getTexture()); //Very important
	}
	else 
	{
		material = new LitTextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + pProperties[1][1]), glm::vec3(0,0,0));
	}

	object->setMesh(mesh);
	object->setMaterial(material);
	object->scale(pVectors[1]);
	object->rotate(glm::radians(pVectors[2].x), glm::vec3(1.0f, 0, 0));
	object->rotate(glm::radians(pVectors[2].y), glm::vec3(0, 1.0f, 0));
	object->rotate(glm::radians(pVectors[2].z), glm::vec3(0, 0, 1.0f));
	_roomParent->add(object);
}

void Room::MoveToPreviousLevel()
{
	_levelIndex--;
	if (_levelIndex < 1) { _levelIndex = 1; return; }
	_roomParent->remove(_puzzle);
	delete(_puzzle);
	_puzzle = new Puzzle(_window, _world, _levelIndex);
	_world->add(_puzzle);
}

void Room::MoveToNextLevel()
{
	_levelIndex++;
	if (_levelIndex > 2) { _levelIndex = 2; return; }
	_roomParent->remove(_puzzle);
	delete(_puzzle);
	_puzzle = new Puzzle(_window, _world, _levelIndex);
	_roomParent->add(_puzzle);
}


void Room::_render()
{
	glm::mat4 lightTransform = light->getWorldTransform();
	_renderToTexture->Render(_puzzle->getObjects(), _blackMaterial, lightTransform);

	_puzzle->PuzzleTimer->draw();
}


Room::~Room()
{
	//_world->remove(_sphere);
	if (_world != NULL) {
		_world->remove(_roomParent);
	}
}
