#include <SFML/Window/Keyboard.hpp>

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "ThirdPerson/config.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Puzzle.hpp"

#include "Room.hpp"

GameObject* _sphere;

Room::Room(TPerson* pGame, World* pWorld, sf::RenderWindow* pWindow, int pIndex, std::string pName, glm::vec3 pPosition)
	: GameObject(pName, pPosition)
{
	_timer = new Timer(pWindow);
	_game = pGame;
	_roomWorld = pWorld;
	Initialize(pIndex);

	_puzzle = new Puzzle(pWindow, pWorld);
}

void Room::Initialize(int levelIndex)
{
	_roomParent = new GameObject("room", glm::vec3(0, 0, 0));
	_roomWorld->add(_roomParent);

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
	
	//TODO: Replace this by make a new "puzzle object" class and load the objects in there
	/*luaL_loadfile(L, ("../src/ThirdPerson/level" + std::to_string(levelIndex) + ".lua").c_str());

	puts(lua_tostring(L, -1));

	lua_call(L, 0, 0);

	lua_getglobal(L, "model");
	std::string model = lua_tostring(L, -1);

	lua_getglobal(L, "texture");
	std::string texture = lua_tostring(L, -1);

	lua_close(L);

	_puzzle->LoadObject(model, texture);*/

	////load a bunch of meshes we will be using throughout this demo
	////each mesh only has to be loaded once, but can be used multiple times:
	////F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	//Mesh* planeMeshDefault = Mesh::load(config::THIRDPERSON_MODEL_PATH + "plane.obj");
	//Mesh* sphereMeshS = Mesh::load(config::THIRDPERSON_MODEL_PATH + model);

	////MATERIALS

	////create some materials to display the cube, the plane and the light
	//AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + texture));

	////add the floor
	//GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	//plane->scale(glm::vec3(5, 5, 5));
	//plane->setMesh(planeMeshDefault);
	//plane->setMaterial(runicStoneMaterial);
	//_roomParent->add(plane);

	////add a spinning sphere
	//_sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
	//_sphere->scale(glm::vec3(2.5, 2.5, 2.5));
	//_sphere->setMesh(sphereMeshS);
	//_sphere->setMaterial(runicStoneMaterial);
	//_sphere->setBehaviour(new RotatingBehaviour());
	//_roomParent->add(_sphere);
	
}

void Room::update(float pStep)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) 
	{
		_game->MoveToNextLevel();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) 
	{
		_game->MoveToPreviousLevel();
	}
	else 
	{
		// Set timer
		_timer->SetTime(_timer->GetTime() + pStep);
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
	AbstractMaterial* material = new TextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + pProperties[1][1]));

	object->setMesh(mesh);
	object->setMaterial(material);
	object->scale(pVectors[1]);
	object->rotate(glm::radians(pVectors[2].x), glm::vec3(1.0f, 0, 0));
	object->rotate(glm::radians(pVectors[2].y), glm::vec3(0, 1.0f, 0));
	object->rotate(glm::radians(pVectors[2].z), glm::vec3(0, 0, 1.0f));
	_roomParent->add(object);
}

void Room::_render()
{
	_timer->draw();
}


Room::~Room()
{
	//_world->remove(_sphere);
	if (_world != NULL) {
		_world->remove(_roomParent);
	}
}
