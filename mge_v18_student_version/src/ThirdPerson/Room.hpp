#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <string>
#include "mge/core/GameObject.hpp"
#include "glm.hpp"
#include <SFML/Graphics.hpp>
#include "ThirdPerson/Timer.hpp"
#include <lua.hpp>

class TPerson;
class Puzzle;
class RenderToTexture;

class Room : public GameObject
{
public:
	Room(TPerson* pGame, World* pWorld, sf::RenderWindow* pWindow, int pIndex, std::string pName = "room",
		glm::vec3 pPosition = glm::vec3(0.0f, 0.0f, 0.0f), RenderToTexture* pRender);
	virtual ~Room();
	virtual void update(float pStep);
	virtual void _render();

private:
	World* _roomWorld;
	TPerson* _game;
	Timer* _timer;
	GameObject* _roomParent;

	void print_table(lua_State* L);
	glm::vec3* fill_vector3(lua_State* L);
	void addObject(std::string pProperties[2][2], glm::vec3 pVectors[3]);
	void Initialize(int levelIndex);

	Puzzle* _puzzle;
	RenderToTexture* _renderToTexture;
};

#endif

